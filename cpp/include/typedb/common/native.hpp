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

#include <functional>
#include <memory>
#include <utility>

namespace TypeDB {

namespace _native {

// Forward declare all relevant native types
struct Annotation;
struct Concept;
struct ConceptMap;
struct ConceptMapGroup;
struct Connection;
struct Credential;
struct Database;
struct DatabaseManager;
struct Error;
struct Explainable;
struct Explainables;
struct Explanation;
struct Options;
struct ReplicaInfo;
struct RolePlayer;
struct Rule;
struct SchemaException;
struct Session;
struct Transaction;
struct User;
struct UserManager;
struct ValueGroup;
struct StringPair;

// Promise
struct ConceptPromise;
struct RulePromise;
struct StringPromise;

struct VoidPromise;
struct BoolPromise;

// Iterators
struct RolePlayerIterator;
struct ReplicaInfoIterator;
struct ConceptIterator;
struct ConceptMapGroupIterator;
struct ConceptMapIterator;
struct DatabaseIterator;
struct ExplanationIterator;
struct RuleIterator;
struct SchemaExceptionIterator;
struct StringIterator;
struct StringPairIterator;
struct UserIterator;
struct ValueGroupIterator;


}  // namespace _native

template <typename T>
using NativePointer = std::unique_ptr<T, std::function<void(T*)> >;

}  // namespace TypeDB

#include "typedb/common/native_traits.hpp"
