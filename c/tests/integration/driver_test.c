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

#include <stdio.h>
#include <string.h>

#include "c/typedb_driver.h"
#include "common.h"

#define FAILED() check_error_may_print(__FILE__, __LINE__)

bool accessManagementExample() {
    const char* accessManagementSchema = "define\n attr sub attribute, value string, owns attr;";
    const char* accessManagementDataBatches[1][1] = {{"insert $s \"o0_val\" isa attr; $s has attr \"o1_val\";"}};
    const int accessManagementDataBatchCount = 1;
    const int accessManagementDataBatchSize = 1;

    {
        Connection* connection = connection_open_core(TYPEDB_CORE_ADDRESS);
        DatabaseManager* databaseManager = database_manager_new(connection);
        delete_database_if_exists(databaseManager, "access-management-db");    databases_create(databaseManager, "access-management-db"); // TODO: Remove line
    }

Connection* connection = connection_open_core("localhost:1729");
DatabaseManager* databaseManager = database_manager_new(connection);
{
    Options* options = options_new();
    Session* session = session_new(databaseManager, "access-management-db", Schema, options);
    Transaction* tx = transaction_new(session, Write, options);
    VoidPromise* results = query_define(tx, accessManagementSchema, options);
    void_promise_resolve(results);
    void_promise_resolve(transaction_commit(tx));
    session_close(session);
    options_drop(options);
}

{
    Options* options = options_new();
    Session* session = session_new(databaseManager, "access-management-db", Data, options);
    {
        Transaction* tx = transaction_new(session, Write, options);
        for (int i = 0; i < accessManagementDataBatchCount; i++) {
            for (int j = 0 ; j < accessManagementDataBatchSize; j++) {
                ConceptMapIterator* inserted = query_insert(tx, accessManagementDataBatches[i][j], options);
                concept_map_iterator_drop(inserted);
            }
        }
        void_promise_resolve(transaction_commit(tx));
    }
    {
        Transaction* tx = transaction_new(session, Read, options);
        ConceptMapIterator* results = query_get(tx, "match $u isa user; get;", options);
        concept_map_iterator_drop(results);
        transaction_close(tx);
    }
    session_close(session);
    options_drop(options);
}


    return true;
}

bool schemaMigrationExample() {

    // TODO: REMOVE SECTION
    {

        Connection* connection = connection_open_core(TYPEDB_CORE_ADDRESS);
        DatabaseManager* databaseManager = database_manager_new(connection);

        const char* schema = "define name sub attribute, value string; email sub attribute, value string ; employee sub entity, owns name, owns email; contractor sub entity; ";
        delete_database_if_exists(databaseManager, "access-management-db");    databases_create(databaseManager, "access-management-db"); // TODO: Remove line
        Options* options = options_new();
        Session* session = session_new(databaseManager, "access-management-db", Schema, options);
        Transaction* tx = transaction_new(session, Write, options);
        void_promise_resolve(query_define(tx, schema, options));
        void_promise_resolve(transaction_commit(tx));
        session_close(session);
        options_drop(options);
    }
    // PLTEASE REMOVE TX COMMIT FROM LINE 10 CPP!

Connection* connection = connection_open_core("localhost:1729");
DatabaseManager* databaseManager = database_manager_new(connection);

Options* options = options_new();
Session* session = session_new(databaseManager, "access-management-db", Schema, options);
Transaction* tx = transaction_new(session, Write, options);

// create a new abstract type "user"
Concept* user = concept_promise_resolve(concepts_put_entity_type(tx, "user"));
void_promise_resolve(thing_type_set_abstract(tx, user));

// change the supertype of "employee" to "user"
Concept* employee = concept_promise_resolve(concepts_get_entity_type(tx, "employee"));
void_promise_resolve(entity_type_set_supertype(tx, employee, user));

// change the supertype of "contractor" to "user"
Concept* contractor = concept_promise_resolve(concepts_get_entity_type(tx, "contractor"));
void_promise_resolve(entity_type_set_supertype(tx, contractor, user));

// move "email" and "name" attribute types to be owned by "user" instead of "employee"
Concept* email = concept_promise_resolve(concepts_get_attribute_type(tx, "email"));
Concept* name = concept_promise_resolve(concepts_get_attribute_type(tx, "name"));
void_promise_resolve(entity_type_set_supertype(tx, contractor, user));
// unset them on "employee"
void_promise_resolve(thing_type_unset_owns(tx, employee, email));
void_promise_resolve(thing_type_unset_owns(tx, employee, name));
// set them on "user"
const Annotation* noAnnotations[1] = {NULL};
void_promise_resolve(thing_type_set_owns(tx, user, email, NULL, noAnnotations));
void_promise_resolve(thing_type_set_owns(tx, user, name, NULL, noAnnotations));

// rename "name" attribute type to "full-name"
void_promise_resolve(thing_type_set_label(tx, name, "full-name"));

// commit all schema changes in one transaction, which will fail if we violate any data validation
void_promise_resolve(transaction_commit(tx));

session_close(session);
options_drop(options);


    return true;
}
bool test_debug() {
    return accessManagementExample() &&  schemaMigrationExample();
}
