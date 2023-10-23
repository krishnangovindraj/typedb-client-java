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
#include "typedb/connection/Driver.hpp"
#include "typedb/common/TypeDBDriverException.hpp"

using namespace TypeDB;

 TEST(TestConceptAPI, TestData) {
     TypeDB::Driver driver("127.0.0.1:1729");
     EXPECT_FALSE(_native::check_error());
     driver.databaseManager.create("hello_from_cpp");

     try {
         driver.databaseManager.create("hello_from_cpp");
     } catch (TypeDBDriverException e) {
         std::cout << "Caught exception with message: " << e.message() << std::endl ;
     }
 }


class MoveMe {
   public:
    char* c;
    int x;
    
    MoveMe(char* ac, int ax) {
        c = ac;
        x = ax;
    }  

    MoveMe(MoveMe& other) = delete;

    MoveMe(MoveMe&& from) {
        c = from.c;
        from.c = nullptr;
        x = from.x + 1;
    }

    ~MoveMe() {
        std::cout << "MoveMe destructor called at " << c << "::" << x << std::endl;
    }

    MoveMe& operator=(MoveMe&& from) {
        c = from.c;
        from.c = nullptr;
        x = from.x + 1;
        return *this;
    }

};

// std::unique_ptr<int> z() {
//     std::unique_ptr<int> x(new int);
//     *x = 5;
//     return std::move(x);
// }


TEST(LearnMove, LearnMove) {
    // std::unique_ptr<int> y = z;
    // std::cout << *y << std::endl;
    char cstr[] = "moo";
    MoveMe m1(cstr, 1);
    MoveMe m2 = std::move(m1);
    std::cout << ((m1.c) ? m1.c : "null") << "::" << m1.x << std::endl;
    std::cout << ((m2.c) ? m2.c : "null") << "::" << m2.x << std::endl;

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
