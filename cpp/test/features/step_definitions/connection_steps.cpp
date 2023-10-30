#include <cucumber-cpp/autodetect.hpp>

#include "typedb/connection/TypeDBDriver.hpp"

using cucumber::ScenarioScope;

struct TypeDBCtx {
    TypeDBDriver driver;

};

GIVEN("^typedb has configuration$") {
    // for when we can run typedb from C++
}

GIVEN("^typedb starts$") {
    // for when we can run typedb from C++
}

WHEN("^connection opens with default authentication$") {
    ScenarioScope<TypeDBCtx> ctx;
    ctx->driver(std::move(TypeDBDriver("127.0.0.1:1729")));
}

THEN("^the result should be (.*) on the screen$") {
    REGEX_PARAM(double, expected);
    ScenarioScope<CalcCtx> context;

    EXPECT_EQ(expected, context->result);
}