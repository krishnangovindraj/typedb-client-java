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
#include "typedb/query/querymanager.hpp"

namespace TypeDB {

class Session;  // forward declaration for friendship

class Transaction {

    friend class TypeDB::Session;
    friend class TypeDB::QueryManager;

   private:
    NativePointer<_native::Transaction> transactionNative;
    

    Transaction(_native::Transaction*, TypeDB::TransactionType);

    _native::Transaction* getNative();
    TypeDB::TransactionType txnType;
   public:
    const QueryManager query;
    

    Transaction();
    Transaction(const Transaction&) = delete;
    Transaction(Transaction&&);

    Transaction& operator=(const Transaction&) = delete;
    Transaction& operator=(Transaction&&);

    TypeDB::TransactionType type();

    bool isOpen() const;

    void close();
    
    void forceClose();

    void commit();

    void rollback();

};

}  // namespace TypeDB