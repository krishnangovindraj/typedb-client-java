/*
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

package com.typedb.driver.api.answer;

import javax.annotation.CheckReturnValue;
import java.util.Iterator;
import java.util.stream.Stream;

/**
 * Represents an iterator over <code>ConceptRow</code>s returned as a server answer.
 */
public interface ConceptRowIterator extends QueryAnswer, Iterator<ConceptRow> {
    /**
     * {@inheritDoc}
     */
    @Override
    default boolean isConceptRows() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @CheckReturnValue
    default ConceptRowIterator asConceptRows() {
        return this;
    }

    /**
     * Creates a stream over <code>ConceptRow</code>s based on this iterator.
     *
     * <h3>Examples</h3>
     * <pre>
     * answer.asConceptRows().stream();
     * </pre>
     */
    @CheckReturnValue
    Stream<ConceptRow> stream();
}
