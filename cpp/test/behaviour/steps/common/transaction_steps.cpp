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

#include <cstdlib>

#include "common.hpp"
#include "steps.hpp"
#include "utils.hpp"

#include "typedb/connection/session.hpp"

using namespace cucumber::messages;

namespace TypeDB::BDD {

// void forEachSessionTransaction_serial(Context& context, std::function<void(TypeDB::Transaction*)> fn) {
//     for (auto& sess: context.sessions) {
//         foreach_serial(context.sessionTransactions[&sess], fn);
//     }
// }

// void forEachSessionTransaction_parallel(Context& context, std::function<void(TypeDB::Transaction*)> fn) {
//     for (auto& sess: context.sessions) {
//         foreach_parallel(context.sessionTransactions[&sess], fn);
//     }
// }

cucumber_bdd::StepCollection<Context> transactionSteps = {
    
    BDD_STEP("session opens transaction of type: (read|write)", {
        context.transaction = std::move(context.session.transaction(parseTransactionType(matches[1].str()), context.transactionOptions));
    }),
    BDD_UNIMPLEMENTED("session open transaction of type; throws exception: (read|write)"),
    BDD_UNIMPLEMENTED("for each session, open transactions of type; throws exception"),
    BDD_STEP("session transaction is null: (true|false)", {
        ASSERT_EQ(parseBoolean(matches[1]), !context.transaction.isOpen());
    }),
    BDD_STEP("session transaction is open: (true|false)", {
        ASSERT_EQ(parseBoolean(matches[1]), context.transaction.isOpen());
    }),
    BDD_STEP("session transaction commits", {
        context.transaction.commit();
    }),
    BDD_STEP("transaction commits", {
        context.transaction.commit();
    }),
    BDD_STEP("session transaction closes", {
        context.transaction.close();
    }),
    BDD_STEP("session transaction commits; throws exception", {
        DRIVER_THROWS("", {context.transaction.commit();});
    }),
    BDD_STEP("transaction commits; throws exception", {
        DRIVER_THROWS("", {context.transaction.commit();});
    }),
    
    BDD_STEP("transaction commits; throws exception containing \"(.+)\"", {
        DRIVER_THROWS(matches[1].str(), {context.transaction.commit();});
    }),
    BDD_STEP("session transaction has type: (read|write)", {
        ASSERT_EQ(parseTransactionType(matches[1].str()), context.transaction.type());
    }),
    BDD_STEP("set transaction option ([A-Za-z_\\-]+) to: ([A-Za-z0-9]+)", {
        assert(matches[1] == "transaction-timeout-millis");
        context.transactionOptions.transactionTimeoutMillis(atoi(matches[2].str().c_str()));
    }),

    // BDD_STEP("for each session, open transaction of type: (read|write)", {
    //     std::function<void(TypeDB::Session*)> fn = [&](TypeDB::Session* session) { 
    //         context.sessionTransactions[session].push_back(session->transaction(parseTransactionType(matches[1].str()), context.transactionOptions));
    //     };
    //     foreach_serial(context.sessions, fn);
    // }),
    // BDD_UNIMPLEMENTED("for each session, open transaction of type:"),
    // BDD_STEP("for each session, open transactions of type:", {
    //     std::vector<zipped<TypeDB::Session>> z = zip(step.argument->data_table->rows, context.sessions);
    //     std::function<void(zipped<TypeDB::Session>*)> fn = [&](zipped<TypeDB::Session>* rowSession) { 
    //         context.sessionTransactions[rowSession->obj].push_back(rowSession->obj->transaction(parseTransactionType(rowSession->row->cells[0].value), context.transactionOptions));
    //     };
    // }),
    // BDD_STEP("for each session, transaction is null: (true|false)", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* tx) { ASSERT_EQ(parseBoolean(matches[1]), !tx->isOpen()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transactions are null: (true|false)", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* tx) { ASSERT_EQ(parseBoolean(matches[1]), !tx->isOpen()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transaction is open: (true|false)", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* tx) { ASSERT_EQ(parseBoolean(matches[1]), tx->isOpen()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transactions are open: (true|false)", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* tx) -> void { ASSERT_EQ(parseBoolean(matches[1]), tx->isOpen()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transaction commits", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* transaction) { transaction->commit(); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transactions commit", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* transaction) { transaction->commit(); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transaction commits; throws exception", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* transaction) { DRIVER_THROWS("", transaction->commit()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transactions commit; throws exception", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* transaction) { DRIVER_THROWS("", transaction->commit()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transaction closes", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* transaction) { transaction->close(); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),
    // BDD_STEP("for each session, transaction has type", {
    //     std::vector<TypeDB::Transaction*> transactions;
    //     for (auto& session: context.sessions) {
    //         for (auto& txn : context.sessionTransactions[&session]) {
    //             transactions.push_back(&txn);
    //         }
    //     } 
    //     ASSERT_EQ(step.argument->data_table->rows.size(), transactions.size());
    //     for (int i=0; i < transactions.size(); i++) {
    //         ASSERT_EQ(parseTransactionType(step.argument->data_table->rows[i].cells[0].value), transactions[i]->type());
    //     }
    // }),
    // BDD_STEP("for each session, transactions have type:", {
    //     std::vector<TypeDB::Transaction*> transactions;
    //     for (auto& session: context.sessions) {
    //         for (auto& txn : context.sessionTransactions[&session]) {
    //             transactions.push_back(&txn);
    //         }
    //     } 
    //     ASSERT_EQ(step.argument->data_table->rows.size(), transactions.size());
    //     for (int i=0; i < transactions.size(); i++) {
    //         ASSERT_EQ(parseTransactionType(step.argument->data_table->rows[i].cells[0].value), transactions[i]->type());
    //     }
    // }),
    // BDD_STEP("for each session, transaction has type: (read|write)", {
    //     std::function<void(TypeDB::Transaction*)> fn = [&](TypeDB::Transaction* transaction) { ASSERT_EQ(parseTransactionType(matches[1].str()), transaction->type()); };
    //     forEachSessionTransaction_serial(context, fn);
    // }),

    // BDD_UNIMPLEMENTED("for each session, open transactions in parallel of type:"),
    // BDD_UNIMPLEMENTED("for each session, transactions in parallel are null: (true|false)"),
    // BDD_UNIMPLEMENTED("for each session, transactions in parallel are open: (true|false)"),
    // BDD_UNIMPLEMENTED("for each session, transactions in parallel have type:"),
    // BDD_UNIMPLEMENTED("for each session in parallel, transactions in parallel are null: (true|false)"),
    // BDD_UNIMPLEMENTED("for each session in parallel, transactions in parallel are open: (true|false)"),
    // BDD_UNIMPLEMENTED("for each transaction, define query; throws exception containing \"(.+)\""),

};

}  // namespace TypeDB::BDD
