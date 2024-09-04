//
// Created by stellaura on 04/09/24.
//
#include <catch2/catch_all.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

TEST_CASE("Test", "[test]"){
    spdlog::info("Hello, world!");
    fmt::print("{}\n", "test");
    REQUIRE(true);
}

