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

TEST_CASE("1x1")
{
    auto m = std::vector<std::vector<int>>{{1}};
    auto expected = m;
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("2x2")
{
    auto m = std::vector<std::vector<int>>{ {1, 2},
                                            {3, 4}};
    auto expected = std::vector<std::vector<int>>{  {3, 1},
                                                    {4, 2}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("3x3")
{
    auto m = std::vector<std::vector<int>>{ {1, 2, 3},
                                            {4, 5, 6},
                                            {7, 8, 9}};
    auto expected = std::vector<std::vector<int>>{  {7, 4, 1},
                                                    {8, 5, 2},
                                                    {9, 6, 3}};
    solution(m);
    REQUIRE(m == expected);
}

TEST_CASE("4x4")
{
    auto m = std::vector<std::vector<int>>{ {1, 2, 3, 4},
                                            {5, 6, 7, 8},
                                            {9, 10, 11, 12},
                                            {13, 14, 15, 16}};
    auto expected = std::vector<std::vector<int>>{  {13, 9, 5, 1},
                                                    {14, 10, 6, 2},
                                                    {15, 11, 7, 3},
                                                    {16, 12, 8, 4}};
    solution(m);
    REQUIRE(m == expected);
}

