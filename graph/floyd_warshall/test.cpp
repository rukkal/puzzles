#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "solution.h"

constexpr auto INF = Digraph::WEIGHT_INFINITE;

std::vector<std::vector<Digraph::weight_type>> make_costs(std::vector<std::vector<Digraph::weight_type>> costs)
{
    return costs;
}

TEST_CASE("empty graph")
{
    auto graph = Digraph();
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    REQUIRE(actual_costs.empty());
}

TEST_CASE("V={0} E={}")
{
    auto graph = Digraph(1);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({ {INF} });
    REQUIRE(actual_costs == expected_costs);
}

TEST_CASE("V={0} E={(0, 0)} w(0, 0)=10")
{
    auto graph = Digraph(1);
    graph.add_edge(0, 0);
    graph.set_weight(0, 0, 10);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({ {10} });
    REQUIRE(actual_costs == expected_costs);
}

TEST_CASE("V={0, 1} E={}")
{
    auto graph = Digraph(2);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({  {INF, INF},
                                        {INF, INF} });
    REQUIRE(actual_costs == expected_costs);
}

TEST_CASE("V={0, 1} E={(0, 1)} w(0, 1)=10")
{
    auto graph = Digraph(2);
    graph.add_edge(0, 1);
    graph.set_weight(0, 1, 10);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({  {INF, 10},
                                        {INF, INF} });
    REQUIRE(actual_costs == expected_costs);
}

TEST_CASE("V={0, 1} E={(0, 1)} w(0, 1)=10 w(1, 0)=11")
{
    auto graph = Digraph(2);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    graph.set_weight(0, 1, 10);
    graph.set_weight(1, 0, 11);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({  {21, 10},
                                        {11, 21} });
    REQUIRE(actual_costs == expected_costs);
}

TEST_CASE("V={0, 1, 2, 3} E={(0, 1), (1, 3), (0, 2), (2, 3)} w(0, 1)=1 w(1, 3)=2 w(0, 2)=10 w(2, 3)=11")
{
    auto graph = Digraph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 3);
    graph.add_edge(0, 2);
    graph.add_edge(2, 3);
    graph.set_weight(0, 1, 1);
    graph.set_weight(1, 3, 2);
    graph.set_weight(0, 2, 10);
    graph.set_weight(2, 3, 11);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({  {INF, 1, 10, 3},
                                        {INF, INF, INF, 2},
                                        {INF, INF, INF, 11},
                                        {INF, INF, INF, INF} });
    REQUIRE(actual_costs == expected_costs);
}

TEST_CASE("V={0, 1, 2, 3} E={(0, 1), (1, 3), (0, 2), (2, 3), (3, 0)} w(0, 1)=1 w(1, 3)=2 w(0, 2)=10 w(2, 3)=11 w(3, 0)=100")
{
    auto graph = Digraph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 3);
    graph.add_edge(0, 2);
    graph.add_edge(2, 3);
    graph.set_weight(0, 1, 1);
    graph.set_weight(1, 3, 2);
    graph.set_weight(0, 2, 10);
    graph.set_weight(2, 3, 11);
    graph.set_weight(3, 0, 100);
    auto actual_costs = Solution{}.solve_floyd_warshall(graph);
    auto expected_costs = make_costs({  {103, 1, 10, 3},
                                        {102, 103, 112, 2},
                                        {111, 112, 121, 11},
                                        {100, 101, 110, 103} });
    REQUIRE(actual_costs == expected_costs);
}
