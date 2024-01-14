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

package com.vaticle.typedb.driver.test.behaviour.connection;

import com.vaticle.typedb.core.tool.runner.TypeDBSingleton;
import com.vaticle.typedb.driver.api.TypeDBDriver;
import com.vaticle.typedb.driver.api.TypeDBOptions;
import com.vaticle.typedb.driver.api.TypeDBSession;
import com.vaticle.typedb.driver.api.TypeDBTransaction;
import com.vaticle.typedb.driver.api.database.Database;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.function.BiConsumer;
import java.util.stream.Stream;

import static com.vaticle.typedb.common.collection.Collections.map;
import static com.vaticle.typedb.common.collection.Collections.pair;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

public abstract class ConnectionStepsBase {
    public static int THREAD_POOL_SIZE = 32;
    public static ExecutorService threadPool = Executors.newFixedThreadPool(THREAD_POOL_SIZE);

    public static TypeDBDriver driver;
    public static List<TypeDBSession> sessions = new ArrayList<>();
    public static List<CompletableFuture<TypeDBSession>> sessionsParallel = new ArrayList<>();
    public static Map<TypeDBSession, List<TypeDBTransaction>> sessionsToTransactions = new HashMap<>();
    public static Map<TypeDBSession, List<CompletableFuture<TypeDBTransaction>>> sessionsToTransactionsParallel = new HashMap<>();
    public static Map<CompletableFuture<TypeDBSession>, List<CompletableFuture<TypeDBTransaction>>> sessionsParallelToTransactionsParallel = new HashMap<>();
    public static TypeDBOptions sessionOptions;
    public static TypeDBOptions transactionOptions;
    static boolean isBeforeAllRan = false;

    public static final Map<String, BiConsumer<TypeDBOptions, String>> optionSetters = map(
            pair("session-idle-timeout-millis", (option, val) -> option.sessionIdleTimeoutMillis(Integer.parseInt(val))),
            pair("transaction-timeout-millis", (option, val) -> option.transactionTimeoutMillis(Integer.parseInt(val)))
    );

    public static TypeDBTransaction tx() {
        return sessionsToTransactions.get(sessions.get(0)).get(0);
    }

    void beforeAll() {
        TypeDBSingleton.deleteTypeDBRunner();
    }

    void before() {
        if (!isBeforeAllRan) {
            try {
                beforeAll();
            } finally {
                isBeforeAllRan = true;
            }
        }
        sessionOptions = createOptions().infer(true);
        transactionOptions = createOptions().infer(true);

        System.out.println("ConnectionSteps.before");
    }

    void after() {
        sessions.parallelStream().forEach(TypeDBSession::close);
        sessions.clear();

        Stream<CompletableFuture<Void>> closures = sessionsParallel
                .stream().map(futureSession -> futureSession.thenApplyAsync(session -> {
                    session.close();
                    return null;
                }));
        CompletableFuture.allOf(closures.toArray(CompletableFuture[]::new)).join();
        sessionsParallel.clear();
        sessionsToTransactions.clear();
        sessionsToTransactionsParallel.clear();
        sessionsParallelToTransactionsParallel.clear();
        driver = createTypeDBDriver(TypeDBSingleton.getTypeDBRunner().address());
        driver.databases().all().forEach(Database::delete);
        driver.close();

        System.out.println("ConnectionSteps.after");
    }

    abstract TypeDBDriver createTypeDBDriver(String address);

    abstract TypeDBOptions createOptions();

    abstract void connection_opens_with_default_authentication();

    void connection_closes() {
        driver.close();
        driver = null;
    }

    void connection_has_been_opened() {
        assertNotNull(driver);
        assertTrue(driver.isOpen());
    }

    void connection_does_not_have_any_database() {
        assertNotNull(driver);
        assertTrue(driver.isOpen());
        assertTrue(driver.databases().all().isEmpty());
    }
}
