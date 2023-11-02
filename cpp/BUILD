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

load("@vaticle_dependencies//tool/checkstyle:rules.bzl", "checkstyle_test")

cc_library(
    name = "typedb-driver-cpp",
    srcs = glob([
        "lib/*/*.cpp", 
        "lib/inc/*.hpp"
    ]),
    hdrs = glob(["include/typedb/**/*"]), # exported public includes
    strip_include_prefix = "include",
    includes = ["lib/"], # private includes
    deps = [
        "//c:typedb_driver_clib",
        "//c:typedb_driver_clib_headers"
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "test-cpp-driver",
    srcs = ["test/integration/test.cpp"],
    deps = [
        ":typedb-driver-cpp",

        # External
        "@gtest//:gtest",
        "@gtest//:gtest_main"
    ],
    copts = ["-std=c++17"],
    env = {"RUST_BACKTRACE": "full"},
)

cc_binary(
    name = "test-behaviour-cucumber-server",
    srcs = glob(["test/features/step_definitions/**/*.cpp"]),
    deps = ["@cucumber_cpp//:cucumber-cpp"],
)

checkstyle_test(
    name = "checkstyle",
    size = "small",
    include = glob(["*/*"]),
    exclude = ["README.md"],
    license_type = "apache-header",
)
