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
#include <cassert>
#include <iostream>
#include <iterator>
#include <optional>

#include "typedb/common/exception.hpp"
#include "typedb/common/native.hpp"
// #include "typedb/common/traits.hpp"
#include "typedb/common/native_traits.hpp"

namespace TypeDB {

/**
 * \private
 */
// template <typename NATIVE_ITER, typename NATIVE_T, typename T>
// class IteratorHelper;

template <typename T, typename TRAITS, typename INSTANTIATER>
class Iterable;

/**
 * \brief A structure emulating std::iterator, used for streaming of query results from the server.
 *
 * It is an <code>input_iterator</code>, meaning it can only be consumed once.
 * Valid operations are <code>++it</code> and <code>*it</code> <br/>
 *
 * Note that <code>it++</code> is deleted, and
 * <code>*it</code> can only be called once per iterator position, owing to the move semantics of the returned data.
 *
 * Also see <code>Iterable</code>
 */
template <typename T, typename TRAITS = _native::NativeTraits<typename T::NativeElement>, typename INSTANTIATER = T>
class Iterator {  // Does not support range-based for loops yet.

    using SELF = Iterator<T, TRAITS, INSTANTIATER>;

    using NATIVE_T = typename TRAITS::native_t;
    using HELPER = typename TRAITS::iterator;
    using NATIVE_ITER = typename HELPER::iterator_t;

public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::input_iterator_tag;

    Iterator(NATIVE_ITER* iteratorNative)
        : iteratorNative(iteratorNative, &HELPER::drop),
          obj() {}

    Iterator(const SELF& from) = delete;

    Iterator(SELF&& from)
        : iteratorNative(std::move(from.iteratorNative)), obj(std::move(from.obj)) {}

    SELF& operator=(const SELF& from) = delete;

    SELF& operator=(SELF&& from) {
        iteratorNative = std::move(from.iteratorNative);
        obj = std::move(from.obj);
        return *this;
    }

    bool operator==(const SELF& other) {
        return iteratorNative == other.iteratorNative;
    }

    bool operator!=(const SELF& other) {
        return !(*this == other);
    }

    SELF operator++(int) = delete;  // Just use ++it.

    SELF& operator++() {
        NATIVE_T* p = HELPER::next(iteratorNative.get());
        DriverException::check_and_throw();

        if (p == nullptr) {
            iteratorNative.reset();  // Makes it equal to end.
            obj.reset();
        } else {
            if constexpr (std::is_same_v<T, INSTANTIATER>){
                obj = std::move(INSTANTIATER(p));
            } else {
                obj = std::move(INSTANTIATER::instantiate(p));
            }
        }
        return *this;
    }

    T& operator*() {
        if ((*this) == SELF()) {
            throw DriverException(InternalError::ITERATOR_INVALIDATED.code, InternalError::ITERATOR_INVALIDATED.formatString);
        }
        assert(obj.has_value());
        return obj.value();
    }

    T* operator->() {
        if ((*this) == SELF()) {
            throw DriverException(InternalError::ITERATOR_INVALIDATED.code, InternalError::ITERATOR_INVALIDATED.formatString);
        }
        assert(obj.has_value());
        return &obj.value();
    }

private:
    Iterator()
        : iteratorNative(nullptr), obj() {}
    NativePointer<NATIVE_ITER> iteratorNative;
    std::optional<T> obj;

    friend class Iterable<T, TRAITS, INSTANTIATER>;
};

/**
 * \brief Result representing a stream of query results.
 *
 * Exposes <code>begin()</code> to get an iterator over the results and <code>end()</code> to check if the end has been reached.<br/>
 * Note: begin() must be called for any server-side exceptions encountered while evaluating the query to be thrown
 *
 * <h3>Examples</h3>
 * <pre>
 * for (auto& element : iterable) { ... }
 * for (auto it = iterable.begin(); it != iterable.end(); ++it ) { ... } // Note: it++ is deleted.
 * </pre>
 */
template <typename T, typename TRAITS = _native::NativeTraits<typename T::NativeElement>, class INSTANTIATER = T>
class Iterable {
    using SELF = Iterable<T, TRAITS, INSTANTIATER>;
    using ITERATOR = Iterator<T, TRAITS, INSTANTIATER>;
    using NATIVE_T = typename TRAITS::native_t;
    using HELPER = typename TRAITS::iterator;
    using NATIVE_ITER = typename HELPER::iterator_t;

public:
    Iterable(NATIVE_ITER* iteratorNative)
        : iteratorNative(iteratorNative, HELPER::drop) {}
    Iterable(SELF& from) = delete;
    Iterable(SELF&& from) {
        *this = std::move(from);
    }

    Iterable& operator=(const SELF& from) = delete;

    Iterable& operator=(SELF&& from) {
        iteratorNative = std::move(from.iteratorNative);
        return *this;
    }

    /**
     * Returns an iterator pointing to the first element.
     */
    ITERATOR begin() {
        ITERATOR it = ITERATOR(iteratorNative.release());
        ++it;  // initialises it
        return it;
    }

    /**
     * Returns an iterator equivalent to the result of advancing past the last element.
     */
    ITERATOR end() {
        return ITERATOR();
    }

private:
    NativePointer<NATIVE_ITER> iteratorNative;
};

using StringIterable = Iterable<std::string, _native::NativeTraits<char>>;
using StringIterator = Iterable<std::string, _native::NativeTraits<char>>;

}  // namespace TypeDB
