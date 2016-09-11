#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Solution.h"

//problem statement:
//Given a set of items, each with two weights and a value, determine which items
//to include in a collection so that the total weights are less than or equal
//to a given limit and the total value is as large as possible

TEST_CASE("items (0 -> not included, 1 -> included): {}")
{
   auto items = std::vector<Solution::Item>{};
   int limit0 = 1;
   int limit1 = 1;
   int expected_total_value = 0;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {0}")
{
   auto items = std::vector<Solution::Item>{
      {100, 1, 2},
   };
   int limit0 = 1;
   int limit1 = 1;
   int expected_total_value = 0;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {1}")
{
   auto items = std::vector<Solution::Item>{
      {100, 1, 2},
   };
   int limit0 = 1;
   int limit1 = 2;
   int expected_total_value = 100;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {0, 0}")
{
   auto items = std::vector<Solution::Item>{
      {100, 10, 20},
      {200, 1, 2},
   };
   int limit0 = 1;
   int limit1 = 1;
   int expected_total_value = 0;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {0, 1}")
{
   auto items = std::vector<Solution::Item>{
      {100, 10, 20},
      {200, 1, 2},
   };
   int limit0 = 1;
   int limit1 = 2;
   int expected_total_value = 200;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {1, 1}")
{
   auto items = std::vector<Solution::Item>{
      {100, 1, 2},
      {200, 2, 3},
   };
   int limit0 = 3;
   int limit1 = 5;
   int expected_total_value = 300;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {1, 1, 0}")
{
   auto items = std::vector<Solution::Item>{
      {100, 1, 2},
      {200, 2, 3},
      {200, 3, 5},
   };
   int limit0 = 3;
   int limit1 = 5;
   int expected_total_value = 300;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {0, 0, 1}")
{
   auto items = std::vector<Solution::Item>{
      {100, 1, 2},
      {200, 2, 3},
      {301, 3, 5},
   };
   int limit0 = 3;
   int limit1 = 5;
   int expected_total_value = 301;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {1, 0, 0, 0}")
{
   auto items = std::vector<Solution::Item>{
      {100, 1, 1},
      {200, 2, 2},
      {200, 3, 3},
      {200, 4, 4},
   };
   int limit0 = 1;
   int limit1 = 1;
   int expected_total_value = 100;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {1, 0, 1, 0}")
{
   auto items = std::vector<Solution::Item>{
      {500, 1, 1},
      {200, 2, 2},
      {500, 3, 3},
      {200, 4, 4},
   };
   int limit0 = 4;
   int limit1 = 4;
   int expected_total_value = 1000;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}

TEST_CASE("items (0 -> not included, 1 -> included): {1, 1, 1, 0}")
{
   auto items = std::vector<Solution::Item>{
      {500, 1, 1},
      {500, 2, 2},
      {500, 3, 3},
      {200, 4, 4},
   };
   int limit0 = 6;
   int limit1 = 6;
   int expected_total_value = 1500;
   REQUIRE(Solution{}.solveKnappsack(items, limit0, limit1) == expected_total_value);
}
