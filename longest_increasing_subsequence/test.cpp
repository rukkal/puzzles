#include <gtest/gtest.h>
#include "solution.h"

TEST(test, max_length_0)
{
    auto nums = std::vector<int>{};
    auto expected = 0;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_one__one_element)
{
    auto nums = std::vector<int>{4};
    auto expected = 1;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_one__strictly_decreasing)
{
    auto nums = std::vector<int>{2, 1, 0, -1, -2};
    auto expected = 1;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_one__equal_elements)
{
    auto nums = std::vector<int>{4, 4, 4, 4, 4};
    auto expected = 1;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_one__n_elements)
{
    auto nums = std::vector<int>{2, 1, 1, 0, -1, -1};
    auto expected = 1;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_two__two_elements)
{
    auto nums = std::vector<int>{4, 5};
    auto expected = 2;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_two__n_elements)
{
    auto nums = std::vector<int>{-1, -1, 1, 1, 1, 0};
    auto expected = 2;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

TEST(test, max_length_n)
{
    auto nums = std::vector<int>{100, 99, 98, 0, 99, 100, 1, 101, 2, 3, 4, 5, 6};
    auto expected = 7;
    auto actual = solution(nums);
    EXPECT_EQ(expected, actual);
}

