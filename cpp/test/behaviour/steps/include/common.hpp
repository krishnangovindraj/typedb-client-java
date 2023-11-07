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
#include <map>
#include <vector>
#include <memory>

#include "cucumber_bdd/runner.hpp"
#include "cucumber_bdd/step.hpp"
#include "cucumber_bdd/testrun.hpp"

#include "typedb/connection/driver.hpp"
#include "typedb/answer/conceptmap.hpp"

namespace TypeDB::BDD {


struct Context {
    TypeDB::Driver driver; // TODO: All these optional, so the null checks are meaningful
    TypeDB::Session session;
    TypeDB::Transaction transaction;

    std::vector<TypeDB::Session> sessions;
    std::map<TypeDB::Session*, std::vector<TypeDB::Transaction>> sessionTransactions; // Brittle: We strongly assume the session will always live in Context.sessions
    
    TypeDB::Options sessionOptions;
    TypeDB::Options transactionOptions;

    // Results:
    std::vector<TypeDB::ConceptMap> lastConceptMapResult;

    void setResult(TypeDB::ConceptMapIterable& results) {
        lastConceptMapResult.clear();
        for (TypeDB::ConceptMap& result: results) {
            lastConceptMapResult.push_back(std::move(result));
        }
        
    }

};

class TestHooks : public cucumber_bdd::TestHooks<Context> {
    void beforeAll() const override;
    void afterScenario(const Context& context, const cucumber_bdd::Scenario<Context>* scenario) const override;
};

extern const TestHooks testHooks;

}  // namespace TypeDB::BDD
