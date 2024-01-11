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

workspace(name = "vaticle_typedb_driver")

##############################
# Load @vaticle_dependencies #
##############################

load("//dependencies/vaticle:repositories.bzl", "vaticle_dependencies")
vaticle_dependencies()

# Load //builder/bazel for RBE
load("@vaticle_dependencies//builder/bazel:deps.bzl", "bazel_toolchain")
bazel_toolchain()

# Load //builder/dotnet
load("@vaticle_dependencies//builder/dotnet:deps.bzl", dotnet_deps = "deps")
dotnet_deps()
load("@rules_dotnet//dotnet:repositories.bzl", "dotnet_register_toolchains", "rules_dotnet_dependencies")
rules_dotnet_dependencies()
dotnet_register_toolchains("dotnet", "7.0.101")
load("@rules_dotnet//dotnet:rules_dotnet_nuget_packages.bzl", "rules_dotnet_nuget_packages")
rules_dotnet_nuget_packages()
load("@rules_dotnet//dotnet:defs.bzl", "nuget_repo")
nuget_repo(
    name = "nuget-repo",
    packages = [ # TODO: Revise. This is taken from the bazel example
#            {"id": "Expecto", "version": "9.0.4", "sha512": "sha512-k0TT6pNIyzDaJD0ZxHDhNU0UmmWZlum2XFfHTGrkApQ+JUdjcoBqKOACXrSkfiLVYsD8Ww768eeAiKPP3QYetw==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": ["FSharp.Core", "Mono.Cecil"], "net462": ["FSharp.Core", "Mono.Cecil"], "net47": ["FSharp.Core", "Mono.Cecil"], "net471": ["FSharp.Core", "Mono.Cecil"], "net472": ["FSharp.Core", "Mono.Cecil"], "net48": ["FSharp.Core", "Mono.Cecil"], "net5.0": ["FSharp.Core", "Mono.Cecil"], "net6.0": ["FSharp.Core", "Mono.Cecil"], "net7.0": ["FSharp.Core", "Mono.Cecil"], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": ["FSharp.Core", "Mono.Cecil"], "netcoreapp2.1": ["FSharp.Core", "Mono.Cecil"], "netcoreapp2.2": ["FSharp.Core", "Mono.Cecil"], "netcoreapp3.0": ["FSharp.Core", "Mono.Cecil"], "netcoreapp3.1": ["FSharp.Core", "Mono.Cecil"], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": ["FSharp.Core", "Mono.Cecil"], "netstandard2.1": ["FSharp.Core", "Mono.Cecil"]}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "FSharp.Core", "version": "6.0.3", "sha512": "sha512-aDyKHiVFMwXWJrfW90iAeKyvw/lN+x98DPfx4oXke9Qnl4dz1sOi8KT2iczGeunqyWXh7nm+XUJ18i/0P3pZYw==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "FSharp.Data", "version": "5.0.2", "sha512": "sha512-BlDokqEWMysUMedhZzaREUPrhAbj8VRUEXjUrd85fzH63XaxppqjEYtpjQLnQcwkyWI71bzr3cfzYgaAANQLAQ==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": ["FSharp.Core"], "net462": ["FSharp.Core"], "net47": ["FSharp.Core"], "net471": ["FSharp.Core"], "net472": ["FSharp.Core"], "net48": ["FSharp.Core"], "net5.0": ["FSharp.Core"], "net6.0": ["FSharp.Core"], "net7.0": ["FSharp.Core"], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": ["FSharp.Core"], "netcoreapp2.1": ["FSharp.Core"], "netcoreapp2.2": ["FSharp.Core"], "netcoreapp3.0": ["FSharp.Core"], "netcoreapp3.1": ["FSharp.Core"], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": ["FSharp.Core"], "netstandard2.1": ["FSharp.Core"]}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Microsoft.AspNetCore.App.Ref", "version": "6.0.8", "sha512": "sha512-yLy7tFshfGLJRCFdlmOv8YOlJ4J5IfE88bnqiulxsJzhgEQNfbPQLpxbvmjCO3Zg0tdBLAS4B8QYWoojkOkWLg==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": ["Microsoft.Extensions.Caching.Abstractions|6.0.0", "Microsoft.Extensions.Caching.Memory|6.0.0", "Microsoft.Extensions.Configuration.Abstractions|6.0.0", "Microsoft.Extensions.Configuration.Binder|6.0.0", "Microsoft.Extensions.Configuration.CommandLine|6.0.0", "Microsoft.Extensions.Configuration|6.0.0", "Microsoft.Extensions.Configuration.EnvironmentVariables|6.0.0", "Microsoft.Extensions.Configuration.FileExtensions|6.0.0", "Microsoft.Extensions.Configuration.Ini|6.0.0", "Microsoft.Extensions.Configuration.Json|6.0.0", "Microsoft.Extensions.Configuration.UserSecrets|6.0.0", "Microsoft.Extensions.Configuration.Xml|6.0.0", "Microsoft.Extensions.DependencyInjection.Abstractions|6.0.0", "Microsoft.Extensions.DependencyInjection|6.0.0", "Microsoft.Extensions.FileProviders.Abstractions|6.0.0", "Microsoft.Extensions.FileProviders.Composite|6.0.0", "Microsoft.Extensions.FileProviders.Physical|6.0.0", "Microsoft.Extensions.FileSystemGlobbing|6.0.0", "Microsoft.Extensions.Hosting.Abstractions|6.0.0", "Microsoft.Extensions.Hosting|6.0.0", "Microsoft.Extensions.Http|6.0.0", "Microsoft.Extensions.Logging.Abstractions|6.0.0", "Microsoft.Extensions.Logging.Configuration|6.0.0", "Microsoft.Extensions.Logging.Console|6.0.0", "Microsoft.Extensions.Logging.Debug|6.0.0", "Microsoft.Extensions.Logging|6.0.0", "Microsoft.Extensions.Logging.EventLog|6.0.0", "Microsoft.Extensions.Logging.EventSource|6.0.0", "Microsoft.Extensions.Logging.TraceSource|6.0.0", "Microsoft.Extensions.Options.ConfigurationExtensions|6.0.0", "Microsoft.Extensions.Options.DataAnnotations|6.0.0", "Microsoft.Extensions.Options|6.0.0", "Microsoft.Extensions.Primitives|6.0.0", "System.Diagnostics.EventLog|6.0.0", "System.IO.Pipelines|6.0.0", "System.Security.Cryptography.Xml|6.0.0", "Microsoft.AspNetCore.Antiforgery|6.0.0", "Microsoft.AspNetCore.Authentication.Abstractions|6.0.0", "Microsoft.AspNetCore.Authentication.Cookies|6.0.0", "Microsoft.AspNetCore.Authentication.Core|6.0.0", "Microsoft.AspNetCore.Authentication|6.0.0", "Microsoft.AspNetCore.Authentication.OAuth|6.0.0", "Microsoft.AspNetCore.Authorization|6.0.0", "Microsoft.AspNetCore.Authorization.Policy|6.0.0", "Microsoft.AspNetCore.Components.Authorization|6.0.0", "Microsoft.AspNetCore.Components|6.0.0", "Microsoft.AspNetCore.Components.Forms|6.0.0", "Microsoft.AspNetCore.Components.Server|6.0.0", "Microsoft.AspNetCore.Components.Web|6.0.0", "Microsoft.AspNetCore.Connections.Abstractions|6.0.0", "Microsoft.AspNetCore.CookiePolicy|6.0.0", "Microsoft.AspNetCore.Cors|6.0.0", "Microsoft.AspNetCore.Cryptography.Internal|6.0.0", "Microsoft.AspNetCore.Cryptography.KeyDerivation|6.0.0", "Microsoft.AspNetCore.DataProtection.Abstractions|6.0.0", "Microsoft.AspNetCore.DataProtection|6.0.0", "Microsoft.AspNetCore.DataProtection.Extensions|6.0.0", "Microsoft.AspNetCore.Diagnostics.Abstractions|6.0.0", "Microsoft.AspNetCore.Diagnostics|6.0.0", "Microsoft.AspNetCore.Diagnostics.HealthChecks|6.0.0", "Microsoft.AspNetCore|6.0.0", "Microsoft.AspNetCore.HostFiltering|6.0.0", "Microsoft.AspNetCore.Hosting.Abstractions|6.0.0", "Microsoft.AspNetCore.Hosting|6.0.0", "Microsoft.AspNetCore.Hosting.Server.Abstractions|6.0.0", "Microsoft.AspNetCore.Html.Abstractions|6.0.0", "Microsoft.AspNetCore.Http.Abstractions|6.0.0", "Microsoft.AspNetCore.Http.Connections.Common|6.0.0", "Microsoft.AspNetCore.Http.Connections|6.0.0", "Microsoft.AspNetCore.Http|6.0.0", "Microsoft.AspNetCore.Http.Extensions|6.0.0", "Microsoft.AspNetCore.Http.Features|6.0.0", "Microsoft.AspNetCore.Http.Results|6.0.0", "Microsoft.AspNetCore.HttpLogging|6.0.0", "Microsoft.AspNetCore.HttpOverrides|6.0.0", "Microsoft.AspNetCore.HttpsPolicy|6.0.0", "Microsoft.AspNetCore.Identity|6.0.0", "Microsoft.AspNetCore.Localization|6.0.0", "Microsoft.AspNetCore.Localization.Routing|6.0.0", "Microsoft.AspNetCore.Metadata|6.0.0", "Microsoft.AspNetCore.Mvc.Abstractions|6.0.0", "Microsoft.AspNetCore.Mvc.ApiExplorer|6.0.0", "Microsoft.AspNetCore.Mvc.Core|6.0.0", "Microsoft.AspNetCore.Mvc.Cors|6.0.0", "Microsoft.AspNetCore.Mvc.DataAnnotations|6.0.0", "Microsoft.AspNetCore.Mvc|6.0.0", "Microsoft.AspNetCore.Mvc.Formatters.Json|6.0.0", "Microsoft.AspNetCore.Mvc.Formatters.Xml|6.0.0", "Microsoft.AspNetCore.Mvc.Localization|6.0.0", "Microsoft.AspNetCore.Mvc.Razor|6.0.0", "Microsoft.AspNetCore.Mvc.RazorPages|6.0.0", "Microsoft.AspNetCore.Mvc.TagHelpers|6.0.0", "Microsoft.AspNetCore.Mvc.ViewFeatures|6.0.0", "Microsoft.AspNetCore.Razor|6.0.0", "Microsoft.AspNetCore.Razor.Runtime|6.0.0", "Microsoft.AspNetCore.ResponseCaching.Abstractions|6.0.0", "Microsoft.AspNetCore.ResponseCaching|6.0.0", "Microsoft.AspNetCore.ResponseCompression|6.0.0", "Microsoft.AspNetCore.Rewrite|6.0.0", "Microsoft.AspNetCore.Routing.Abstractions|6.0.0", "Microsoft.AspNetCore.Routing|6.0.0", "Microsoft.AspNetCore.Server.HttpSys|6.0.0", "Microsoft.AspNetCore.Server.IIS|6.0.0", "Microsoft.AspNetCore.Server.IISIntegration|6.0.0", "Microsoft.AspNetCore.Server.Kestrel.Core|6.0.0", "Microsoft.AspNetCore.Server.Kestrel|6.0.0", "Microsoft.AspNetCore.Server.Kestrel.Transport.Quic|6.0.0", "Microsoft.AspNetCore.Server.Kestrel.Transport.Sockets|6.0.0", "Microsoft.AspNetCore.Session|6.0.0", "Microsoft.AspNetCore.SignalR.Common|6.0.0", "Microsoft.AspNetCore.SignalR.Core|6.0.0", "Microsoft.AspNetCore.SignalR|6.0.0", "Microsoft.AspNetCore.SignalR.Protocols.Json|6.0.0", "Microsoft.AspNetCore.StaticFiles|6.0.0", "Microsoft.AspNetCore.WebSockets|6.0.0", "Microsoft.AspNetCore.WebUtilities|6.0.0", "Microsoft.Extensions.Configuration.KeyPerFile|6.0.0", "Microsoft.Extensions.Diagnostics.HealthChecks.Abstractions|6.0.0", "Microsoft.Extensions.Diagnostics.HealthChecks|6.0.0", "Microsoft.Extensions.Features|6.0.0", "Microsoft.Extensions.FileProviders.Embedded|6.0.0", "Microsoft.Extensions.Identity.Core|6.0.0", "Microsoft.Extensions.Identity.Stores|6.0.0", "Microsoft.Extensions.Localization.Abstractions|6.0.0", "Microsoft.Extensions.Localization|6.0.0", "Microsoft.Extensions.ObjectPool|6.0.0", "Microsoft.Extensions.WebEncoders|6.0.0", "Microsoft.JSInterop|6.0.0", "Microsoft.Net.Http.Headers|6.0.0"], "framework_list": ["Microsoft.AspNetCore.Antiforgery|6.0.0.0", "Microsoft.AspNetCore.Authentication.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Authentication.Cookies|6.0.0.0", "Microsoft.AspNetCore.Authentication.Core|6.0.0.0", "Microsoft.AspNetCore.Authentication.OAuth|6.0.0.0", "Microsoft.AspNetCore.Authentication|6.0.0.0", "Microsoft.AspNetCore.Authorization.Policy|6.0.0.0", "Microsoft.AspNetCore.Authorization|6.0.0.0", "Microsoft.AspNetCore.Components.Authorization|6.0.0.0", "Microsoft.AspNetCore.Components.Forms|6.0.0.0", "Microsoft.AspNetCore.Components.Server|6.0.0.0", "Microsoft.AspNetCore.Components.Web|6.0.0.0", "Microsoft.AspNetCore.Components|6.0.0.0", "Microsoft.AspNetCore.Connections.Abstractions|6.0.0.0", "Microsoft.AspNetCore.CookiePolicy|6.0.0.0", "Microsoft.AspNetCore.Cors|6.0.0.0", "Microsoft.AspNetCore.Cryptography.Internal|6.0.0.0", "Microsoft.AspNetCore.Cryptography.KeyDerivation|6.0.0.0", "Microsoft.AspNetCore.DataProtection.Abstractions|6.0.0.0", "Microsoft.AspNetCore.DataProtection.Extensions|6.0.0.0", "Microsoft.AspNetCore.DataProtection|6.0.0.0", "Microsoft.AspNetCore.Diagnostics.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Diagnostics.HealthChecks|6.0.0.0", "Microsoft.AspNetCore.Diagnostics|6.0.0.0", "Microsoft.AspNetCore.HostFiltering|6.0.0.0", "Microsoft.AspNetCore.Hosting.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Hosting.Server.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Hosting|6.0.0.0", "Microsoft.AspNetCore.Html.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Http.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Http.Connections.Common|6.0.0.0", "Microsoft.AspNetCore.Http.Connections|6.0.0.0", "Microsoft.AspNetCore.Http.Extensions|6.0.0.0", "Microsoft.AspNetCore.Http.Features|6.0.0.0", "Microsoft.AspNetCore.Http.Results|6.0.0.0", "Microsoft.AspNetCore.Http|6.0.0.0", "Microsoft.AspNetCore.HttpLogging|6.0.0.0", "Microsoft.AspNetCore.HttpOverrides|6.0.0.0", "Microsoft.AspNetCore.HttpsPolicy|6.0.0.0", "Microsoft.AspNetCore.Identity|6.0.0.0", "Microsoft.AspNetCore.Localization.Routing|6.0.0.0", "Microsoft.AspNetCore.Localization|6.0.0.0", "Microsoft.AspNetCore.Metadata|6.0.0.0", "Microsoft.AspNetCore.Mvc.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Mvc.ApiExplorer|6.0.0.0", "Microsoft.AspNetCore.Mvc.Core|6.0.0.0", "Microsoft.AspNetCore.Mvc.Cors|6.0.0.0", "Microsoft.AspNetCore.Mvc.DataAnnotations|6.0.0.0", "Microsoft.AspNetCore.Mvc.Formatters.Json|6.0.0.0", "Microsoft.AspNetCore.Mvc.Formatters.Xml|6.0.0.0", "Microsoft.AspNetCore.Mvc.Localization|6.0.0.0", "Microsoft.AspNetCore.Mvc.Razor|6.0.0.0", "Microsoft.AspNetCore.Mvc.RazorPages|6.0.0.0", "Microsoft.AspNetCore.Mvc.TagHelpers|6.0.0.0", "Microsoft.AspNetCore.Mvc.ViewFeatures|6.0.0.0", "Microsoft.AspNetCore.Mvc|6.0.0.0", "Microsoft.AspNetCore.Razor.Runtime|6.0.0.0", "Microsoft.AspNetCore.Razor|6.0.0.0", "Microsoft.AspNetCore.ResponseCaching.Abstractions|6.0.0.0", "Microsoft.AspNetCore.ResponseCaching|6.0.0.0", "Microsoft.AspNetCore.ResponseCompression|6.0.0.0", "Microsoft.AspNetCore.Rewrite|6.0.0.0", "Microsoft.AspNetCore.Routing.Abstractions|6.0.0.0", "Microsoft.AspNetCore.Routing|6.0.0.0", "Microsoft.AspNetCore.Server.HttpSys|6.0.0.0", "Microsoft.AspNetCore.Server.IIS|6.0.0.0", "Microsoft.AspNetCore.Server.IISIntegration|6.0.0.0", "Microsoft.AspNetCore.Server.Kestrel.Core|6.0.0.0", "Microsoft.AspNetCore.Server.Kestrel.Transport.Quic|6.0.0.0", "Microsoft.AspNetCore.Server.Kestrel.Transport.Sockets|6.0.0.0", "Microsoft.AspNetCore.Server.Kestrel|6.0.0.0", "Microsoft.AspNetCore.Session|6.0.0.0", "Microsoft.AspNetCore.SignalR.Common|6.0.0.0", "Microsoft.AspNetCore.SignalR.Core|6.0.0.0", "Microsoft.AspNetCore.SignalR.Protocols.Json|6.0.0.0", "Microsoft.AspNetCore.SignalR|6.0.0.0", "Microsoft.AspNetCore.StaticFiles|6.0.0.0", "Microsoft.AspNetCore.WebSockets|6.0.0.0", "Microsoft.AspNetCore.WebUtilities|6.0.0.0", "Microsoft.AspNetCore|6.0.0.0", "Microsoft.Extensions.Caching.Abstractions|6.0.0.0", "Microsoft.Extensions.Caching.Memory|6.0.0.0", "Microsoft.Extensions.Configuration.Abstractions|6.0.0.0", "Microsoft.Extensions.Configuration.Binder|6.0.0.0", "Microsoft.Extensions.Configuration.CommandLine|6.0.0.0", "Microsoft.Extensions.Configuration.EnvironmentVariables|6.0.0.0", "Microsoft.Extensions.Configuration.FileExtensions|6.0.0.0", "Microsoft.Extensions.Configuration.Ini|6.0.0.0", "Microsoft.Extensions.Configuration.Json|6.0.0.0", "Microsoft.Extensions.Configuration.KeyPerFile|6.0.0.0", "Microsoft.Extensions.Configuration.UserSecrets|6.0.0.0", "Microsoft.Extensions.Configuration.Xml|6.0.0.0", "Microsoft.Extensions.Configuration|6.0.0.0", "Microsoft.Extensions.DependencyInjection.Abstractions|6.0.0.0", "Microsoft.Extensions.DependencyInjection|6.0.0.0", "Microsoft.Extensions.Diagnostics.HealthChecks.Abstractions|6.0.0.0", "Microsoft.Extensions.Diagnostics.HealthChecks|6.0.0.0", "Microsoft.Extensions.Features|6.0.0.0", "Microsoft.Extensions.FileProviders.Abstractions|6.0.0.0", "Microsoft.Extensions.FileProviders.Composite|6.0.0.0", "Microsoft.Extensions.FileProviders.Embedded|6.0.0.0", "Microsoft.Extensions.FileProviders.Physical|6.0.0.0", "Microsoft.Extensions.FileSystemGlobbing|6.0.0.0", "Microsoft.Extensions.Hosting.Abstractions|6.0.0.0", "Microsoft.Extensions.Hosting|6.0.0.0", "Microsoft.Extensions.Http|6.0.0.0", "Microsoft.Extensions.Identity.Core|6.0.0.0", "Microsoft.Extensions.Identity.Stores|6.0.0.0", "Microsoft.Extensions.Localization.Abstractions|6.0.0.0", "Microsoft.Extensions.Localization|6.0.0.0", "Microsoft.Extensions.Logging.Abstractions|6.0.0.0", "Microsoft.Extensions.Logging.Configuration|6.0.0.0", "Microsoft.Extensions.Logging.Console|6.0.0.0", "Microsoft.Extensions.Logging.Debug|6.0.0.0", "Microsoft.Extensions.Logging.EventLog|6.0.0.0", "Microsoft.Extensions.Logging.EventSource|6.0.0.0", "Microsoft.Extensions.Logging.TraceSource|6.0.0.0", "Microsoft.Extensions.Logging|6.0.0.0", "Microsoft.Extensions.ObjectPool|6.0.0.0", "Microsoft.Extensions.Options.ConfigurationExtensions|6.0.0.0", "Microsoft.Extensions.Options.DataAnnotations|6.0.0.0", "Microsoft.Extensions.Options|6.0.0.0", "Microsoft.Extensions.Primitives|6.0.0.0", "Microsoft.Extensions.WebEncoders|6.0.0.0", "Microsoft.JSInterop|6.0.0.0", "Microsoft.Net.Http.Headers|6.0.0.0", "System.Diagnostics.EventLog|6.0.0.0", "System.IO.Pipelines|6.0.0.0", "System.Security.Cryptography.Xml|6.0.0.0"]},
#            {"id": "Microsoft.AspNetCore.App.Runtime.linux-x64", "version": "6.0.8", "sha512": "sha512-3Hig5sP4ALm0aaB3cYCdhmW0a6SgT23ReaP5oYOZ9p1fQoQy4fHeLlU2LXQTXgJDopd3sQZCaWg639rJCYppiQ==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Microsoft.AspNetCore.App.Runtime.osx-x64", "version": "6.0.8", "sha512": "sha512-AQHu61cati6QzemklVlevQgChYJ3+msUUnXVDh51cEHhFEO/HBLKFWTiS1A49jnLBFpNUY98jPJMauyKIrh4jQ==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Microsoft.AspNetCore.App.Runtime.win-x64", "version": "6.0.8", "sha512": "sha512-fSuPkgA89T57pmGx2g6pcMSizT49ABL43d6s8Vp0PCzPjrme7UBISHATM9zP45Sq6GUhTZe2892wj7NmPa0wBA==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
            {"id": "Microsoft.NETCore.App.Ref", "version": "6.0.8", "sha512": "sha512-TcZWOpmw+hWGQANrK0YWS3oHvtxdkn5A5JB284IdgXNvQ4rGABOPK8u52qB2bATbpSy3DbiMdobRxgAB2/mcJQ==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": ["Microsoft.CSharp|4.4.0", "Microsoft.Win32.Primitives|4.3.0", "Microsoft.Win32.Registry|4.4.0", "runtime.debian.8-x64.runtime.native.System|4.3.0", "runtime.debian.8-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.debian.8-x64.runtime.native.System.Net.Http|4.3.0", "runtime.debian.8-x64.runtime.native.System.Net.Security|4.3.0", "runtime.debian.8-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.debian.8-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.fedora.23-x64.runtime.native.System|4.3.0", "runtime.fedora.23-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.fedora.23-x64.runtime.native.System.Net.Http|4.3.0", "runtime.fedora.23-x64.runtime.native.System.Net.Security|4.3.0", "runtime.fedora.23-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.fedora.23-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.fedora.24-x64.runtime.native.System|4.3.0", "runtime.fedora.24-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.fedora.24-x64.runtime.native.System.Net.Http|4.3.0", "runtime.fedora.24-x64.runtime.native.System.Net.Security|4.3.0", "runtime.fedora.24-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.fedora.24-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.opensuse.13.2-x64.runtime.native.System|4.3.0", "runtime.opensuse.13.2-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.opensuse.13.2-x64.runtime.native.System.Net.Http|4.3.0", "runtime.opensuse.13.2-x64.runtime.native.System.Net.Security|4.3.0", "runtime.opensuse.13.2-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.opensuse.13.2-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.opensuse.42.1-x64.runtime.native.System|4.3.0", "runtime.opensuse.42.1-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.opensuse.42.1-x64.runtime.native.System.Net.Http|4.3.0", "runtime.opensuse.42.1-x64.runtime.native.System.Net.Security|4.3.0", "runtime.opensuse.42.1-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.opensuse.42.1-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.osx.10.10-x64.runtime.native.System|4.3.0", "runtime.osx.10.10-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.osx.10.10-x64.runtime.native.System.Net.Http|4.3.0", "runtime.osx.10.10-x64.runtime.native.System.Net.Security|4.3.0", "runtime.osx.10.10-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.osx.10.10-x64.runtime.native.System.Security.Cryptography.Apple|4.3.0", "runtime.osx.10.10-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.rhel.7-x64.runtime.native.System|4.3.0", "runtime.rhel.7-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.rhel.7-x64.runtime.native.System.Net.Http|4.3.0", "runtime.rhel.7-x64.runtime.native.System.Net.Security|4.3.0", "runtime.rhel.7-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.rhel.7-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.ubuntu.14.04-x64.runtime.native.System|4.3.0", "runtime.ubuntu.14.04-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.ubuntu.14.04-x64.runtime.native.System.Net.Http|4.3.0", "runtime.ubuntu.14.04-x64.runtime.native.System.Net.Security|4.3.0", "runtime.ubuntu.14.04-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.ubuntu.14.04-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.ubuntu.16.04-x64.runtime.native.System|4.3.0", "runtime.ubuntu.16.04-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.ubuntu.16.04-x64.runtime.native.System.Net.Http|4.3.0", "runtime.ubuntu.16.04-x64.runtime.native.System.Net.Security|4.3.0", "runtime.ubuntu.16.04-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.ubuntu.16.04-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "runtime.ubuntu.16.10-x64.runtime.native.System|4.3.0", "runtime.ubuntu.16.10-x64.runtime.native.System.IO.Compression|4.3.0", "runtime.ubuntu.16.10-x64.runtime.native.System.Net.Http|4.3.0", "runtime.ubuntu.16.10-x64.runtime.native.System.Net.Security|4.3.0", "runtime.ubuntu.16.10-x64.runtime.native.System.Security.Cryptography|4.3.0", "runtime.ubuntu.16.10-x64.runtime.native.System.Security.Cryptography.OpenSsl|4.3.0", "System.AppContext|4.3.0", "System.Buffers|4.4.0", "System.Collections|4.3.0", "System.Collections.Concurrent|4.3.0", "System.Collections.Immutable|1.4.0", "System.Collections.NonGeneric|4.3.0", "System.Collections.Specialized|4.3.0", "System.ComponentModel|4.3.0", "System.ComponentModel.EventBasedAsync|4.3.0", "System.ComponentModel.Primitives|4.3.0", "System.ComponentModel.TypeConverter|4.3.0", "System.Console|4.3.0", "System.Data.Common|4.3.0", "System.Diagnostics.Contracts|4.3.0", "System.Diagnostics.Debug|4.3.0", "System.Diagnostics.DiagnosticSource|4.4.0", "System.Diagnostics.FileVersionInfo|4.3.0", "System.Diagnostics.Process|4.3.0", "System.Diagnostics.StackTrace|4.3.0", "System.Diagnostics.TextWriterTraceListener|4.3.0", "System.Diagnostics.Tools|4.3.0", "System.Diagnostics.TraceSource|4.3.0", "System.Diagnostics.Tracing|4.3.0", "System.Dynamic.Runtime|4.3.0", "System.Globalization|4.3.0", "System.Globalization.Calendars|4.3.0", "System.Globalization.Extensions|4.3.0", "System.IO|4.3.0", "System.IO.Compression|4.3.0", "System.IO.Compression.ZipFile|4.3.0", "System.IO.FileSystem|4.3.0", "System.IO.FileSystem.AccessControl|4.4.0", "System.IO.FileSystem.DriveInfo|4.3.0", "System.IO.FileSystem.Primitives|4.3.0", "System.IO.FileSystem.Watcher|4.3.0", "System.IO.IsolatedStorage|4.3.0", "System.IO.MemoryMappedFiles|4.3.0", "System.IO.Pipes|4.3.0", "System.IO.UnmanagedMemoryStream|4.3.0", "System.Linq|4.3.0", "System.Linq.Expressions|4.3.0", "System.Linq.Queryable|4.3.0", "System.Net.Http|4.3.0", "System.Net.NameResolution|4.3.0", "System.Net.Primitives|4.3.0", "System.Net.Requests|4.3.0", "System.Net.Security|4.3.0", "System.Net.Sockets|4.3.0", "System.Net.WebHeaderCollection|4.3.0", "System.ObjectModel|4.3.0", "System.Private.DataContractSerialization|4.3.0", "System.Reflection|4.3.0", "System.Reflection.Emit|4.3.0", "System.Reflection.Emit.ILGeneration|4.3.0", "System.Reflection.Emit.Lightweight|4.3.0", "System.Reflection.Extensions|4.3.0", "System.Reflection.Metadata|1.5.0", "System.Reflection.Primitives|4.3.0", "System.Reflection.TypeExtensions|4.3.0", "System.Resources.ResourceManager|4.3.0", "System.Runtime|4.3.0", "System.Runtime.Extensions|4.3.0", "System.Runtime.Handles|4.3.0", "System.Runtime.InteropServices|4.3.0", "System.Runtime.InteropServices.RuntimeInformation|4.3.0", "System.Runtime.Loader|4.3.0", "System.Runtime.Numerics|4.3.0", "System.Runtime.Serialization.Formatters|4.3.0", "System.Runtime.Serialization.Json|4.3.0", "System.Runtime.Serialization.Primitives|4.3.0", "System.Security.AccessControl|4.4.0", "System.Security.Claims|4.3.0", "System.Security.Cryptography.Algorithms|4.3.0", "System.Security.Cryptography.Cng|4.4.0", "System.Security.Cryptography.Csp|4.3.0", "System.Security.Cryptography.Encoding|4.3.0", "System.Security.Cryptography.OpenSsl|4.4.0", "System.Security.Cryptography.Primitives|4.3.0", "System.Security.Cryptography.X509Certificates|4.3.0", "System.Security.Cryptography.Xml|4.4.0", "System.Security.Principal|4.3.0", "System.Security.Principal.Windows|4.4.0", "System.Text.Encoding|4.3.0", "System.Text.Encoding.Extensions|4.3.0", "System.Text.RegularExpressions|4.3.0", "System.Threading|4.3.0", "System.Threading.Overlapped|4.3.0", "System.Threading.Tasks|4.3.0", "System.Threading.Tasks.Extensions|4.3.0", "System.Threading.Tasks.Parallel|4.3.0", "System.Threading.Thread|4.3.0", "System.Threading.ThreadPool|4.3.0", "System.Threading.Timer|4.3.0", "System.ValueTuple|4.3.0", "System.Xml.ReaderWriter|4.3.0", "System.Xml.XDocument|4.3.0", "System.Xml.XmlDocument|4.3.0", "System.Xml.XmlSerializer|4.3.0", "System.Xml.XPath|4.3.0", "System.Xml.XPath.XDocument|4.3.0"], "framework_list": ["Microsoft.CSharp|6.0.0.0", "Microsoft.VisualBasic.Core|11.0.0.0", "Microsoft.VisualBasic|10.0.0.0", "Microsoft.Win32.Primitives|6.0.0.0", "Microsoft.Win32.Registry|6.0.0.0", "System.AppContext|6.0.0.0", "System.Buffers|6.0.0.0", "System.Collections.Concurrent|6.0.0.0", "System.Collections.Immutable|6.0.0.0", "System.Collections.NonGeneric|6.0.0.0", "System.Collections.Specialized|6.0.0.0", "System.Collections|6.0.0.0", "System.ComponentModel.Annotations|6.0.0.0", "System.ComponentModel.DataAnnotations|4.0.0.0", "System.ComponentModel.EventBasedAsync|6.0.0.0", "System.ComponentModel.Primitives|6.0.0.0", "System.ComponentModel.TypeConverter|6.0.0.0", "System.ComponentModel|6.0.0.0", "System.Configuration|4.0.0.0", "System.Console|6.0.0.0", "System.Core|4.0.0.0", "System.Data.Common|6.0.0.0", "System.Data.DataSetExtensions|4.0.0.0", "System.Data|4.0.0.0", "System.Diagnostics.Contracts|6.0.0.0", "System.Diagnostics.Debug|6.0.0.0", "System.Diagnostics.DiagnosticSource|6.0.0.0", "System.Diagnostics.FileVersionInfo|6.0.0.0", "System.Diagnostics.Process|6.0.0.0", "System.Diagnostics.StackTrace|6.0.0.0", "System.Diagnostics.TextWriterTraceListener|6.0.0.0", "System.Diagnostics.Tools|6.0.0.0", "System.Diagnostics.TraceSource|6.0.0.0", "System.Diagnostics.Tracing|6.0.0.0", "System.Drawing.Primitives|6.0.0.0", "System.Drawing|4.0.0.0", "System.Dynamic.Runtime|6.0.0.0", "System.Formats.Asn1|6.0.0.0", "System.Globalization.Calendars|6.0.0.0", "System.Globalization.Extensions|6.0.0.0", "System.Globalization|6.0.0.0", "System.IO.Compression.Brotli|6.0.0.0", "System.IO.Compression.FileSystem|4.0.0.0", "System.IO.Compression.ZipFile|6.0.0.0", "System.IO.Compression|6.0.0.0", "System.IO.FileSystem.AccessControl|6.0.0.0", "System.IO.FileSystem.DriveInfo|6.0.0.0", "System.IO.FileSystem.Primitives|6.0.0.0", "System.IO.FileSystem.Watcher|6.0.0.0", "System.IO.FileSystem|6.0.0.0", "System.IO.IsolatedStorage|6.0.0.0", "System.IO.MemoryMappedFiles|6.0.0.0", "System.IO.Pipes.AccessControl|6.0.0.0", "System.IO.Pipes|6.0.0.0", "System.IO.UnmanagedMemoryStream|6.0.0.0", "System.IO|6.0.0.0", "System.Linq.Expressions|6.0.0.0", "System.Linq.Parallel|6.0.0.0", "System.Linq.Queryable|6.0.0.0", "System.Linq|6.0.0.0", "System.Memory|6.0.0.0", "System.Net.Http.Json|6.0.0.0", "System.Net.Http|6.0.0.0", "System.Net.HttpListener|6.0.0.0", "System.Net.Mail|6.0.0.0", "System.Net.NameResolution|6.0.0.0", "System.Net.NetworkInformation|6.0.0.0", "System.Net.Ping|6.0.0.0", "System.Net.Primitives|6.0.0.0", "System.Net.Requests|6.0.0.0", "System.Net.Security|6.0.0.0", "System.Net.ServicePoint|6.0.0.0", "System.Net.Sockets|6.0.0.0", "System.Net.WebClient|6.0.0.0", "System.Net.WebHeaderCollection|6.0.0.0", "System.Net.WebProxy|6.0.0.0", "System.Net.WebSockets.Client|6.0.0.0", "System.Net.WebSockets|6.0.0.0", "System.Net|4.0.0.0", "System.Numerics.Vectors|6.0.0.0", "System.Numerics|4.0.0.0", "System.ObjectModel|6.0.0.0", "System.Reflection.DispatchProxy|6.0.0.0", "System.Reflection.Emit.ILGeneration|6.0.0.0", "System.Reflection.Emit.Lightweight|6.0.0.0", "System.Reflection.Emit|6.0.0.0", "System.Reflection.Extensions|6.0.0.0", "System.Reflection.Metadata|6.0.0.0", "System.Reflection.Primitives|6.0.0.0", "System.Reflection.TypeExtensions|6.0.0.0", "System.Reflection|6.0.0.0", "System.Resources.Reader|6.0.0.0", "System.Resources.ResourceManager|6.0.0.0", "System.Resources.Writer|6.0.0.0", "System.Runtime.CompilerServices.Unsafe|6.0.0.0", "System.Runtime.CompilerServices.VisualC|6.0.0.0", "System.Runtime.Extensions|6.0.0.0", "System.Runtime.Handles|6.0.0.0", "System.Runtime.InteropServices.RuntimeInformation|6.0.0.0", "System.Runtime.InteropServices|6.0.0.0", "System.Runtime.Intrinsics|6.0.0.0", "System.Runtime.Loader|6.0.0.0", "System.Runtime.Numerics|6.0.0.0", "System.Runtime.Serialization.Formatters|6.0.0.0", "System.Runtime.Serialization.Json|6.0.0.0", "System.Runtime.Serialization.Primitives|6.0.0.0", "System.Runtime.Serialization.Xml|6.0.0.0", "System.Runtime.Serialization|4.0.0.0", "System.Runtime|6.0.0.0", "System.Security.AccessControl|6.0.0.0", "System.Security.Claims|6.0.0.0", "System.Security.Cryptography.Algorithms|6.0.0.0", "System.Security.Cryptography.Cng|6.0.0.0", "System.Security.Cryptography.Csp|6.0.0.0", "System.Security.Cryptography.Encoding|6.0.0.0", "System.Security.Cryptography.OpenSsl|6.0.0.0", "System.Security.Cryptography.Primitives|6.0.0.0", "System.Security.Cryptography.X509Certificates|6.0.0.0", "System.Security.Principal.Windows|6.0.0.0", "System.Security.Principal|6.0.0.0", "System.Security.SecureString|6.0.0.0", "System.Security|4.0.0.0", "System.ServiceModel.Web|4.0.0.0", "System.ServiceProcess|4.0.0.0", "System.Text.Encoding.CodePages|6.0.0.0", "System.Text.Encoding.Extensions|6.0.0.0", "System.Text.Encoding|6.0.0.0", "System.Text.Encodings.Web|6.0.0.0", "System.Text.Json|6.0.0.0", "System.Text.RegularExpressions|6.0.0.0", "System.Threading.Channels|6.0.0.0", "System.Threading.Overlapped|6.0.0.0", "System.Threading.Tasks.Dataflow|6.0.0.0", "System.Threading.Tasks.Extensions|6.0.0.0", "System.Threading.Tasks.Parallel|6.0.0.0", "System.Threading.Tasks|6.0.0.0", "System.Threading.Thread|6.0.0.0", "System.Threading.ThreadPool|6.0.0.0", "System.Threading.Timer|6.0.0.0", "System.Threading|6.0.0.0", "System.Transactions.Local|6.0.0.0", "System.Transactions|4.0.0.0", "System.ValueTuple|4.0.3.0", "System.Web.HttpUtility|6.0.0.0", "System.Web|4.0.0.0", "System.Windows|4.0.0.0", "System.Xml.Linq|4.0.0.0", "System.Xml.ReaderWriter|6.0.0.0", "System.Xml.Serialization|4.0.0.0", "System.Xml.XDocument|6.0.0.0", "System.Xml.XPath.XDocument|6.0.0.0", "System.Xml.XPath|6.0.0.0", "System.Xml.XmlDocument|6.0.0.0", "System.Xml.XmlSerializer|6.0.0.0", "System.Xml|4.0.0.0", "System|4.0.0.0", "WindowsBase|4.0.0.0", "mscorlib|4.0.0.0", "netstandard|2.1.0.0"]},
#            {"id": "Microsoft.NETCore.App.Runtime.linux-x64", "version": "6.0.8", "sha512": "sha512-cjVzAUiYxPv949mXl0IbwzSRq0xBTGcW3N619CUcCwe35Ma1C1Tg1nh75Xc+OEn5+eAMW/S66dy+kQhdc277tA==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Microsoft.NETCore.App.Runtime.osx-x64", "version": "6.0.8", "sha512": "sha512-RDOy3pzl0sutv5U3JAx23JWiw2UCoHAPNsCo35TA8MU2DM+LMDXN/lxi2cslot6GfFsxe0cYhclkEocHa2xMPQ==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Microsoft.NETCore.App.Runtime.win-x64", "version": "6.0.8", "sha512": "sha512-pgpxzvQPZzBPD1lWulgRO/aafBhSBLhqH+SrBD+sYSIu7eswlxE5icW/r8o60fNFKYVg0CFvrnmCut5YpTT27Q==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Microsoft.NETCore.Platforms", "version": "7.0.4", "sha512": "sha512-mcQWjuDBh4WHGG4WcBI0k025WAdA2afMm6fs42sm1f+3gRyNQUiuMVT5gAWNUGSHmlu6qn/TCnAQpfl4Gm6cBw==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "Mono.Cecil", "version": "0.11.4", "sha512": "sha512-CnjwUMmFHnScNG8e/4DRZQQX67H5ajekRDudmZ6Fy1jCLhyH1jjzbQCOEFhBLa2NjPWQpMF+RHdBJY8a7GgmlA==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": [], "net451": [], "net452": [], "net46": [], "net461": [], "net462": [], "net47": [], "net471": [], "net472": [], "net48": [], "net5.0": [], "net6.0": [], "net7.0": [], "netcoreapp1.0": [], "netcoreapp1.1": [], "netcoreapp2.0": [], "netcoreapp2.1": [], "netcoreapp2.2": [], "netcoreapp3.0": [], "netcoreapp3.1": [], "netstandard": [], "netstandard1.0": [], "netstandard1.1": [], "netstandard1.2": [], "netstandard1.3": [], "netstandard1.4": [], "netstandard1.5": [], "netstandard1.6": [], "netstandard2.0": [], "netstandard2.1": []}, "targeting_pack_overrides": [], "framework_list": []},
#            {"id": "NETStandard.Library", "version": "2.0.3", "sha512": "sha512-548M6mnBSJWxsIlkQHfbzoYxpiYFXZZSL00p4GHYv8PkiqFBnnT68mW5mGEsA/ch9fDO9GkPgkFQpWiXZN7mAQ==", "sources": ["https://api.nuget.org/v3/index.json"], "dependencies": {"net11": [], "net20": [], "net30": [], "net35": [], "net40": [], "net403": [], "net45": ["Microsoft.NETCore.Platforms"], "net451": ["Microsoft.NETCore.Platforms"], "net452": ["Microsoft.NETCore.Platforms"], "net46": ["Microsoft.NETCore.Platforms"], "net461": ["Microsoft.NETCore.Platforms"], "net462": ["Microsoft.NETCore.Platforms"], "net47": ["Microsoft.NETCore.Platforms"], "net471": ["Microsoft.NETCore.Platforms"], "net472": ["Microsoft.NETCore.Platforms"], "net48": ["Microsoft.NETCore.Platforms"], "net5.0": ["Microsoft.NETCore.Platforms"], "net6.0": ["Microsoft.NETCore.Platforms"], "net7.0": ["Microsoft.NETCore.Platforms"], "netcoreapp1.0": ["Microsoft.NETCore.Platforms"], "netcoreapp1.1": ["Microsoft.NETCore.Platforms"], "netcoreapp2.0": ["Microsoft.NETCore.Platforms"], "netcoreapp2.1": ["Microsoft.NETCore.Platforms"], "netcoreapp2.2": ["Microsoft.NETCore.Platforms"], "netcoreapp3.0": ["Microsoft.NETCore.Platforms"], "netcoreapp3.1": ["Microsoft.NETCore.Platforms"], "netstandard": [], "netstandard1.0": ["Microsoft.NETCore.Platforms"], "netstandard1.1": ["Microsoft.NETCore.Platforms"], "netstandard1.2": ["Microsoft.NETCore.Platforms"], "netstandard1.3": ["Microsoft.NETCore.Platforms"], "netstandard1.4": ["Microsoft.NETCore.Platforms"], "netstandard1.5": ["Microsoft.NETCore.Platforms"], "netstandard1.6": ["Microsoft.NETCore.Platforms"], "netstandard2.0": ["Microsoft.NETCore.Platforms"], "netstandard2.1": ["Microsoft.NETCore.Platforms"]}, "targeting_pack_overrides": [], "framework_list": []},
        ],
)

# Load //builder/python
load("@vaticle_dependencies//builder/python:deps.bzl", python_deps = "deps")
python_deps()
load("@rules_python//python:repositories.bzl", "py_repositories", "python_register_toolchains")
py_repositories()
load("//python:python_versions.bzl", "register_all_toolchains")
register_all_toolchains()

# Load //builder/java
load("@vaticle_dependencies//builder/java:deps.bzl", java_deps = "deps")
java_deps()

# Load //builder/kotlin
load("@vaticle_dependencies//builder/kotlin:deps.bzl", kotlin_deps = "deps")
kotlin_deps()
load("@io_bazel_rules_kotlin//kotlin:repositories.bzl", "kotlin_repositories")
kotlin_repositories()
load("@io_bazel_rules_kotlin//kotlin:core.bzl", "kt_register_toolchains")
kt_register_toolchains()

# Load //builder/antlr
load("@vaticle_dependencies//builder/antlr:deps.bzl", antlr_deps = "deps", "antlr_version")
antlr_deps()

load("@rules_antlr//antlr:lang.bzl", "JAVA")
load("@rules_antlr//antlr:repositories.bzl", "rules_antlr_dependencies")
rules_antlr_dependencies(antlr_version, JAVA)

# Load //builder/cpp
load("@vaticle_dependencies//builder/cpp:deps.bzl", cpp_deps = "deps")
cpp_deps()

# Load //builder/proto_grpc
load("@vaticle_dependencies//builder/proto_grpc:deps.bzl", grpc_deps = "deps")
grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", com_github_grpc_grpc_deps = "grpc_deps")
com_github_grpc_grpc_deps()

# Load //builder/rust
load("@vaticle_dependencies//builder/rust:deps.bzl", rust_deps = "deps")
rust_deps()

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies", "rust_register_toolchains", "rust_analyzer_toolchain_tools_repository")
rules_rust_dependencies()
load("@rules_rust//tools/rust_analyzer:deps.bzl", "rust_analyzer_dependencies")
rust_analyzer_dependencies()
load("@rules_rust//rust:defs.bzl", "rust_common")
rust_register_toolchains(
    edition = "2021",
    extra_target_triples = [
        "aarch64-apple-darwin",
        "aarch64-unknown-linux-gnu",
        "x86_64-apple-darwin",
        "x86_64-pc-windows-msvc",
        "x86_64-unknown-linux-gnu",
    ],
    rust_analyzer_version = rust_common.default_version,
)

rust_analyzer_toolchain_tools_repository(
    name = "rust_analyzer_toolchain_tools",
    version = rust_common.default_version
)

load("@vaticle_dependencies//library/crates:crates.bzl", "fetch_crates")
fetch_crates()
load("@crates//:defs.bzl", "crate_repositories")
crate_repositories()

load("@vaticle_dependencies//tool/swig:deps.bzl", swig_deps = "deps")
swig_deps()

# Load //tool/common
load("@vaticle_dependencies//tool/common:deps.bzl", "vaticle_dependencies_ci_pip")
vaticle_dependencies_ci_pip()
load("@vaticle_dependencies_ci_pip//:requirements.bzl", "install_deps")
install_deps()

# Load //tool/checkstyle
load("@vaticle_dependencies//tool/checkstyle:deps.bzl", checkstyle_deps = "deps")
checkstyle_deps()

# Load //tool/sonarcloud
load("@vaticle_dependencies//tool/sonarcloud:deps.bzl", "sonarcloud_dependencies")
sonarcloud_dependencies()

# Load //tool/unuseddeps
load("@vaticle_dependencies//tool/unuseddeps:deps.bzl", unuseddeps_deps = "deps")
unuseddeps_deps()

# Load //tool/docs
load("@vaticle_dependencies//tool/docs:python_deps.bzl", docs_deps = "deps")
docs_deps()
load("@vaticle_dependencies_tool_docs//:requirements.bzl", install_doc_deps = "install_deps")
install_doc_deps()

load("@vaticle_dependencies//tool/docs:java_deps.bzl", java_doc_deps = "deps")
java_doc_deps()
load("@google_bazel_common//:workspace_defs.bzl", "google_common_workspace_rules")
google_common_workspace_rules()

####################################
# Load @vaticle_bazel_distribution #
####################################

load("@vaticle_dependencies//distribution:deps.bzl", "vaticle_bazel_distribution")
vaticle_bazel_distribution()

# Load //common
load("@vaticle_bazel_distribution//common:deps.bzl", "rules_pkg")
rules_pkg()
load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")
rules_pkg_dependencies()

# Load //github
load("@vaticle_bazel_distribution//github:deps.bzl", github_deps = "deps")
github_deps()

# Load //pip
load("@vaticle_bazel_distribution//pip:deps.bzl", pip_deps = "deps")
pip_deps()
load("@vaticle_bazel_distribution_pip//:requirements.bzl", install_pip_deps = "install_deps")
install_pip_deps()

######################################
# Load @vaticle_typedb_driver_python #
######################################

load("@rules_python//python:pip.bzl", "pip_parse")
pip_parse(
    name = "vaticle_typedb_driver_pip",
    requirements_lock = "//python:requirements_dev.txt",
)
load("@vaticle_typedb_driver_pip//:requirements.bzl", "install_deps")
install_deps()

##############################
# Load @vaticle dependencies #
##############################

# Load repositories
load("//dependencies/vaticle:repositories.bzl", "vaticle_typedb_common", "vaticle_typeql", "vaticle_typedb_behaviour", "vaticle_typedb_protocol")
vaticle_typedb_common()
vaticle_typeql()
vaticle_typedb_behaviour()
vaticle_typedb_protocol()

# Load artifacts
load("//dependencies/vaticle:artifacts.bzl", "vaticle_typedb_artifact", "vaticle_typedb_cloud_artifact")
vaticle_typedb_artifact()
vaticle_typedb_cloud_artifact()

####################
# Load npm modules #
####################

# Load //builder/nodejs
load("@vaticle_dependencies//builder/nodejs:deps.bzl", nodejs_deps = "deps")
nodejs_deps()

load("@aspect_rules_js//js:repositories.bzl", "rules_js_dependencies")
rules_js_dependencies()

load("@rules_nodejs//nodejs:repositories.bzl", "DEFAULT_NODE_VERSION", "nodejs_register_toolchains")
nodejs_register_toolchains(
    name = "nodejs",
    node_version = DEFAULT_NODE_VERSION,
)

load("@aspect_rules_js//npm:repositories.bzl", "npm_translate_lock")

npm_translate_lock(
    name = "vaticle_typedb_protocol_npm",
    bins = {
        "protoc-gen-ts": {
            "protoc-gen-ts-js": "./bin/protoc-gen-ts.js",
        },
    },
    pnpm_lock = "@vaticle_typedb_protocol//grpc/nodejs:pnpm-lock.yaml",
)

npm_translate_lock(
    name = "npm",
    bins = {
        "@cucumber/cucumber": {
            "cucumber-js": "./bin/cucumber-js",
        },
    },
    pnpm_lock = "//nodejs:pnpm-lock.yaml",
)

load("@npm//:repositories.bzl", "npm_repositories")
npm_repositories()

load("@vaticle_typedb_protocol_npm//:repositories.bzl", vaticle_typedb_protocol_npm_repositories = "npm_repositories")
vaticle_typedb_protocol_npm_repositories()

# Setup rules_ts
load("@aspect_rules_ts//ts:repositories.bzl", "rules_ts_dependencies")

rules_ts_dependencies(
    ts_version_from = "//nodejs:package.json",
)

load("@aspect_bazel_lib//lib:repositories.bzl", "register_jq_toolchains")
register_jq_toolchains()

###############
# Load @maven #
###############

# Load maven artifacts
load("@vaticle_dependencies//tool/common:deps.bzl", vaticle_dependencies_tool_maven_artifacts = "maven_artifacts")
load("@vaticle_typedb_common//dependencies/maven:artifacts.bzl", vaticle_typedb_common_maven_artifacts = "artifacts")
load("@vaticle_typeql//dependencies/maven:artifacts.bzl", vaticle_typeql_maven_artifacts = "artifacts")
load("//dependencies/maven:artifacts.bzl", vaticle_typedb_driver_java_maven_artifacts = "artifacts", vaticle_typedb_driver_java_maven_overrides = "overrides")
load("@vaticle_bazel_distribution//maven:deps.bzl", vaticle_bazel_distribution_maven_artifacts = "maven_artifacts")

load("@vaticle_dependencies//library/maven:rules.bzl", "maven")
maven(
    vaticle_typedb_common_maven_artifacts +
    vaticle_typeql_maven_artifacts +
    vaticle_dependencies_tool_maven_artifacts +
    vaticle_typedb_driver_java_maven_artifacts +
    vaticle_bazel_distribution_maven_artifacts,
    vaticle_typedb_driver_java_maven_overrides
)

################################################
# Create @vaticle_typedb_driver_workspace_refs #
################################################
load("@vaticle_bazel_distribution//common:rules.bzl", "workspace_refs")
workspace_refs(
    name = "vaticle_typedb_driver_workspace_refs"
)
