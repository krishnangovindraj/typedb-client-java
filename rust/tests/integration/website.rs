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

use serial_test::serial;
use std::{collections::HashMap, default::Default};
use async_std::sync::Arc;
use futures::TryStreamExt;

use crate::test_for_each_arg;
use typedb_driver::{
    answer::{ConceptMap, Explainable},
    concept::{Attribute, Concept, Value},
    logic::Explanation,
    transaction::concept::api::{ThingAPI, ThingTypeAPI, EntityTypeAPI},
    Connection, DatabaseManager, Options, Result as TypeDBResult, Session,
    SessionType::{Data, Schema},
    Transaction,
    TransactionType::{Read, Write},
    TransactionType,
    SessionType
};

test_for_each_arg! {
    {
        core => 0,
    }

    async fn on_website_test_api(_conn: i64) -> TypeDBResult {
        let access_management_schema = "define user sub entity;";
        let access_management_data_batches: Vec<Vec<String>> = vec![
            vec!["insert $u isa user;".to_string()]
        ];
        let connection_setup = Connection::new_core("localhost:1729")?;
        let databases_setup = DatabaseManager::new(connection_setup);
        if databases_setup.contains("access-management-db").await? { databases_setup.get("access-management-db").await?.delete().await?; }

        // ---- START WEBSITE SNIPPET ----
        let connection = Connection::new_core("localhost:1729")?;
        let databases = DatabaseManager::new(connection);

        databases.create("access-management-db").await?;

        let session = Session::new(databases.get("access-management-db").await?, SessionType::Schema).await?;
        let tx = session.transaction(TransactionType::Write).await?;
        tx.query().define(access_management_schema).await?;
        tx.commit().await?;
        drop(session);

        let session = Arc::new(Session::new(databases.get("access-management-db").await?, SessionType::Data).await?);
        futures::future::try_join_all(access_management_data_batches.into_iter().map(|batch| {
            let session = session.clone();
            async move {
                let tx = session.transaction(TransactionType::Write).await?;
                batch.iter().try_for_each(|query| tx.query().insert(query).map(|_| ()))?;
                tx.commit().await
            }
        })).await?;

        let tx = session.transaction(TransactionType::Read).await?;
        let mut stream = tx.query().get("match $u isa user; get;")?;

        // ---- END WEBSITE SNIPPET ----
        Ok(())
    }


    async fn on_website_test_migration(_conn: i64) -> TypeDBResult  {
        let access_management_schema = "define employee sub entity, owns email, owns name; contractor sub entity; name sub attribute, value string; email sub attribute, value string;";
        let connection_setup = Connection::new_core("localhost:1729")?;
        let databases_setup = DatabaseManager::new(connection_setup);
        if databases_setup.contains("access-management-db").await? { databases_setup.get("access-management-db").await?.delete().await?; }
        databases_setup.create("access-management-db").await?;

        let session_setup = Session::new(databases_setup.get("access-management-db").await?, SessionType::Schema).await?;
        let tx_setup = session_setup.transaction(TransactionType::Write).await?;
        tx_setup.query().define(access_management_schema).await?;
        tx_setup.commit().await?;
        drop(session_setup);


        // ---- START WEBSITE SNIPPET ----
        let connection = Connection::new_core("localhost:1729")?;
        let databases = DatabaseManager::new(connection);
        let session = Session::new(databases.get("access-management-db").await?, SessionType::Schema).await?;
        let tx = session.transaction(TransactionType::Write).await?;

        // create a new abstract type "user"
        let mut user = tx.concept().put_entity_type("user".to_owned()).await?;
        user.set_abstract(&tx).await?;

        // change the supertype of "employee" to "user"
        let mut employee = tx.concept().get_entity_type("employee".to_owned()).await?.unwrap();
        employee.set_supertype(&tx, user.clone()).await?;

        // change the supertype of "contractor" to "user"
        let mut contractor = tx.concept().get_entity_type("contractor".to_owned()).await?.unwrap();
        contractor.set_supertype(&tx, user.clone()).await?;

        // move "email" and "name" attribute types to be owned by "user" instead of "employee"
        let email = tx.concept().get_attribute_type("email".to_owned()).await?.unwrap();
        let mut name = tx.concept().get_attribute_type("name".to_owned()).await?.unwrap();
        employee.unset_owns(&tx, email.clone()).await?;
        employee.unset_owns(&tx, name.clone()).await?;
        user.set_owns(&tx, email, None, Vec::new()).await?;
        user.set_owns(&tx, name.clone(), None, Vec::new()).await?;

        // rename "name" attribute type to "full-name"
        name.set_label(&tx, "full-name".to_owned()).await?;

        // commit all schema changes in one transaction, which will fail if we violate any data validation
        tx.commit().await?;

        // ---- END WEBSITE SNIPPET ----
        Ok(())
    }
}
