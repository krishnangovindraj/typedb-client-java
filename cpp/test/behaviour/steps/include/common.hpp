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

#pragma once

#include "cucumber_bdd/step.hpp"
#include "cucumber_bdd/driver.hpp"
#include "cucumber_bdd/testrun.hpp"

#include "typedb/connection/Driver.hpp"

// #define BDD_STEP(REGEX, IMPL) (StepDefinition<TypeDB::BDD::Context>{(REGEX), [](Context& context, const cucumber::messages::pickle_step& step, const std::smatch& matches){IMPL}})

namespace TypeDB::BDD {
    
    struct Context { 
        // TypeDB::Driver driver;
    };

    void noop(Context& context, const cucumber::messages::pickle_step& step, const std::smatch& matches);
    void unimplemented(Context& context, const cucumber::messages::pickle_step& step, const std::smatch& matches);

    extern cucumber_bdd::StepCollection<Context> connectionSteps;
    extern cucumber_bdd::StepCollection<Context> databaseSteps;
    extern cucumber_bdd::StepCollection<Context> sessionSteps;

}
