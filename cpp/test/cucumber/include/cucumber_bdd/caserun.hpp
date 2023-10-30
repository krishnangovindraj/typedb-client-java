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
#include <cassert>

#include "gtest/gtest.h"
#include <cucumber/messages/envelope.hpp>

#include "cucumber_bdd/step.hpp"

namespace cucumber_bdd {

using pickle = cucumber::messages::pickle;
using pickle_step = cucumber::messages::pickle_step;

template <typename CTX>
using Scenario = std::vector<ResolvedStep<CTX>>;


#ifdef NDEBUG
#define DEBUGONLY(CMD) {}
#else
#define DEBUGONLY(CMD) {(CMD);}
#endif

template <typename CTX>
class CaseRun : public testing::Test {
   private:
    CTX ctx;
    const Scenario<CTX>* scenario;

   public:
    CaseRun(const Scenario<CTX>* scenario) 
    : scenario(scenario)
     { }


    void TestBody() override {
        DEBUGONLY(std::cout << "Running scenario: " << testing::UnitTest::GetInstance()->current_test_info()->name() << std::endl);
        for (ResolvedStep<CTX> step : *scenario) {
            DEBUGONLY(std::cout << "\t-" << step.step.text << std::endl);
            std::smatch regex_matches;
            bool success = std::regex_match(step.step.text, regex_matches, step.definition->regex);
            assert(success);
            step.definition->impl(ctx, step.step, regex_matches);
        }
    }
};

template <typename CTX>
struct CaseRunFactory {
    const Scenario<CTX> resolvedSteps;
    
    CaseRun<CTX>* operator()() {
        return new CaseRun<CTX>(&resolvedSteps);
    }
};


}

#undef DEBUG_ONLY