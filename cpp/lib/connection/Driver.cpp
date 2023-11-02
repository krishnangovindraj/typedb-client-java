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

#include "typedb/connection/driver.hpp"

#include <iostream>

using namespace TypeDB;

namespace TypeDB {

Driver::Driver(const std::string& coreAddress)
    : Driver(_native::connection_open_core(coreAddress.c_str())) {}

Driver::Driver(_native::Connection* conn) noexcept
    : connectionNative(conn, _native::connection_close),
      databases(this->connectionNative.get()),
      users(this->connectionNative.get()) {}

Driver::Driver(Driver&& from)
    : connectionNative(std::move(from.connectionNative)),
      databases(std::move(from.databases)),
      users(std::move(from.users)) {}

Driver& Driver::operator=(Driver&& from) {
    connectionNative = std::move(from.connectionNative);
    from.connectionNative = nullptr;
    databases = std::move(from.databases);
    users = std::move(from.users);
    return *this;
}

bool Driver::isOpen() {
    return connectionNative != nullptr && _native::connection_is_open(connectionNative.get());
}

bool Driver::operator==(const Driver& other) {
    return connectionNative == other.connectionNative;
}

}  // namespace TypeDB
