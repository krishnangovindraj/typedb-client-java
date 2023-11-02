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

#include "typedb/connection/DatabaseManager.hpp"
#include "typedb/common/TypeDBDriverException.hpp"

#include "../inc/macros.hpp"

namespace TypeDB {

// DatabaseIterator
template <>
std::function<void(_native::DatabaseIterator*)> DatabaseIterator::fn_nativeIterDrop = &_native::database_iterator_drop;
template <>
std::function<_native::Database*(_native::DatabaseIterator*)> DatabaseIterator::fn_nativeIterNext = &_native::database_iterator_next;
template <>
std::function<void(_native::Database*)> DatabaseIterator::fn_nativeElementDrop = &_native::database_close;


DatabaseManager::DatabaseManager(_native::Connection* connectionNative) {
    databaseManagerNative = connectionNative ? NativePointer<_native::DatabaseManager>(_native::database_manager_new(connectionNative), _native::database_manager_drop) : NativePointer<_native::DatabaseManager>(nullptr);
}

DatabaseManager::DatabaseManager(DatabaseManager&& from) noexcept {
    *this = std::move(from);
}

DatabaseManager& DatabaseManager::operator=(DatabaseManager&& from) {
    databaseManagerNative = std::move(from.databaseManagerNative);
    return *this;
}

void DatabaseManager::create(const std::string& name) const {
    CHECK_NATIVE(databaseManagerNative);
    _native::databases_create(databaseManagerNative.get(), name.c_str());
    TypeDBDriverException::check_and_throw();
}

bool DatabaseManager::contains(const std::string& name) const {
    CHECK_NATIVE(databaseManagerNative);
    auto t = _native::databases_contains(databaseManagerNative.get(), name.c_str());
    TypeDBDriverException::check_and_throw();
    return t; 
}

Database DatabaseManager::get(const std::string& name) const {
    CHECK_NATIVE(databaseManagerNative);
    auto t = _native::databases_get(databaseManagerNative.get(), name.c_str());
    TypeDBDriverException::check_and_throw();
    return Database(t);  // No std::move for copy-elision
}

DatabaseIterable DatabaseManager::all() const {
    CHECK_NATIVE(databaseManagerNative);
    _native::DatabaseIterator* t = _native::databases_all(databaseManagerNative.get());
    TypeDBDriverException::check_and_throw();
    return DatabaseIterable(t);
}

}  // namespace TypeDB
