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
#include "utils.hpp"

namespace TypeDB::BDD {

cucumber_bdd::StepCollection<Context> sessionSteps = {
    BDD_STEP("connection open session for database: (\\w+)", {
        context.session = std::move(context.driver.session(matches[1], Constants::SessionType::DATA, Options()));
    }),
    BDD_STEP("session is null: (true|false)", {
        ASSERT_EQ(parseBoolean(matches[1]), !context.session.isOpen());
    }),
    BDD_STEP("session is open: (true|false)", {
        ASSERT_EQ(parseBoolean(matches[1]), context.session.isOpen());
    }),
    BDD_STEP("session has database: (\\w+)", {
        ASSERT_EQ(matches[1], context.session.databaseName());
    })
};

}
