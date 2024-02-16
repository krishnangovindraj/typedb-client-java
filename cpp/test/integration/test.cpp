/*
 * Copyright (C) 2022 Vaticle
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <atomic>
#include <chrono>
#include <iostream>
#include <regex>
#include <thread>

#include "gtest/gtest.h"

#include "typedb_driver.hpp"

using namespace TypeDB;

void delete_if_exists(const TypeDB::Driver& driver, const std::string& name) {
    if (driver.databases.contains(name)) {
        driver.databases.get(name).deleteDatabase();
    }
}

TEST(TestDatabaseManager, TestCreateTwice) {
    std::string dbName = "hello_from_cpp";
    TypeDB::Driver driver = TypeDB::Driver::coreDriver("127.0.0.1:1729");
    delete_if_exists(driver, dbName);
    driver.databases.create(dbName);

    try {
        driver.databases.create(dbName);
        FAIL();  // "Exception not thrown"
    } catch (DriverException& e) {
        ASSERT_TRUE(e.message().find("already exists") != std::string::npos);
    }
}


TEST(TestExplanations, TestExplainableOwnership) {
    std::string dbName = "test_explanations";
    TypeDB::Driver driver = TypeDB::Driver::coreDriver("127.0.0.1:1729");
    int attrValue = 42;
    std::string ruleLabel = "ownership-generation";
    std::string then = "$a has $a";
    std::string when = "$a isa attr;";
    std::regex whenRegex = std::regex("\\{\\s*\\$a isa attr;\\s*\\}");

    delete_if_exists(driver, dbName);

    driver.databases.create(dbName);
    TypeDB::Options options;

    {
        auto session = driver.session(dbName, TypeDB::SessionType::SCHEMA, options);
        auto tx = session.transaction(TypeDB::TransactionType::WRITE, options);
        std::string schema =
            " define attr sub attribute, value long, owns attr;"
            "rule " +
            ruleLabel + ": when { " + when + " } then { " + then + "; }; ";
        tx.query.define(schema, options).wait();

        tx.commit();
    }

    {
        auto session = driver.session(dbName, TypeDB::SessionType::DATA, options);
        auto tx = session.transaction(TypeDB::TransactionType::WRITE, options);

        auto results = tx.query.insert("insert $o " + std::to_string(attrValue) + " isa attr;", options);
        for (auto& it : results)
            ;
        tx.commit();
    }

    {
        TypeDB::Options explainOptions;
        explainOptions.infer(true).explain(true);

        auto session = driver.session(dbName, TypeDB::SessionType::DATA, options);
        auto tx = session.transaction(TypeDB::TransactionType::READ, explainOptions);

        auto results = tx.query.get("match $o1 has $o2; get;", options);
        for (TypeDB::ConceptMap& cm : results) {
            for (std::string& v : cm.variables()) {
                ASSERT_TRUE(v == "o1" || v == "o2");
                ASSERT_EQ(attrValue, cm.get(v)->asAttribute()->getValue()->asLong());
            }
            for (auto& ownsKey : cm.explainables().ownerships()) {
                auto explainable = cm.explainables().ownership(ownsKey.owner, ownsKey.attribute);
                for (auto& explanation : tx.query.explain(explainable, options)) {
                    ASSERT_EQ(ruleLabel, explanation.rule().label());
                    ASSERT_EQ(then, explanation.rule().then());
                    ASSERT_TRUE(std::regex_match(explanation.rule().when(), whenRegex));
                    // std::cout << explanation.rule().then() << " :- " << explanation.rule().when() <<  std::endl;

                    auto conclusion = explanation.conclusion();
                    for (std::string& v : conclusion.variables()) {
                        ASSERT_EQ(v, "a");
                        ASSERT_EQ(attrValue, conclusion.get(v)->asAttribute()->getValue()->asLong());
                    }
                    auto condition = explanation.condition();
                    for (std::string& v : condition.variables()) {
                        ASSERT_EQ(v, "a");
                        ASSERT_EQ(attrValue, conclusion.get(v)->asAttribute()->getValue()->asLong());
                    }
                }
            }
        }
    }
}

TEST(TestCallbacks, TestCallbacks) {
    std::string dbName = "test-integration-callbacks";
    TypeDB::Driver driver = TypeDB::Driver::coreDriver("127.0.0.1:1729");
    TypeDB::Options options;
    delete_if_exists(driver, dbName);
    driver.databases.create(dbName);
    bool txCalled = false;
    bool sessCalled = false;
    {
        auto session = driver.session(dbName, TypeDB::SessionType::DATA, options);
        session.onClose([&]() { sessCalled = true; });
        {
            auto tx = session.transaction(TypeDB::TransactionType::READ, options);
            tx.onClose([&](const std::optional<DriverException>& e) { txCalled = true; });
            ASSERT_FALSE(txCalled);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // ASSERT_TRUE(txCalled); // TODO: re-enable
        ASSERT_FALSE(sessCalled);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ASSERT_TRUE(sessCalled);
}

TEST(TestConnection, TestMissingPort) {
    std::string dbName = "hello_from_cpp";

    try {
        TypeDB::Driver driver = TypeDB::Driver::coreDriver("127.0.0.1");
        FAIL();  // "Exception not thrown"
    } catch (DriverException& e) {
        ASSERT_TRUE(e.message().find("missing port") != std::string::npos);
    }
}

TEST(TestDebug, TestRobustAPI) {
    const char* accessManagementSchema = "define\n attr sub attribute, value string, owns attr;";
    const char* accessManagementDataBatches[1][1] = {"insert $s \"o0_val\" isa attr; $s has attr \"o1_val\";"};
    {
    auto driver = TypeDB::Driver::coreDriver("localhost:1729");
    delete_if_exists(driver, "access-management-db");
    driver.databases.create("access-management-db");
    }

TypeDB::Driver driver = TypeDB::Driver::coreDriver("localhost:1729");
TypeDB::Options options;
{
    TypeDB::Session session = driver.session("access-management-db", TypeDB::SessionType::SCHEMA, options);
    TypeDB::Transaction tx = session.transaction(TypeDB::TransactionType::WRITE, options);
    tx.query.define(accessManagementSchema, options).wait();
    tx.commit();
}
{
    TypeDB::Session session = driver.session("access-management-db", TypeDB::SessionType::DATA, options);

    for (auto& batch: accessManagementDataBatches) {
        TypeDB::Transaction tx = session.transaction(TypeDB::TransactionType::WRITE, options);
        for (auto& query: batch) {
            tx.query.insert(query, options);
        }
        tx.commit();
    }
    {
        TypeDB::Transaction tx = session.transaction(TypeDB::TransactionType::READ, options);
        ConceptMapIterable results = tx.query.get("match $u isa user; get;", options);
    }
}

}

TEST(TestDebug, TestSchemaMigration ) {
    {
    auto driver = TypeDB::Driver::coreDriver("localhost:1729");
    delete_if_exists(driver, "access-management-db");
    driver.databases.create("access-management-db");

    const char* schema = "define name sub attribute, value string; email sub attribute, value string ; employee sub entity, owns name, owns email; contractor sub entity; ";
    TypeDB::Options options;
    TypeDB::Session session = driver.session("access-management-db", TypeDB::SessionType::SCHEMA, options);
    TypeDB::Transaction tx = session.transaction(TypeDB::TransactionType::WRITE, options);
    tx.query.define(schema);
    tx.commit();
    }

TypeDB::Driver driver = TypeDB::Driver::coreDriver("localhost:1729");
TypeDB::Options options;
TypeDB::Session session = driver.session("access-management-db", TypeDB::SessionType::SCHEMA, options);
TypeDB::Transaction tx = session.transaction(TypeDB::TransactionType::WRITE, options);

// create a new abstract type "user"
std::unique_ptr<EntityType> user = tx.concepts.putEntityType("user").get();
user->setAbstract(tx).get();

// change the supertype of "employee" to "user"
auto employee = tx.concepts.getEntityType("employee").get();
employee->setSupertype(tx, user.get()).get();

// change the supertype of "contractor" to "user"
auto contractor = tx.concepts.getEntityType("contractor").get();
contractor->setSupertype(tx, user.get()).get();

// move "email" and "name" attribute types to be owned by "user" instead of "employee"
std::unique_ptr<AttributeType> email = tx.concepts.getAttributeType("email").get();
std::unique_ptr<AttributeType> name = tx.concepts.getAttributeType("name").get();
employee->unsetOwns(tx, email.get()).get();
employee->unsetOwns(tx, name.get()).get();
user->setOwns(tx, email.get()).get();
user->setOwns(tx, name.get()).get();

// rename "name" attribute type to "full-name"
name->setLabel(tx, "full-name").get();

// commit all schema changes in one transaction, which will fail if we violate any data validation
tx.commit();

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
