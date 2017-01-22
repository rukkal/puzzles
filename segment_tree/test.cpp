#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "segment_tree.h"

TEST_CASE("initial values = []")
{
    auto values = std::vector<int>{ };
    auto tree = SegmentTree{values};
}

TEST_CASE("initial values = [10]")
{
    auto values = std::vector<int>{ 10 };
    auto tree = SegmentTree{values};
    REQUIRE(tree.get_range_sum(0, 0) == 10);

    tree.update_element(0, 20);
    REQUIRE(tree.get_range_sum(0, 0) == 20);
}

TEST_CASE("initial values = [10, 11]")
{
    auto values = std::vector<int>{ 10, 11 };
    auto tree = SegmentTree{values};
    REQUIRE(tree.get_range_sum(0, 0) == 10);
    REQUIRE(tree.get_range_sum(1, 1) == 11);
    REQUIRE(tree.get_range_sum(0, 1) == 21);

    tree.update_element(0, 20);
    tree.update_element(1, 21);
    REQUIRE(tree.get_range_sum(0, 0) == 20);
    REQUIRE(tree.get_range_sum(1, 1) == 21);
    REQUIRE(tree.get_range_sum(0, 1) == 41);
}

TEST_CASE("initial values = [10, 11, 12]")
{
    auto values = std::vector<int>{ 10, 11, 12 };
    auto tree = SegmentTree{values};

    // query width = 1
    REQUIRE(tree.get_range_sum(0, 0) == 10);
    REQUIRE(tree.get_range_sum(1, 1) == 11);
    REQUIRE(tree.get_range_sum(2, 2) == 12);
    // query width = 2
    REQUIRE(tree.get_range_sum(0, 1) == 21);
    REQUIRE(tree.get_range_sum(1, 2) == 23);
    // query width = 3
    REQUIRE(tree.get_range_sum(0, 2) == 33);

    tree.update_element(0, 20);
    tree.update_element(1, 21);
    tree.update_element(2, 22);

    // query width = 1
    REQUIRE(tree.get_range_sum(0, 0) == 20);
    REQUIRE(tree.get_range_sum(1, 1) == 21);
    REQUIRE(tree.get_range_sum(2, 2) == 22);
    // query width = 2
    REQUIRE(tree.get_range_sum(0, 1) == 41);
    REQUIRE(tree.get_range_sum(1, 2) == 43);
    // query width = 3
    REQUIRE(tree.get_range_sum(0, 2) == 63);
}

TEST_CASE("initial values = [10, 11, 12, 13]")
{
    auto values = std::vector<int>{ 10, 11, 12, 13 };
    auto tree = SegmentTree{values};

    // query width = 1
    REQUIRE(tree.get_range_sum(0, 0) == 10);
    REQUIRE(tree.get_range_sum(1, 1) == 11);
    REQUIRE(tree.get_range_sum(2, 2) == 12);
    REQUIRE(tree.get_range_sum(3, 3) == 13);
    // query width = 2
    REQUIRE(tree.get_range_sum(0, 1) == 21);
    REQUIRE(tree.get_range_sum(1, 2) == 23);
    REQUIRE(tree.get_range_sum(2, 3) == 25);
    // query width = 3
    REQUIRE(tree.get_range_sum(0, 2) == 33);
    REQUIRE(tree.get_range_sum(1, 3) == 36);
    // query width = 4
    REQUIRE(tree.get_range_sum(0, 3) == 46);

    tree.update_element(0, 20);
    tree.update_element(1, 21);
    tree.update_element(2, 22);
    tree.update_element(3, 23);

    // query width = 1
    REQUIRE(tree.get_range_sum(0, 0) == 20);
    REQUIRE(tree.get_range_sum(1, 1) == 21);
    REQUIRE(tree.get_range_sum(2, 2) == 22);
    REQUIRE(tree.get_range_sum(3, 3) == 23);
    // query width = 2
    REQUIRE(tree.get_range_sum(0, 1) == 41);
    REQUIRE(tree.get_range_sum(1, 2) == 43);
    REQUIRE(tree.get_range_sum(2, 3) == 45);
    // query width = 3
    REQUIRE(tree.get_range_sum(0, 2) == 63);
    REQUIRE(tree.get_range_sum(1, 3) == 66);
    // query width = 4
    REQUIRE(tree.get_range_sum(0, 3) == 86);
}
