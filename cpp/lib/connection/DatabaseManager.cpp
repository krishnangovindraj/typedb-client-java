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

#include <iostream>

namespace TypeDB {

DatabaseManager::DatabaseManager(_native::Connection* connectionNative) {    
    databaseManagerNative = connectionNative ? 
        NativePointer<_native::DatabaseManager>(_native::database_manager_new(connectionNative), _native::database_manager_drop) :
        NativePointer<_native::DatabaseManager>(nullptr);
}

DatabaseManager::DatabaseManager(DatabaseManager&& from) noexcept {
    *this = std::move(from);
}

DatabaseManager& DatabaseManager::operator=(DatabaseManager&& from) {
    databaseManagerNative = std::move(from.databaseManagerNative);
    return *this;
}

void DatabaseManager::create(const std::string& name) const {
    _native::databases_create(databaseManagerNative.get(), name.c_str());
    TypeDBDriverException::check_and_throw();
}

bool DatabaseManager::contains(const std::string& name) const {
    return _native::databases_contains(databaseManagerNative.get(), name.c_str());
}

Database DatabaseManager::get(const std::string& name) const {
    std::cout << "Database manager get called" << std::endl;
    return Database(_native::databases_get(databaseManagerNative.get(), name.c_str())); // No std::move for copy-elision
}


DatabaseIterator DatabaseManager::all() const {
    return DatabaseIterator(_native::databases_all(databaseManagerNative.get()));
}

DatabaseIterator::DatabaseIterator(_native::DatabaseIterator* nativeIterator) {
    databaseIteratorNative = nativeIterator ? 
        NativePointer<_native::DatabaseIterator>(nativeIterator, _native::database_iterator_drop) :
        NativePointer<_native::DatabaseIterator>(nullptr);
}

bool DatabaseIterator::hasNext() {
    if (pNext.get() == nullptr && databaseIteratorNative != nullptr) {
        _native::Database* p = _native::database_iterator_next(databaseIteratorNative.get());
        if (p != nullptr) {
            pNext = NativePointer<_native::Database>(p, &_native::database_close);
        } else {
            pNext = NativePointer<_native::Database>(nullptr);
            databaseIteratorNative.reset();
        }
    }
    return pNext.get() != nullptr;
}

Database DatabaseIterator::next() {
    if (hasNext()) {
        return Database(pNext.release());
    } else {
        throw std::out_of_range("next() was called on iterator which does not have a next element.");
    }
}

}
