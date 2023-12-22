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

#include "typedb/common/native.hpp"


namespace TypeDB {

namespace _native {

template <typename T>
struct DropImpl {
    void operator()(T*);
};

template <typename T, typename F>
struct FutureImpl {
    using FUTURE = F;
    static T* resolve(F*);
};

template <typename T, typename I>
struct IteratorImpl {
    using ITERATOR = I;
    static T* next(I*);
    static void drop(I*);
};

template <typename T>
struct NativeTraits {
    // Optionally: using iterator = IteratorImpl<T, ?>;
    // Optionally: using future = FutureImpl<T, ?>;
    typedef DropImpl<T> drop;
};


// Specialisations for the iteratos
template <>
struct NativeTraits<RolePlayer> {
    using iterator = IteratorImpl<RolePlayer, RolePlayerIterator>;
};
template <>
struct NativeTraits<ReplicaInfo> {
    using iterator = IteratorImpl<ReplicaInfo, ReplicaInfoIterator>;
};
template <>
struct NativeTraits<Concept> {
    using iterator = IteratorImpl<Concept, ConceptIterator>;
    using future = FutureImpl<Concept, ConceptPromise>;
};
template <>
struct NativeTraits<ConceptMapGroup> {
    using iterator = IteratorImpl<ConceptMapGroup, ConceptMapGroupIterator>;
};
template <>
struct NativeTraits<ConceptMap> {
    using iterator = IteratorImpl<ConceptMap, ConceptMapIterator>;
};
template <>
struct NativeTraits<Database> {
    using iterator = IteratorImpl<Database, DatabaseIterator>;
};
template <>
struct NativeTraits<Explanation> {
    using iterator = IteratorImpl<Explanation, ExplanationIterator>;
};

template <>
struct NativeTraits<Rule> {
    using iterator = IteratorImpl<Rule, RuleIterator>;
};

template <>
struct NativeTraits<SchemaException> {
    using iterator = IteratorImpl<SchemaException, SchemaExceptionIterator>;
};

template <>
struct NativeTraits<char> {
    using iterator = IteratorImpl<char, StringIterator>;
    using future = FutureImpl<char, StringPromise>;
    using drop = DropImpl<char>;
};

template <>
struct NativeTraits<StringPair> {
    using iterator = IteratorImpl<StringPair, StringPairIterator>;
};

template <>
struct NativeTraits<User> {
    using iterator = IteratorImpl<User, UserIterator>;
};

template <>
struct NativeTraits<ValueGroup> {
    using iterator = IteratorImpl<ValueGroup, ValueGroupIterator>;
};

}

// Hiding this in traits for now
template <typename T, typename Deleter = typename _native::NativeTraits<T>::drop>
using __NativePointer = std::unique_ptr<T, Deleter>;

}  // namespace TypeDB
