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

namespace TypeDB::BDD {

void createDatabase() {
    
}


cucumber_bdd::StepCollection<Context> databaseSteps = { 
    
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

    {std::regex("connection delete database; throws exception: (\\w+)"), &unimplemented},

    {std::regex("connection create databases:"), &unimplemented},
    {std::regex("connection has databases:"), &unimplemented},
    {std::regex("connection does not have databases:"), &unimplemented},
    {std::regex("connection delete databases:"), &unimplemented},

    {std::regex("connection create databases in parallel:"), &unimplemented},
    {std::regex("connection delete databases in parallel:"), &unimplemented},
};

}
