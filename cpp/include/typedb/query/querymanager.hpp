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

#include "typedb/common/native.hpp"
#include "typedb/connection/options.hpp"

namespace TypeDB {

class Transaction;

class QueryManager {

    friend class TypeDB::Transaction;

   private:
    // _native::Transaction* transactionNative; // Use the native directly, enforcing that the QueryManager never outlives the transaction.
    TypeDB::Transaction* parentTransaction;

    QueryManager(TypeDB::Transaction*);
    QueryManager(QueryManager&&) noexcept;
    QueryManager& operator=(QueryManager&&);

   public:
    QueryManager(const QueryManager&) = delete;
    QueryManager& operator=(const QueryManager&) = delete;

    void define(const std::string& query, const Options& options) const;
};

}