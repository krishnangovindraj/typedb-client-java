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

cucumber_bdd::StepCollection<Context> databaseSteps = {
    // basic
    BDD_STEP("connection create database: (\\w+)", {
        context.driver->databases.create(matches[1]);
    }),

    BDD_STEP("connection has database: (\\w+)", {
        ASSERT_TRUE(context.driver->databases.contains(matches[1]));
    }),

    BDD_STEP("connection does not have database: (\\w+)", {
        ASSERT_FALSE(context.driver->databases.contains(matches[1]));
    }),

    BDD_STEP("connection delete database: (\\w+)", {
        context.driver->databases.get(matches[1]).drop();
    }),

    BDD_STEP("connection delete database; throws exception: (\\w+)", {
      DRIVER_THROWS(matches[1], {context.driver->databases.get(matches[1]).drop();});
    }),

    // multi
    BDD_STEP("connection create databases:", {
        for (auto row : step.argument->data_table->rows) {
            context.driver->databases.create(row.cells[0].value);
        }
    }),

    BDD_STEP("connection has databases:", {
        std::set<std::string> expected;
        for (auto row : step.argument->data_table->rows) expected.insert(row.cells[0].value);
        
        int cnt = 0;
        DatabaseIterable databases = context.driver->databases.all();
        for (DatabaseIterator it = databases.begin(); it != databases.end() ; ++it ) {
            Database& db = *it;
            std::string dbName = db.name();
            cnt++;
            ASSERT_TRUE( expected.find(dbName) != expected.end() );
        }
        ASSERT_EQ(expected.size(), cnt);
    }),

    BDD_STEP("connection does not have databases:", {
        for (auto row : step.argument->data_table->rows) {
            ASSERT_FALSE(context.driver->databases.contains(row.cells[0].value));
        }
    }),

    BDD_STEP("connection delete databases:", {
        for (auto row : step.argument->data_table->rows) {
            context.driver->databases.get(row.cells[0].value).drop();
        }
    }),

    // parallel
    BDD_STEP("connection create databases in parallel:", {
        for (auto row : step.argument->data_table->rows) {
            context.driver->databases.create(row.cells[0].value);
        }
    }),
    BDD_STEP("connection delete databases in parallel:", {
        for (auto row : step.argument->data_table->rows) {
            context.driver->databases.get(row.cells[0].value).drop();
        }
    }),
};

}  // namespace TypeDB::BDD
