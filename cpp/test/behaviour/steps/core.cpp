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

#include "common.hpp"
#include "steps.hpp"

namespace TypeDB::BDD {

const std::string DEFAULT_CORE_ADDRESS = "127.0.0.1:1729";

void TestHooks::beforeScenario(const Context& context, const cucumber_bdd::Scenario<Context>* scenario) const {
}

void TestHooks::afterScenario(const Context& context, const cucumber_bdd::Scenario<Context>* scenario) const {
    TypeDB::Driver driver(DEFAULT_CORE_ADDRESS);
    DatabaseIterator dbIter = driver.databases.all();
    while (dbIter.hasNext()) {
        dbIter.next().drop();
    }
}

const TestHooks testHooks;

cucumber_bdd::StepCollection<Context> connectionSteps = {
    BDD_NOOP("typedb starts"),

    BDD_STEP("connection opens with default authentication", {
        context.driver = std::make_unique<TypeDB::Driver>(DEFAULT_CORE_ADDRESS);
    }),

    BDD_UNIMPLEMENTED("connection opens with authentication: (\\w), (\\w)"),

    BDD_UNIMPLEMENTED("connection opens with authentication: (\\w), (\\w); throws exception"),

    BDD_STEP("connection has been opened", {
        ASSERT_TRUE(context.driver->isOpen());
    }),

    BDD_STEP("connection does not have any database", {
        ASSERT_FALSE(context.driver->databases.all().hasNext());
    }),

    BDD_STEP("connection closes", {
        context.driver.reset();
    }),

    BDD_NOOP("typedb stops"),
};

}  // namespace TypeDB::BDD
