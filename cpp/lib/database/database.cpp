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

#include "typedb/database/Database.hpp"

#include <iostream>

using namespace TypeDB;

namespace TypeDB {

Database::Database(_native::Database* db) noexcept
    : databaseNative(db, _native::database_close) {}

Database::Database(Database&& from) noexcept {
    *this = std::move(from);
}

Database& Database::operator=(Database&& from) {
    databaseNative = std::move(from.databaseNative);
    return *this;
}

void Database::drop() {
    _native::database_delete(databaseNative.get());
    databaseNative.release();  // Dangling pointer. Release avoids invoking the deleter (database_close)
}

}  // namespace TypeDB
