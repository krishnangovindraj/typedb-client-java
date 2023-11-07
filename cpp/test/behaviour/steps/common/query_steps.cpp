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
#include <algorithm>

#include "common.hpp"
#include "steps.hpp"
#include "utils.hpp"


#include "typedb/connection/session.hpp"

using namespace cucumber::messages;

namespace TypeDB::BDD {

std::vector<std::map<std::string, std::string>> dataTabletoMap(const pickle_table& table) {
    std::vector<std::map<std::string, std::string>> result;
    std::vector<std::string> varNames;
    for (pickle_table_cell cell : table.rows[0].cells) {
        varNames.push_back(cell.value);
    } 
    for (int i = 1; i < table.rows.size(); i++) {
        auto& row = table.rows[i];
        std::map<std::string, std::string> m;
        for (int i=0; i < varNames.size(); i++) {
            m[varNames[i]] = row.cells[i].value;
        }
        result.push_back(m);
    }
    return result;
}

cucumber_bdd::StepCollection<Context> querySteps = {

    BDD_STEP("typeql define", {
        context.transaction.query.define(step.argument->doc_string->content, TypeDB::Options());
    }),
    BDD_STEP("typeql define; throws exception", {
        DRIVER_THROWS("", { context.transaction.query.define(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql define; throws exception containing \"(.+)\"", {
        DRIVER_THROWS(matches[1].str(), { context.transaction.query.define(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql undefine", {
        context.transaction.query.undefine(step.argument->doc_string->content, TypeDB::Options());
    }),
    BDD_STEP("typeql undefine; throws exception", {
        DRIVER_THROWS("", { context.transaction.query.undefine(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql undefine; throws exception containing \"(.*)\"", {
        DRIVER_THROWS("", { context.transaction.query.undefine(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql insert", {
        auto iterable = context.transaction.query.insert(step.argument->doc_string->content, TypeDB::Options());
        context.setResult(iterable);
    }),
    BDD_STEP("typeql insert; throws exception", {
        DRIVER_THROWS("", { context.transaction.query.insert(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql insert; throws exception containing \"(.*)\"", {
        DRIVER_THROWS(matches[1].str(), { context.transaction.query.insert(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql delete", {
        context.transaction.query.matchDelete(step.argument->doc_string->content, TypeDB::Options());
    }),
    BDD_STEP("typeql delete; throws exception", {
        DRIVER_THROWS("", { context.transaction.query.matchDelete(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_STEP("typeql delete; throws exception containing \"(.*)\"", {
        DRIVER_THROWS("", { context.transaction.query.matchDelete(step.argument->doc_string->content, TypeDB::Options()); });
    }),
    BDD_UNIMPLEMENTED("typeql update"),
    BDD_UNIMPLEMENTED("typeql update; throws exception"),
    BDD_UNIMPLEMENTED("typeql update; throws exception containing \"(.*)\""),
    BDD_UNIMPLEMENTED("get answers of typeql insert"),
    BDD_STEP("get answers of typeql match", {
        auto iterable = context.transaction.query.match(step.argument->doc_string->content, TypeDB::Options());
        context.setResult(iterable);
    }),
    BDD_STEP("typeql match; throws exception", {
        DRIVER_THROWS("", {context.transaction.query.match(step.argument->doc_string->content, TypeDB::Options());});
    }),
    BDD_STEP("typeql match; throws exception containing \"(.*)\"", {
        DRIVER_THROWS(matches[1].str(), {context.transaction.query.match(step.argument->doc_string->content, TypeDB::Options());});
    }),
    BDD_UNIMPLEMENTED("get answer of typeql match aggregate"),
    BDD_UNIMPLEMENTED("typeql match aggregate; throws exception"),
    BDD_UNIMPLEMENTED("get answers of typeql match group"),
    BDD_UNIMPLEMENTED("typeql match group; throws exception"),
    BDD_UNIMPLEMENTED("get answers of typeql match group aggregate"),
    BDD_STEP("answer size is: (\\d+)", {
        ASSERT_EQ(atoi(matches[1].str().c_str()), context.lastConceptMapResult.size());
    }),
    BDD_UNIMPLEMENTED("rules contain: (\\w+)"),
    BDD_UNIMPLEMENTED("rules do not contain: (\\w+)"),
    BDD_STEP("uniquely identify answer concepts", {
        // std::map<std::string, std::string> expected = dataTabletoMap(step.argument->data_table);
        // for (auto & k : expected) std::cout << k << std::endl;
        // for (TypeDB::ConceptMap& ans: context.lastConceptMapResult) {
        //     std::cout << "ONE!" ;
        // }

    }),
    BDD_UNIMPLEMENTED("order of answer concepts is"),
    BDD_UNIMPLEMENTED("aggregate value is: (\\d+(\\.\\d+)?)"),
    BDD_UNIMPLEMENTED("aggregate answer is not a number"),
    BDD_UNIMPLEMENTED("answer groups are"),
    BDD_UNIMPLEMENTED("group aggregate values are"),
    BDD_UNIMPLEMENTED("each answer satisfies"),
    BDD_UNIMPLEMENTED("templated typeql match; throws exception"),

};

}  // namespace TypeDB::BDD
