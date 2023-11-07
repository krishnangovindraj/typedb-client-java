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

#include "typedb/query/querymanager.hpp"
#include "typedb/common/exception.hpp"
#include "typedb/connection/transaction.hpp"

#include "../inc/macros.hpp"

namespace TypeDB {

QueryManager::QueryManager(TypeDB::Transaction* parentTransaction)
    : parentTransaction(parentTransaction) { }

void QueryManager::define(const std::string& query, const Options& options) const {
    CHECK_NATIVE(parentTransaction);
    _native::query_define(parentTransaction->getNative(), query.c_str(), options.getNative());
    TypeDBDriverException::check_and_throw();
}

void QueryManager::undefine(const std::string& query, const Options& options) const {
    CHECK_NATIVE(parentTransaction);
    _native::query_undefine(parentTransaction->getNative(), query.c_str(), options.getNative());
    TypeDBDriverException::check_and_throw();
}

ConceptMapIterable QueryManager::match(const std::string& query, const Options& options) const {
    CHECK_NATIVE(parentTransaction);
    auto p = _native::query_match(parentTransaction->getNative(), query.c_str(), options.getNative());
    TypeDBDriverException::check_and_throw();
    return ConceptMapIterable(p);
}

ConceptMapIterable QueryManager::insert(const std::string& query, const Options& options) const {
    CHECK_NATIVE(parentTransaction);
    auto p = _native::query_insert(parentTransaction->getNative(), query.c_str(), options.getNative());
    TypeDBDriverException::check_and_throw();
    return ConceptMapIterable(p);
}

void QueryManager::matchDelete(const std::string& query, const Options& options) const {
    CHECK_NATIVE(parentTransaction);
    _native::query_delete(parentTransaction->getNative(), query.c_str(), options.getNative());
    TypeDBDriverException::check_and_throw();
}

}  // namespace TypeDB
