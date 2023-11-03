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

#include "typedb/connection/session.hpp"
#include "typedb/common/exception.hpp"

#include "inc/macros.hpp"

#include <iostream>

namespace TypeDB {

void closeMe(_native::Session* sessionNative) {
    DBG("Closeme called on %x", sessionNative);
    _native::session_close(sessionNative);
}

Session::Session() : Session(nullptr) {}

Session::Session(_native::Session* sessionNative)
    : sessionNative(sessionNative, closeMe) {} // _native::session_close) {} // TODO: Revert


Session::Session(Session&& from) {
    *this = std::move(from);
}

Session& Session::operator=(Session&& from) {
    sessionNative = std::move(from.sessionNative);
    return *this;
}

bool Session::isOpen() const {
    return sessionNative != nullptr && _native::session_is_open(sessionNative.get());
}

std::string Session::databaseName() const {
    CHECK_NATIVE(sessionNative);
    char* nameNative = _native::session_get_database_name(sessionNative.get());
    TypeDBDriverException::check_and_throw();
    std::string databaseName(nameNative);
    _native::string_free(nameNative);
    return databaseName;
}


}  // namespace TypeDB
