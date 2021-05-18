/*
 * Copyright (C) 2021 Vaticle
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

import {When} from "@cucumber/cucumber";
import {get, put} from "../ThingSteps";
import {tx} from "../../../connection/ConnectionStepsBase";
import {AttributeType} from "../../../../../dist/api/concept/type/AttributeType";
import {Attribute,} from "../../../../../dist/api/concept/thing/Attribute";
import {assertThrows} from "../../../util/Util";
import assert = require("assert");
import ValueType = AttributeType.ValueType;
import ValueClass = AttributeType.ValueClass;

When("attribute\\({type_label}) get instances contain: {var}", async (typeLabel: string, var0: string) => {
    assert(await (await tx().concepts().getAttributeType(typeLabel)).asRemote(tx()).getInstances().some(x => x.equals(get(var0))));
});

When("attribute {var} get owners contain: {var}", async (var1: string, var2: string) => {
    assert(await (get(var1) as Attribute<ValueClass>).asRemote(tx()).getOwners().some(x => x.equals(get(var2))));
});

When("attribute {var} get owners do not contain: {var}", async (var1: string, var2: string) => {
    assert(!(await (get(var1) as Attribute<ValueClass>).asRemote(tx()).getOwners().some(x => x.equals(get(var2)))));
});

When("attribute {var} has value type: {value_type}", async (var0: string, valueType: ValueType) => {
    assert.strictEqual(valueType, (get(var0) as Attribute<ValueClass>).getType().getValueType());
});

When("{var} = attribute\\({type_label}) as\\(boolean) put: {bool}", async (var0: string, typeLabel: string, value: boolean) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Boolean).asRemote(tx()).put(value))
});

When("attribute\\({type_label}) as\\(boolean) put: {bool}; throws exception", async (typeLabel: string, value: boolean) => {
    await assertThrows(async () => await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Boolean).asRemote(tx()).put(value))
});

When("{var} = attribute\\({type_label}) as\\(long) put: {int}", async (var0: string, typeLabel: string, value: number) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Long).asRemote(tx()).put(value))
});

When("attribute\\({type_label}) as\\(long) put: {int}; throws exception", async (typeLabel: string, value: number) => {
    await assertThrows(async () => await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Long).asRemote(tx()).put(value))
});

When("{var} = attribute\\({type_label}) as\\(double) put: {float}", async (var0: string, typeLabel: string, value: number) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Double).asRemote(tx()).put(value))
});

When("attribute\\({type_label}) as\\(double) put: {float}; throws exception", async (typeLabel: string, value: number) => {
    await assertThrows(async () => await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Double).asRemote(tx()).put(value))
});

When("{var} = attribute\\({type_label}) as\\(string) put: {word}", async (var0: string, typeLabel: string, value: string) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.String).asRemote(tx()).put(value))
});

When("attribute\\({type_label}) as\\(string) put: {word}; throws exception", async (typeLabel: string, value: string) => {
    await assertThrows(async () => await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.String).asRemote(tx()).put(value))
});

When("{var} = attribute\\({type_label}) as\\(datetime) put: {datetime}", async (var0: string, typeLabel: string, value: Date) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.DateTime).asRemote(tx()).put(value))
});

When("attribute\\({type_label}) as\\(datetime) put: {datetime}; throws exception", async (typeLabel: string, value: Date) => {
    await assertThrows(async () => await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.DateTime).asRemote(tx()).put(value))
});

When("{var} = attribute\\({type_label}) as\\(boolean) get: {bool}", async (var0: string, typeLabel: string, value: boolean) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Boolean).asRemote(tx()).get(value))
});

When("{var} = attribute\\({type_label}) as\\(long) get: {int}", async (var0: string, typeLabel: string, value: number) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Long).asRemote(tx()).get(value))
});

When("{var} = attribute\\({type_label}) as\\(double) get: {float}", async (var0: string, typeLabel: string, value: number) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.Double).asRemote(tx()).get(value))
});

When("{var} = attribute\\({type_label}) as\\(string) get: {word}", async (var0: string, typeLabel: string, value: string) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.String).asRemote(tx()).get(value))
});

When("{var} = attribute\\({type_label}) as\\(datetime) get: {datetime}", async (var0: string, typeLabel: string, value: Date) => {
    put(var0, await ((await tx().concepts().getAttributeType(typeLabel)) as AttributeType.DateTime).asRemote(tx()).get(value))
});

When("attribute {var} has boolean value: {bool}", async (var0: string, value: boolean) => {
    assert.strictEqual(value, (get(var0) as Attribute.Boolean).getValue())
});

When("attribute {var} has long value: {int}", async (var0: string, value: number) => {
    assert.strictEqual(value, (get(var0) as Attribute.Long).getValue())
});

When("attribute {var} has double value: {float}", async (var0: string, value: number) => {
    assert.strictEqual(value, (get(var0) as Attribute.Double).getValue())
});

When("attribute {var} has string value: {word}", async (var0: string, value: string) => {
    assert.strictEqual(value, (get(var0) as Attribute.String).getValue())
});

When("attribute {var} has datetime value: {datetime}", async (var0: string, value: Date) => {
    assert.strictEqual(value.getTime(), (get(var0) as Attribute.DateTime).getValue().getTime())
});
