#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Solution.h"

TEST_CASE("[1, 2, 3], []")
{
   auto a = std::vector<int>{1, 2, 3};
   auto b = std::vector<int>{};
   double expectedMedian = 2.0;
   REQUIRE(Solution{}.findMedianSortedArrays(a, b) == expectedMedian);
}

TEST_CASE("[], [1, 2, 3]")
{
   auto a = std::vector<int>{};
   auto b = std::vector<int>{1, 2, 3};
   double expectedMedian = 2.0;
   REQUIRE(Solution{}.findMedianSortedArrays(a, b) == expectedMedian);
}

TEST_CASE("[1, 2], []")
{
   auto a = std::vector<int>{1, 2};
   auto b = std::vector<int>{};
   double expectedMedian = 1.5;
   REQUIRE(Solution{}.findMedianSortedArrays(a, b) == expectedMedian);
}

TEST_CASE("[], [1, 2]")
{
   auto a = std::vector<int>{};
   auto b = std::vector<int>{1, 2};
   double expectedMedian = 1.5;
   REQUIRE(Solution{}.findMedianSortedArrays(a, b) == expectedMedian);
}

TEST_CASE("[1, 3, 4], [2]")
{
   auto a = std::vector<int>{1, 3, 4};
   auto b = std::vector<int>{2};
   double expectedMedian = 2.5;
   REQUIRE(Solution{}.findMedianSortedArrays(a, b) == expectedMedian);
}

TEST_CASE("[3], [1, 2]")
{
   auto a = std::vector<int>{3};
   auto b = std::vector<int>{1, 2};
   double expectedMedian = 2.0;
   REQUIRE(Solution{}.findMedianSortedArrays(a, b) == expectedMedian);
}
