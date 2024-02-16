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

import unittest
from unittest import TestCase

from typedb.driver import *

TYPEDB = "typedb"
SCHEMA = SessionType.SCHEMA
DATA = SessionType.DATA
READ = TransactionType.READ
WRITE = TransactionType.WRITE


class TestWebsite(TestCase):

    def setUp(self):
        with TypeDB.core_driver(TypeDB.DEFAULT_ADDRESS) as driver:
            if TYPEDB not in [db.name for db in driver.databases.all()]:
                driver.databases.create(TYPEDB)

    def test_website_docs_api(self):
        access_management_schema = "define user sub entity;"
        access_management_data_batches= [["insert $u isa user;"]]
        with TypeDB.core_driver("localhost:1729") as driver:
            if driver.databases.contains("access-management-db"): driver.databases.get("access-management-db").delete()

        # ---- START WEBSITE SNIPPET ---
        with TypeDB.core_driver("localhost:1729") as driver:


            driver.databases.create("access-management-db")

            with driver.session("access-management-db", SessionType.SCHEMA) as session:
                with session.transaction(TransactionType.WRITE) as tx:
                    tx.query.define(access_management_schema)
                    tx.commit()

            with driver.session("access-management-db", SessionType.DATA) as session:
                for batch in access_management_data_batches:
                    with session.transaction(TransactionType.WRITE) as tx:
                        for query in batch:
                            tx.query.insert(query)

                        tx.commit()

                    with session.transaction(TransactionType.READ) as tx:
                        results = tx.query.get("match $u isa user; get;")
        # ---- END WEBSITE SNIPPET ---

    def test_website_docs_migration(self):
        access_management_schema = "define employee sub entity, owns email, owns name; contractor sub entity; name sub attribute, value string; email sub attribute, value string;";
        with TypeDB.core_driver("localhost:1729") as driver:
            if driver.databases.contains("access-management-db"): driver.databases.get("access-management-db").delete()
            driver.databases.create("access-management-db")
            with driver.session("access-management-db", SessionType.SCHEMA) as session:
                with session.transaction(TransactionType.WRITE) as tx:
                    tx.query.define(access_management_schema).resolve()
                    tx.commit()

        # ---- START WEBSITE SNIPPET ---
        with TypeDB.core_driver("localhost:1729") as driver:
            with driver.session("access-management-db", SessionType.SCHEMA) as session:
                with session.transaction(TransactionType.WRITE) as tx:

                    # create a new abstract type "user"
                    user = tx.concepts.put_entity_type("user").resolve()
                    user.set_abstract(tx).resolve()

                    # change the supertype of "employee" to "user"
                    employee = tx.concepts.get_entity_type("employee").resolve()
                    employee.set_supertype(tx, user).resolve()

                    # change the supertype of "contractor" to "user"
                    contractor = tx.concepts.get_entity_type("contractor").resolve()
                    contractor.set_supertype(tx, user).resolve()

                    # move "email" and "name" attribute types to be owned by "user" instead of "employee"
                    email = tx.concepts.get_attribute_type("email").resolve()
                    name = tx.concepts.get_attribute_type("name").resolve()
                    employee.unset_owns(tx, email).resolve()
                    employee.unset_owns(tx, name).resolve()
                    user.set_owns(tx, email).resolve()
                    user.set_owns(tx, name).resolve()

                    # rename "name" attribute type to "full-name"
                    name.set_label(tx, "full-name").resolve()

                    # commit all schema changes in one transaction, which will fail if we violate any data validation
                    tx.commit()
        # ---- END WEBSITE SNIPPET ---



if __name__ == "__main__":
    unittest.main(verbosity=2)
