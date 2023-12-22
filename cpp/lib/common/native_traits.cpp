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

#include "typedb/common/native.hpp"
#include "typedb/common/native_traits.hpp"

#include "./native.hpp"

#include <iostream>

namespace TypeDB {

using namespace TypeDB::_native;
#define FREE(T, FN) template <> void DropImpl<T>::operator()(T* p) { FN(p); }
#define FUTURE(T, F, RESOLVE) template <> T* FutureImpl<T, F>::resolve(F* p) { return RESOLVE(p); }
#define ITERATOR(T, I, NEXT, DROP_I) \
    template <> T* IteratorImpl<T, I>::next(I* p) { return NEXT(p); } \
    template <> void IteratorImpl<T, I>::drop(I* p) { DROP_I(p); }


void lie(char* c) {
    std::cout << "lie: " << c << std::endl;
}

FREE(char, lie);//_native::string_free);

FREE(Annotation, _native::annotation_drop);
FREE(Concept, _native::concept_drop);
FREE(ConceptMap, _native::concept_map_drop);
FREE(ConceptMapGroup, _native::concept_map_group_drop);
FREE(Connection, _native::connection_close);
FREE(Credential, _native::credential_drop);
FREE(Database, _native::database_close);
FREE(DatabaseManager, _native::database_manager_drop);
FREE(Error, _native::error_drop);
FREE(Explainable, _native::explainable_drop);
FREE(Explainables, _native::explainables_drop);
FREE(Explanation, _native::explanation_drop);
FREE(Options, _native::options_drop);
FREE(ReplicaInfo, _native::replica_info_drop);
FREE(RolePlayer, _native::role_player_drop);
FREE(Rule, _native::rule_drop);
FREE(SchemaException, _native::schema_exception_drop);
FREE(Session, _native::session_close);
FREE(Transaction, _native::transaction_close);
FREE(User, _native::user_drop);
FREE(UserManager, _native::user_manager_drop);
FREE(ValueGroup, _native::value_group_drop);
FREE(StringPair, _native::string_pair_drop);

// Iterators. TODO: Do we want this here?
ITERATOR(RolePlayer, RolePlayerIterator, _native::role_player_iterator_next, _native::role_player_iterator_drop);
ITERATOR(ReplicaInfo, ReplicaInfoIterator, _native::replica_info_iterator_next, _native::replica_info_iterator_drop);
ITERATOR(Concept, ConceptIterator, _native::concept_iterator_next, _native::concept_iterator_drop);
ITERATOR(ConceptMapGroup, ConceptMapGroupIterator, _native::concept_map_group_iterator_next, _native::concept_map_group_iterator_drop);
ITERATOR(ConceptMap, ConceptMapIterator, _native::concept_map_iterator_next, _native::concept_map_iterator_drop);
ITERATOR(Database, DatabaseIterator, _native::database_iterator_next, _native::database_iterator_drop);
ITERATOR(Explanation, ExplanationIterator, _native::explanation_iterator_next, _native::explanation_iterator_drop);
ITERATOR(Rule, RuleIterator, _native::rule_iterator_next, _native::rule_iterator_drop);
ITERATOR(SchemaException, SchemaExceptionIterator, _native::schema_exception_iterator_next, _native::schema_exception_iterator_drop);
ITERATOR(char, StringIterator, _native::string_iterator_next, _native::string_iterator_drop);
ITERATOR(StringPair, StringPairIterator, _native::string_pair_iterator_next, _native::string_pair_iterator_drop);
ITERATOR(User, UserIterator, _native::user_iterator_next, _native::user_iterator_drop);
ITERATOR(ValueGroup, ValueGroupIterator, _native::value_group_iterator_next, _native::value_group_iterator_drop);

// Future
FUTURE(Concept, ConceptPromise, _native::concept_promise_resolve);
FUTURE(Rule, RulePromise, _native::rule_promise_resolve);
FUTURE(char, StringPromise, _native::string_promise_resolve);

// TODO: Implement differently
// FUTURE(void, VoidPromise, _native::void_promise_resolve);FUTURE(void, VoidPromise, _native::void_promise_resolve);

};