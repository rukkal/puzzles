#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "digraph.h"

TEST_CASE("empty graph")
{
    auto graph = Digraph();
    REQUIRE(graph.get_number_of_vertices() == 0);
    REQUIRE(graph.get_vertex_ids() == std::vector<Digraph::VertexID>{});
}

TEST_CASE("V={0} E={}")
{
    auto graph = Digraph(1);
    REQUIRE(graph.get_number_of_vertices() == 1);
    REQUIRE(graph.get_vertex_ids() == std::vector<Digraph::VertexID>{ 0 });
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ });
}

TEST_CASE("V={0} E={(1, 1)}")
{
    auto graph = Digraph(1);
    graph.add_edge(0, 0);
    REQUIRE(graph.get_number_of_vertices() == 1);
    REQUIRE(graph.get_vertex_ids() == std::vector<Digraph::VertexID>{ 0 });
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ 0 });
}

TEST_CASE("V={0, 1} E={}")
{
    auto graph = Digraph(2);
    REQUIRE(graph.get_number_of_vertices() == 2);
    REQUIRE(graph.get_vertex_ids() == (std::vector<Digraph::VertexID>{ 0, 1 }));
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ });
    REQUIRE(graph.get_adjacent_vertex_ids(1) == std::vector<Digraph::VertexID>{ });
}

TEST_CASE("V={0, 1} E={(0, 1)}")
{
    auto graph = Digraph(2);
    graph.add_edge(0, 1);
    REQUIRE(graph.get_number_of_vertices() == 2);
    REQUIRE(graph.get_vertex_ids() == (std::vector<Digraph::VertexID>{ 0, 1 }));
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ 1 });
    REQUIRE(graph.get_adjacent_vertex_ids(1) == std::vector<Digraph::VertexID>{ });
}

TEST_CASE("V={0, 1} E={(0, 1), (1, 0)}")
{
    auto graph = Digraph(2);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    REQUIRE(graph.get_number_of_vertices() == 2);
    REQUIRE(graph.get_vertex_ids() == (std::vector<Digraph::VertexID>{ 0, 1 }));
    REQUIRE(graph.get_adjacent_vertex_ids(0) == std::vector<Digraph::VertexID>{ 1 });
    REQUIRE(graph.get_adjacent_vertex_ids(1) == std::vector<Digraph::VertexID>{ 0 });
}
