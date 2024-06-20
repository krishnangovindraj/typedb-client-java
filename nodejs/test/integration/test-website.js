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

const {TypeDB, SessionType, TransactionType, Concept, ThingType} = require("../../dist");
const assert = require("assert");
const Annotation = ThingType.Annotation;

async function run() {

    try {
        try {
            driver_setup = await TypeDB.coreDriver();
            accessManagementSchema = "define user sub entity;";
            accessManagementDataBatches = [["insert $u isa user;"]]
            if (await driver_setup.databases.contains("access-management-db")) await (await driver_setup.databases.get("access-management-db")).delete()

            console.log("Complete setup")
        } finally {
            if (driver_setup) await driver_setup.close()
        }
        // ---- START WEBSITE SNIPPET ----
        let driver, session, tx;
        try {
            driver = await TypeDB.coreDriver("localhost:1729");
            await driver.databases.create("access-management-db");

            session = await driver.session("access-management-db", SessionType.SCHEMA);
            tx = await session.transaction(TransactionType.WRITE);
            tx.query.define(accessManagementSchema);
            await tx.commit();
            await session.close();

            session = await driver.session("access-management-db", SessionType.DATA);
            for (const batch of accessManagementDataBatches) {
                tx = await session.transaction(TransactionType.WRITE);
                for (const query of batch) {
                    tx.query.insert(query);
                }
                await tx.commit();
            }
            tx = await session.transaction(TransactionType.READ);
            const results = tx.query.get("match $u isa user; get;");
        } finally {
            if (tx) await tx.close();
            if (session) await session.close();
            if (driver) await driver.close();
        }

        // ---- END WEBSITE SNIPPET ----

    } catch (err) {
        console.log("OUTER ERROR: " + err)
    }

   try {

        try {
            tx = null
            driver_setup = await TypeDB.coreDriver();
            accessManagementSchema = "define employee sub entity, owns email, owns name; contractor sub entity; name sub attribute, value string; email sub attribute, value string;"
            if (await driver_setup.databases.contains("access-management-db")) await (await driver_setup.databases.get("access-management-db")).delete()
            await driver_setup.databases.create("access-management-db")
            session = await driver_setup.session("access-management-db", SessionType.SCHEMA);
            tx = await session.transaction(TransactionType.WRITE);
            await tx.query.define(accessManagementSchema)
            await tx.commit()
            console.log("Complete setup")
        } finally {
            if (tx) await tx.close();
            if (session) await session.close();
            if (driver_setup) await driver_setup.close()
        }

        // ---- START WEBSITE SNIPPET ----
        try {
            driver = await TypeDB.coreDriver("localhost:1729");
            session = await driver.session("access-management-db", SessionType.SCHEMA);
            tx = await session.transaction(TransactionType.WRITE);

            // create a new abstract type "user"
            let user = await tx.concepts.putEntityType("user");
            await user.setAbstract(tx);

            // change the supertype of "employee" to "user"
            let employee = await tx.concepts.getEntityType("employee");
            await employee.setSupertype(tx, user);

            // change the supertype of "contractor" to "user"
            let contractor = await tx.concepts.getEntityType("contractor");
            await contractor.setSupertype(tx, user);

            // move "email" and "name" attribute types to be owned by "user" instead of "employee"
            let email = await tx.concepts.getAttributeType("email");
            let name = await tx.concepts.getAttributeType("name");
            await employee.unsetOwns(tx, email);
            await employee.unsetOwns(tx, name);
            await user.setOwns(tx, email);
            await user.setOwns(tx, name);

            // rename "name" attribute type to "full-name"
            await name.setLabel(tx, "full-name");

            // commit all schema changes in one transaction, which will fail if we violate any data validation
            await tx.commit()
        }  finally {
            if (tx) await tx.close();
            if (session) await session.close();
            if (driver) await driver.close();
        }
        // ---- END WEBSITE SNIPPET ----

    } catch (err) {
        console.log("OUTER ERROR: " + err)
    }

}

run()