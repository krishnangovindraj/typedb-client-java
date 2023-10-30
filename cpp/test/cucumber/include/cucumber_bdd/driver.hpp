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

#include <cucumber/messages/envelope.hpp>

#include "cucumber_bdd/step.hpp"
#include "cucumber_bdd/caserun.hpp"

namespace cucumber_bdd {

using pickle = cucumber::messages::pickle;
using pickle_step = cucumber::messages::pickle_step;

class DriverBase {
   private:
    std::vector<std::pair<const std::regex*, void*>> stepIndex;

   public:

    void loadFeature(const std::string& path);

    int runAllTests();

    virtual void registerTest(const std::string& featureName, const pickle& scenario) = 0;
};

template <typename CTX>
class Driver : public DriverBase {
   private:
    CTX ctx;
    const StepCollection<CTX> steps;

   public:
    Driver(StepCollection<CTX> steps) : steps(steps) {}
    
    void registerTest(const std::string& featureName, const pickle& scenario) override {
        std::vector<ResolvedStep<CTX>> resolvedSteps;
        for (pickle_step step : scenario.steps) {
            resolvedSteps.push_back(ResolvedStep<CTX>{step, resolveStep(step)});
        }
        testing::RegisterTest(
            featureName.c_str(), scenario.name.c_str(), 
            nullptr, nullptr,
            __FILE__, __LINE__,
            CaseRunFactory<CTX>{resolvedSteps}
        );
    }

     const StepDefinition<CTX>* resolveStep(pickle_step& step) {
        for (const StepDefinition<CTX>* s = steps.steps ; s < (steps.steps + steps.nSteps); s++)  {
            if ( std::regex_match(step.text, s->regex) ) {
                return s;
            }
        }
        throw std::runtime_error("Unmatched step: " + step.text);
    } 
};

}