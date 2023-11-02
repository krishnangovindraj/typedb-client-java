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

#include <iostream>

#include "gtest/gtest.h"

#include "typedb/connection/driver.hpp"
#include "typedb/common/exception.hpp"

#define NULLSAFE(X) ((X) ? (X) : "null")

using namespace TypeDB;


void delete_if_exists(const TypeDB::Driver& driver, const std::string& name) {
    if (driver.databases().contains(name)) {
        driver.databases().get(name).drop();
    }
}

TEST(TestConceptAPI, TestData) {
    std::string dbName = "hello_from_cpp";
    TypeDB::Driver driver("127.0.0.1:1729");
    delete_if_exists(driver, dbName);
    EXPECT_FALSE(_native::check_error());
    driver.databases().create(dbName);

    try {
        driver.databases().create(dbName);
        FAIL(); // "Exception not thrown"
    } catch (TypeDBDriverException e) {
        std::cout << "Caught exception with message: " << e.message() << std::endl ;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
