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

#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <gherkin/parser.hpp>
#include <gherkin/utils.hpp>
#include <gherkin/pickle_compiler.hpp>

#include "cucumber_bdd/driver.hpp"



#ifdef NDEBUG
#define DEBUGONLY(CMD) {}
#else
#define DEBUGONLY(CMD) {(CMD);}
#endif

namespace cucumber_bdd {


bool skipScenario(const cucumber::messages::pickle& scenario) {
    for (auto tag: scenario.tags) {
        if (tag.name == "@ignore") return true;
    }
    return false;
}

void DriverBase::loadFeature(const std::string& path) {
    std::string featureContents = gherkin::slurp(path);
    gherkin::parser parser;
    cucumber::messages::gherkin_document doc = parser.parse(path, featureContents);
    gherkin::pickle_compiler compiler;
    
    if (doc.feature.has_value()) {
        for (cucumber::messages::pickle scenario : compiler.compile(doc, path)) {
            if (skipScenario(scenario)) {
                DEBUGONLY(std::cout << "Skipping scenario: " << scenario.name << std::endl)
            } else {
                DEBUGONLY(std::cout << "Registering scenario: " << scenario.name << std::endl)
                registerTest(doc.feature.value().name, scenario);
            }
        }
    }
    DEBUGONLY(std::cout << "All tests registered." << std::endl);
}


int DriverBase::runAllTests() {
    return RUN_ALL_TESTS();
}

}

#undef DEBUGONLY
