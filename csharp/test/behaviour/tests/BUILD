#
# Copyright (C) 2022 Vaticle
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

load("@rules_dotnet//dotnet:defs.bzl", "csharp_test", "csharp_nunit_test")
package(default_visibility = ["//visibility:public"])

csharp_nunit_test(
    name = "hello-test",
    srcs = ["HelloSteps.cs"],
    target_frameworks = ["net6.0"],
    runtime_identifier = "osx-arm64",
    targeting_packs = [
        "@paket.standard_deps//microsoft.netcore.app.ref",
        "@paket.bdd_deps//specflow"
    ],
    deps = ["//csharp:hello-lib"]
)
