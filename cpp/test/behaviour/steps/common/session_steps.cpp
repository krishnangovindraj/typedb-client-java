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

#include <cstdlib>

#include "common.hpp"
#include "steps.hpp"
#include "utils.hpp"

#include "typedb/connection/session.hpp"

namespace TypeDB::BDD {

using namespace cucumber::messages;

cucumber_bdd::StepCollection<Context> sessionSteps = {
    BDD_STEP("connection open session for database: (\\w+)", {
        context.session = std::move(context.driver.session(matches[1], Constants::SessionType::DATA, context.sessionOptions));
    }),
    BDD_STEP("session is null: (true|false)", {
        ASSERT_EQ(parseBoolean(matches[1]), !context.session.isOpen());
    }),
    BDD_STEP("session is open: (true|false)", {
        ASSERT_EQ(parseBoolean(matches[1]), context.session.isOpen());
    }),
    BDD_STEP("session has database: (\\w+)", {
        ASSERT_EQ(matches[1], context.session.databaseName());
    }),

    BDD_STEP("connection open schema session for database: (\\w+)", {
        context.session = std::move(context.driver.session(matches[1], Constants::SessionType::SCHEMA, context.sessionOptions));
    }),
    BDD_STEP("connection open data session for database: (\\w+)", {
        context.session = std::move(context.driver.session(matches[1], Constants::SessionType::DATA, context.sessionOptions));
    }),
    BDD_STEP("connection open sessions for databases:", {
        std::function<TypeDB::Session(const pickle_table_row&)> fn = [&](const pickle_table_row& row) { return context.driver.session(row.cells[0].value, Constants::SessionType::DATA, context.sessionOptions); };
        context.sessions = std::move(apply_serial(step.argument->data_table->rows, fn));
    }),
    
    BDD_STEP("connection open data sessions in parallel for databases:", {
        std::function<TypeDB::Session(const pickle_table_row&)> fn = [&](const pickle_table_row& row) { return context.driver.session(row.cells[0].value, Constants::SessionType::DATA, context.sessionOptions); };
        context.sessions = std::move(apply_parallel(step.argument->data_table->rows, fn));
    }),
    BDD_STEP("connection open sessions in parallel for databases:", {
        std::function<TypeDB::Session(const pickle_table_row&)> fn = [&](const pickle_table_row& row) { return context.driver.session(row.cells[0].value, Constants::SessionType::DATA, context.sessionOptions); };
        context.sessions = std::move(apply_parallel(step.argument->data_table->rows, fn));
    }),
    BDD_STEP("connection close all sessions", {
        std::function<TypeDB::Session(const pickle_table_row&)> fn = [&](const pickle_table_row& row) { return context.driver.session(row.cells[0].value, Constants::SessionType::DATA, context.sessionOptions); };
        foreach_serial(step.argument->data_table->rows, fn);
    }),
    
    BDD_STEP("sessions are null: (true|false)", {
        std::function<void(const pickle_table_row&)> fn = [&](const pickle_table_row& row) {  ASSERT_EQ(parseBoolean(matches[1]), !context.session.isOpen()); };
        foreach_serial(step.argument->data_table->rows, fn);
    }),
    
    BDD_STEP("sessions are open: (true|false)", {
        std::function<void(const pickle_table_row&)> fn = [&](const pickle_table_row& row) {  ASSERT_EQ(parseBoolean(matches[1]), context.session.isOpen()); };
        foreach_serial(step.argument->data_table->rows, fn);
    }),
    BDD_STEP("sessions in parallel are null: (true|false)", {
        std::function<void(const pickle_table_row&)> fn = [&](const pickle_table_row& row) {  ASSERT_EQ(parseBoolean(matches[1]), !context.session.isOpen()); };
        foreach_parallel(step.argument->data_table->rows, fn);
    }),
    BDD_STEP("sessions in parallel are open: (true|false)", {
        std::function<void(const pickle_table_row&)> fn = [&](const pickle_table_row& row) {  ASSERT_EQ(parseBoolean(matches[1]), context.session.isOpen()); };
        foreach_parallel(step.argument->data_table->rows, fn);
    }),
    
    
    BDD_STEP("sessions have databases:", {
        auto rows = step.argument->data_table->rows;
        ASSERT_EQ(context.sessions.size(), rows.size());
        for (int i = 0; i < rows.size() ; i++) {
            ASSERT_EQ(rows[i].cells[0].value, context.sessions[i].databaseName());
        }
    }),
    
    BDD_STEP("sessions in parallel have databases:", {
        std::function<void(const pickle_table_row* row, const TypeDB::Session* session)> fn = [&](const pickle_table_row* row, const TypeDB::Session* session){ ASSERT_EQ(row->cells[0].value, session->databaseName()); };
        auto rows = step.argument->data_table->rows;
        ASSERT_EQ(context.sessions.size(), rows.size());
        std::vector<std::future<void>> futures;
        for (int i = 0; i < rows.size() ; i++) {
            futures.push_back(std::async(std::launch::async, fn, &rows[i], &context.sessions[i]));
        }
        for (auto& f: futures) { f.wait(); }
    }),
    BDD_STEP("set session option (\\w+) to: (\\w+)", {
        assert(matches[1] == "session-idle-timeout-millis");
        context.sessionOptions.sessionIdleTimeoutMillis(atoi(matches[2].str().c_str()));
    }),
};

}
