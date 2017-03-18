#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "solution.h"

TEST_CASE("empty")
{
    auto m = std::vector<std::vector<int>>{{}};
    auto expected = m;
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("1x1_zero")
{
    auto m = std::vector<std::vector<int>>{{0}};
    auto expected = m;
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("1x1_one")
{
    auto m = std::vector<std::vector<int>>{{1}};
    auto expected = m;
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("1x2")
{
    auto m = std::vector<std::vector<int>>{{1, 0}};
    auto expected = std::vector<std::vector<int>>{{0, 0}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("2x1")
{
    auto m = std::vector<std::vector<int>>{ {1},
                                            {0}};
    auto expected = std::vector<std::vector<int>>{  {0},
                                                    {0}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("3x3_first_row_with_zeros")
{
    auto m = std::vector<std::vector<int>>{ {1, 0, 1},
                                            {1, 1, 1},
                                            {1, 1, 1}};
    auto expected = std::vector<std::vector<int>>{  {0, 0, 0},
                                                    {1, 0, 1},
                                                    {1, 0, 1}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("3x3_first_col_with_zeros")
{
    auto m = std::vector<std::vector<int>>{ {1, 1, 1},
                                            {0, 1, 1},
                                            {1, 1, 1}};
    auto expected = std::vector<std::vector<int>>{  {0, 1, 1},
                                                    {0, 0, 0},
                                                    {0, 1, 1}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("3x3_first_row_and_col_with_zeros")
{
    auto m = std::vector<std::vector<int>>{ {0, 1, 1},
                                            {1, 1, 1},
                                            {1, 1, 1}};
    auto expected = std::vector<std::vector<int>>{  {0, 0, 0},
                                                    {0, 1, 1},
                                                    {0, 1, 1}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("4x5")
{
    auto m = std::vector<std::vector<int>>{ {1, 1, 1, 1},
                                            {1, 0, 1, 1 },
                                            {1, 1, 1, 1},
                                            {1, 1, 1, 0}};
    auto expected = std::vector<std::vector<int>>{  {1, 0, 1, 0},
                                                    {0, 0, 0, 0 },
                                                    {1, 0, 1, 0},
                                                    {0, 0, 0, 0}};
    solution(m);
    REQUIRE(m == expected);
}
