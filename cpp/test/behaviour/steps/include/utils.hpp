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

namespace TypeDB::BDD {

template <typename T, typename A1>
void foreach_serial(const std::vector<A1>& args, std::function<T(const A1&)> fn) {
    std::for_each(args.begin(), args.end(), fn);
}

template <typename T, typename A1>
void foreach_parallel(const std::vector<A1>& args, std::function<T(const A1&)> fn) {
    std::function<std::future<T>(const A1&)> async_fn = [&](const A1& arg) { return std::async(std::launch::async, fn, arg); };

    std::vector<std::future<T>> futures;
    std::transform(args.begin(), args.end(), std::back_inserter(futures), async_fn);
    std::for_each(futures.begin(), futures.end(), [](std::future<T>& f) { f.wait(); });
}

}  // namespace TypeDB::BDD