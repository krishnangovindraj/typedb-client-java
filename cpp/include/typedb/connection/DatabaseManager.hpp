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

#include <string>
#include <memory>

#include "typedb/common/native.hpp"
#include "typedb/database/Database.hpp"

namespace TypeDB {

class DatabaseIterator;

class DatabaseManager {
   private:
    NativePointer<_native::DatabaseManager> databaseManagerNative;

   public:
    DatabaseManager(_native::Connection*);
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager(DatabaseManager&&) noexcept;
     
    DatabaseManager& operator=(DatabaseManager&&);

    void create(const std::string&) const;
    bool contains(const std::string&) const;
    Database get(const std::string&) const;
    DatabaseIterator all() const;
};

class DatabaseIterator : public std::iterator<std::input_iterator_tag,Database> {
    // Start with the java style iterator. Can implement std::iterator style functions later.
   private: 
    NativePointer<_native::DatabaseIterator> databaseIteratorNative;
    NativePointer<_native::Database> pNext;
   public:
    DatabaseIterator(_native::DatabaseIterator* nativeIterator);
    bool hasNext();
    Database next();
};

}
