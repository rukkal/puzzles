#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Solution.h"

//problem statement (from leetcode):
//Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.
//Each rectangle is represented as a bottom-left point and a top-right point.
//For example, a unit square is represented as [1,1,2,2].
//(coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)). 

TEST_CASE("valid: 1 rectangles")
{
   auto rectangles = std::vector<std::vector<int>> {
      {1, 1, 2, 2},
   };
   REQUIRE(Solution{}.isRectangleCover(rectangles) == true);
}

TEST_CASE("valid: 2 rectangles")
{
   auto rectangles = std::vector<std::vector<int>> {
      {1, 1, 2, 5},
      {1, 5, 2, 10}
   };
   REQUIRE(Solution{}.isRectangleCover(rectangles) == true);
}

TEST_CASE("invalid: 2 rectangles (with contact)")
{
   auto rectangles = std::vector<std::vector<int>> {
      {1, 1, 5, 2},
      {3, 2, 5, 3}
   };
   REQUIRE(Solution{}.isRectangleCover(rectangles) == false);
}

TEST_CASE("invalid: 2 rectangles (without contact)")
{
   auto rectangles = std::vector<std::vector<int>> {
      {1, 1, 5, 2},
      {1, 3, 5, 4}
   };
   REQUIRE(Solution{}.isRectangleCover(rectangles) == false);
}

TEST_CASE("invalid: 2 rectangles (with overlap)")
{
   auto rectangles = std::vector<std::vector<int>> {
      {1, 1, 10, 5},
      {5, 3, 15, 10}
   };
   REQUIRE(Solution{}.isRectangleCover(rectangles) == false);
}

TEST_CASE("invalid: 3 rectangles (2 identical)")
{
   auto rectangles = std::vector<std::vector<int>> {
      {1, 1, 2, 2},
      {1, 1, 2, 2},
      {2, 1, 3, 2}
   };
   REQUIRE(Solution{}.isRectangleCover(rectangles) == false);
}
