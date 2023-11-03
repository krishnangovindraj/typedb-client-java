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

cucumber_bdd::StepCollection<Context> querySteps = {

    BDD_STEP("typeql define", {
        context.transaction.query.define(step.argument->doc_string->content, TypeDB::Options());
    }),
    BDD_STEP("typeql define; throws exception", {
        DRIVER_THROWS("", {context.transaction.query.define(step.argument->doc_string->content, TypeDB::Options());});
    }),
    BDD_STEP("typeql define; throws exception containing \"(.+)\"", {
        DRIVER_THROWS(matches[1].str(), {context.transaction.query.define(step.argument->doc_string->content, TypeDB::Options());});
    }),
    BDD_UNIMPLEMENTED("typeql undefine"),
    BDD_UNIMPLEMENTED("typeql undefine; throws exception"),
    BDD_UNIMPLEMENTED("typeql undefine; throws exception containing \"(.*)\""),
    BDD_STEP("typeql insert", {
        context.transaction.query.insert(step.argument->doc_string->content, TypeDB::Options());
    }),
    BDD_STEP("typeql insert; throws exception", {
        DRIVER_THROWS("", {context.transaction.query.insert(step.argument->doc_string->content, TypeDB::Options());});
    }),
    BDD_STEP("typeql insert; throws exception containing \"(.*)\"", {
        DRIVER_THROWS(matches[1].str(), {context.transaction.query.insert(step.argument->doc_string->content, TypeDB::Options());});
    }),
    BDD_UNIMPLEMENTED("typeql delete"),
    BDD_UNIMPLEMENTED("typeql delete; throws exception"),
    BDD_UNIMPLEMENTED("typeql delete; throws exception containing \"(.*)\""),
    BDD_UNIMPLEMENTED("typeql update"),
    BDD_UNIMPLEMENTED("typeql update; throws exception"),
    BDD_UNIMPLEMENTED("typeql update; throws exception containing \"(.*)\""),
    BDD_UNIMPLEMENTED("get answers of typeql insert"),
    BDD_UNIMPLEMENTED("get answers of typeql match"),
    BDD_UNIMPLEMENTED("typeql match; throws exception"),
    BDD_UNIMPLEMENTED("typeql match; throws exception containing \"(.*)\""),
    BDD_UNIMPLEMENTED("get answer of typeql match aggregate"),
    BDD_UNIMPLEMENTED("typeql match aggregate; throws exception"),
    BDD_UNIMPLEMENTED("get answers of typeql match group"),
    BDD_UNIMPLEMENTED("typeql match group; throws exception"),
    BDD_UNIMPLEMENTED("get answers of typeql match group aggregate"),
    BDD_UNIMPLEMENTED("answer size is: (\\d+)"),
    BDD_UNIMPLEMENTED("rules contain: (\\w+)"),
    BDD_UNIMPLEMENTED("rules do not contain: (\\w+)"),
    BDD_UNIMPLEMENTED("uniquely identify answer concepts"),
    BDD_UNIMPLEMENTED("order of answer concepts is"),
    BDD_UNIMPLEMENTED("aggregate value is: (\\d+(\\.\\d+)?)"),
    BDD_UNIMPLEMENTED("aggregate answer is not a number"),
    BDD_UNIMPLEMENTED("answer groups are"),
    BDD_UNIMPLEMENTED("group aggregate values are"),
    BDD_UNIMPLEMENTED("each answer satisfies"),
    BDD_UNIMPLEMENTED("templated typeql match; throws exception"),

};

}  // namespace TypeDB::BDD
