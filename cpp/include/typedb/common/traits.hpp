// /*
//  * Copyright (C) 2022 Vaticle
//  *
//  * Licensed to the Apache Software Foundation (ASF) under one
//  * or more contributor license agreements.  See the NOTICE file
//  * distributed with this work for additional information
//  * regarding copyright ownership.  The ASF licenses this file
//  * to you under the Apache License, Version 2.0 (the
//  * "License"); you may not use this file except in compliance
//  * with the License.  You may obtain a copy of the License at
//  *
//  *   http://www.apache.org/licenses/LICENSE-2.0
//  *
//  * Unless required by applicable law or agreed to in writing,
//  * software distributed under the License is distributed on an
//  * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//  * KIND, either express or implied.  See the License for the
//  * specific language governing permissions and limitations
//  * under the License.
//  */

// #include <string>
// #include "typedb/common/native.hpp"

// namespace TypeDB {

// /**
//  * \private
//  */
// template <typename NATIVE_ITER, typename NATIVE_T, typename T>
// class IteratorHelper {
//     using SELF = IteratorHelper<NATIVE_ITER, NATIVE_T, T>;
// public:
//     static void nativeIterDrop(NATIVE_ITER* it);
//     static NATIVE_T* nativeIterNext(NATIVE_ITER* it);
//     static T instantiate(NATIVE_T* element);
// };

// template <typename T> 
// struct StandardIteratorTraits {
//     typedef typename T::NativeIterator NativeIterator;
//     typedef typename T::NativeElement NativeElement;
//     typedef IteratorHelper<NativeIterator, NativeElement, T> NativeInterface;
// };

// }
