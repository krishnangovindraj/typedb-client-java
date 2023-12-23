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

#include "typedb/answer/concept_map.hpp"
#include "typedb/common/iterator.hpp"
#include "typedb/common/native.hpp"
#include "typedb/concept/concept.hpp"

namespace TypeDB {

/**
 * \brief Contains an element of the group query result.
 */
class ConceptMapGroup {
public:
    using NativeIterator = _native::ConceptMapGroupIterator;
    using NativeElement = _native::ConceptMapGroup;

    ConceptMapGroup(const ConceptMapGroup&) = delete;
    ConceptMapGroup(ConceptMapGroup&&) = default;

    ConceptMapGroup& operator=(const ConceptMapGroup&) = delete;
    ConceptMapGroup& operator=(ConceptMapGroup&&) = default;
    ~ConceptMapGroup() = default;

    /**
     * Retrieves the concept that is the group owner.
     *
     * <h3>Examples</h3>
     * <pre>
     * conceptMapGroup.owner();
     * </pre>
     */
    std::unique_ptr<Concept> owner();

    /**
     * Retrieves the <code>ConceptMap</code>s of the group.
     *
     * <h3>Examples</h3>
     * <pre>
     * conceptMapGroup.conceptMaps();
     * </pre>
     */
    ConceptMapIterable conceptMaps();

    /**
     * A string representation of this ConceptMapGroup.
     */
    std::string toString();

private:
    NativePointer<_native::ConceptMapGroup> conceptMapGroupNative;

    ConceptMapGroup(_native::ConceptMapGroup*);

    friend class Iterator<TypeDB::ConceptMapGroup, _native::NativeTraits<_native::ConceptMapGroup>, TypeDB::ConceptMapGroup>;
};

// For ConceptMapGroup
using ConceptMapGroupIterable = Iterable<TypeDB::ConceptMapGroup>;

}  // namespace TypeDB
