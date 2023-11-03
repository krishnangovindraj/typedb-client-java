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

namespace TypeDB::BDD {

using namespace cucumber::messages;

cucumber_bdd::StepCollection<Context> transactionSteps = {
    
    BDD_STEP("session opens transaction of type: (read|write)", {
        context.transaction = std::move(context.session.transaction(parseTransactionType(matches[1].str()), context.transactionOptions));
    }),
    
    BDD_STEP("for each session, open transaction of type: (read|write)", {
        std::function<TypeDB::Transaction(const TypeDB::Session&)> fn = [&](const TypeDB::Session& session) { return session.transaction(parseTransactionType(matches[1].str()), context.transactionOptions); };
        apply_serial(context.sessions, fn);
    }),
    // BDD_STEP("for each session, open transaction of type:"),
    BDD_STEP("for each session, open transactions of type:", {
        std::vector<zipped<TypeDB::Session>> z = zip(step.argument->data_table->rows, context.sessions);
        std::function<TypeDB::Transaction(const zipped<TypeDB::Session>&)> fn = [&](const zipped<TypeDB::Session>& rowSession) { 
            return rowSession.obj->transaction(parseTransactionType(rowSession.row->cells[0].value), context.transactionOptions);
        };
        context.transactions = apply_serial(z, fn);
    }),
    BDD_UNIMPLEMENTED("session open transaction of type; throws exception: (read|write)"),
    BDD_UNIMPLEMENTED("for each session, open transactions of type; throws exception"),
    BDD_UNIMPLEMENTED("session transaction is null: (true|false)"),
    BDD_UNIMPLEMENTED("for each session, transaction is null: (true|false)"),
    BDD_UNIMPLEMENTED("for each session, transactions are null: (true|false)"),
    BDD_UNIMPLEMENTED("session transaction is open: (true|false)"),
    BDD_UNIMPLEMENTED("for each session, transaction is open: (true|false)"),
    BDD_UNIMPLEMENTED("for each session, transactions are open: (true|false)"),
    BDD_UNIMPLEMENTED("session transaction commits"),
    BDD_UNIMPLEMENTED("transaction commits"),
    BDD_UNIMPLEMENTED("session transaction closes"),
    BDD_UNIMPLEMENTED("session transaction commits; throws exception"),
    BDD_UNIMPLEMENTED("transaction commits; throws exception"),
    BDD_UNIMPLEMENTED("transaction commits; throws exception containing \"(.+)\""),
    BDD_UNIMPLEMENTED("for each session, transaction commits"),
    BDD_UNIMPLEMENTED("for each session, transactions commit"),
    BDD_UNIMPLEMENTED("for each session, transaction commits; throws exception"),
    BDD_UNIMPLEMENTED("for each session, transactions commit; throws exception"),
    BDD_UNIMPLEMENTED("for each session, transaction closes"),
    BDD_UNIMPLEMENTED("for each session, transaction has type"),
    BDD_STEP("for each session, transactions have type:", {
        std::vector<zipped<TypeDB::Transaction>> z = zip(step.argument->data_table->rows, context.transactions);
        std::function<void(const zipped<TypeDB::Transaction>&)> fn = [&](const zipped<TypeDB::Transaction>& rowTxn) { 
            ASSERT_EQ(parseTransactionType(rowTxn.row->cells[0].value), rowTxn.obj->type());
        };
        foreach_serial(z, fn);
    }),
    BDD_UNIMPLEMENTED("for each session, transaction has type: (read|write)"),
    BDD_UNIMPLEMENTED("session transaction has type: (read|write)"),
    BDD_UNIMPLEMENTED("for each session, open transactions in parallel of type:"),
    BDD_UNIMPLEMENTED("for each session, transactions in parallel are null: (true|false)"),
    BDD_UNIMPLEMENTED("for each session, transactions in parallel are open: (true|false)"),
    BDD_UNIMPLEMENTED("for each session, transactions in parallel have type:"),
    BDD_UNIMPLEMENTED("for each session in parallel, transactions in parallel are null: (true|false)"),
    BDD_UNIMPLEMENTED("for each session in parallel, transactions in parallel are open: (true|false)"),
    BDD_STEP("set transaction option ([A-Za-z_\\-]+) to: ([A-Za-z0-9]+)", {
        assert(matches[1] == "transaction-timeout-millis");
        context.transactionOptions.transactionTimeoutMillis(atoi(matches[2].str().c_str()));
    }),
    BDD_UNIMPLEMENTED("for each transaction, define query; throws exception containing \"(.+)\""),
};

}  // namespace TypeDB::BDD
