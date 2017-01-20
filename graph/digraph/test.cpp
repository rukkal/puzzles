#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "digraph.h"

std::vector<std::vector<Digraph::weight_type>> make_weights(const std::vector<std::vector<Digraph::weight_type>>& weights)
{
    return weights;
}

TEST_CASE("empty graph")
{
    auto graph = Digraph();
    REQUIRE(graph.get_number_of_vertices() == 0);
    REQUIRE(graph.get_vertex_ids() == std::vector<Digraph::VertexID>{});
    REQUIRE(graph.get_weights_matrix().empty());
}

TEST_CASE("V={0} E={}")
{
    auto graph = Digraph(1);
    auto expected_weights = make_weights({ {Digraph::WEIGHT_INFINITE} });
    REQUIRE(graph.get_number_of_vertices() == 1);
    REQUIRE(graph.get_vertex_ids() == std::vector<Digraph::VertexID>{ 0 });
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ });
    REQUIRE(graph.get_weights_matrix() == expected_weights);
}

TEST_CASE("V={0} E={(1, 1) w(1, 1)=10}")
{
    auto graph = Digraph(1);
    graph.add_edge(0, 0);
    graph.set_weight(0, 0, 10);
    auto expected_weights = make_weights({ {10} });
    REQUIRE(graph.get_number_of_vertices() == 1);
    REQUIRE(graph.get_vertex_ids() == std::vector<Digraph::VertexID>{ 0 });
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ 0 });
    REQUIRE(graph.get_weights_matrix() == expected_weights);
}

TEST_CASE("V={0, 1} E={}")
{
    auto graph = Digraph(2);
    auto expected_weights = make_weights({  {Digraph::WEIGHT_INFINITE, Digraph::WEIGHT_INFINITE},
                                            {Digraph::WEIGHT_INFINITE, Digraph::WEIGHT_INFINITE} });
    REQUIRE(graph.get_number_of_vertices() == 2);
    REQUIRE(graph.get_vertex_ids() == (std::vector<Digraph::VertexID>{ 0, 1 }));
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ });
    REQUIRE(graph.get_adjacent_vertex_ids(1) == std::vector<Digraph::VertexID>{ });
    REQUIRE(graph.get_weights_matrix() == expected_weights);
}

TEST_CASE("V={0, 1} E={(0, 1)} w(0, 1)=10")
{
    auto graph = Digraph(2);
    graph.add_edge(0, 1);
    graph.set_weight(0, 1, 10);
    auto expected_weights = make_weights({  {Digraph::WEIGHT_INFINITE, 10},
                                            {Digraph::WEIGHT_INFINITE, Digraph::WEIGHT_INFINITE} });
    REQUIRE(graph.get_number_of_vertices() == 2);
    REQUIRE(graph.get_vertex_ids() == (std::vector<Digraph::VertexID>{ 0, 1 }));
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ 1 });
    REQUIRE(graph.get_adjacent_vertex_ids(1) == std::vector<Digraph::VertexID>{ });
    REQUIRE(graph.get_weights_matrix() == expected_weights);
}

TEST_CASE("V={0, 1} E={(0, 1), (1, 0)}")
{
    auto graph = Digraph(2);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    graph.set_weight(0, 1, 10);
    graph.set_weight(1, 0, 11);
    auto expected_weights = make_weights({  {Digraph::WEIGHT_INFINITE, 10},
                                            {11, Digraph::WEIGHT_INFINITE} });
    REQUIRE(graph.get_number_of_vertices() == 2);
    REQUIRE(graph.get_vertex_ids() == (std::vector<Digraph::VertexID>{ 0, 1 }));
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ 1 });
    REQUIRE(graph.get_adjacent_vertex_ids(1) == std::vector<Digraph::VertexID>{ 0 });
    REQUIRE(graph.get_weights_matrix() == expected_weights);
}
