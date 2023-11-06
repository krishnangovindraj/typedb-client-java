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
#include <vector>
#include <future>
#include "typedb/common/native.hpp"
#include "cucumber/messages/pickle_table.hpp"


#include <cstdio>
#define DBG1(STR) fprintf(stderr, STR "\n")
#define DBG(FMT, ...) fprintf(stderr, FMT "\n", __VA_ARGS__) // TODO: Remove

namespace TypeDB::BDD {

bool parseBoolean(const std::string& str);
TypeDB::TransactionType parseTransactionType(const std::string& str);


template <typename T> 
struct zipped {
    const cucumber::messages::pickle_table_row* row;
    T* obj;   
};

template <typename T> 
std::vector<zipped<T>> zip(const std::vector<cucumber::messages::pickle_table_row>& rows, std::vector<T>& objs) { // Important that these are by reference.
    assert( rows.size() == objs.size() );
    std::vector<zipped<T>> z;
    for (int i = 0; i < rows.size(); i++) {
        z.push_back(zipped<T>{&rows[i], &objs[i]});
    }
    return z;
}


template <typename A1>
void foreach_serial(const std::vector<A1>& args, std::function<void(const A1*)> fn) {
    for (auto& arg: args) { fn(&arg); }
}

template <typename T, typename A1>
std::vector<T> apply_serial(const std::vector<A1>& args, std::function<T(const A1*)> fn) {
    std::vector<T> results;
    for (auto& arg: args) results.push_back(fn(&arg));
    return results;
}

template <typename A1>
void foreach_parallel(const std::vector<A1>& args, std::function<void(const A1*)> fn) {
    std::vector<std::future<void>> futures;
    for (const A1& arg : args ) {
        futures.push_back(std::async(std::launch::async, fn, &arg));
    }
    std::for_each(futures.begin(), futures.end(), [](std::future<void>& f) { f.wait(); });
}

template <typename T, typename A1>
std::vector<T> apply_parallel(const std::vector<A1>& args, std::function<T(const A1*)> fn) {
    std::vector<std::future<T>> futures;
    for (const A1& arg : args ) {
        futures.push_back(std::async(std::launch::async, fn, &arg));
    }
    std::vector<T> results;
    std::transform(futures.begin(), futures.end(), std::back_inserter(results), [](std::future<T>& f) { return f.get(); });
    return results;
}

}  // namespace TypeDB::BDD