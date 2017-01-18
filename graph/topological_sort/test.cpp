#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../graph.h"
#include "solution.h"

class checker
{
public:
    checker(const Graph& graph) : graph(graph)
    {
    }

    bool is_valid_topological_sort(const std::vector<Graph::VertexID>& topological_sort) const
    {
        if(topological_sort.size() != graph.get_number_of_vertices())
        {
            return false;
        }

        for(size_t i=0; i<topological_sort.size(); ++i)
        {
            for(size_t j=i+1; j<topological_sort.size(); ++j)
            {
                auto vertex0 = topological_sort[i];
                auto vertex1 = topological_sort[j];
                if(!graph.has_path(vertex0, vertex1) && graph.has_path(vertex1, vertex0))
                {
                    return false;
                }
            }
        }

        return true;
    }

private:
    const Graph& graph;
};

TEST_CASE("empty graph")
{
    auto graph = Graph{};
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(topological_sort == std::vector<Graph::VertexID>{});
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0}")
{
    auto graph = Graph{ 1 };
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(topological_sort == std::vector<Graph::VertexID>{0});
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1}")
{
    auto graph = Graph{ 2 };
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(topological_sort == (std::vector<Graph::VertexID>{1, 0}));
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1} E={{0, 1}}")
{
    auto graph = Graph{ 2 };
    graph.add_directed_edge(0, 1);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(topological_sort == (std::vector<Graph::VertexID>{0, 1}));
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1,2} E={{0,1}, {1,2}}")
{
    auto graph = Graph{ 3 };
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1,2} E={{0,1}}")
{
    auto graph = Graph{ 3 };
    graph.add_directed_edge(0, 1);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(topological_sort == (std::vector<Graph::VertexID>{2, 0, 1}));
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1,2} E={{0,1}, {0,2}}")
{
    auto graph = Graph{ 3 };
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(0, 2);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1,2} E={{0,1}, {0,2}, {1,2}}")
{
    auto graph = Graph{ 3 };
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(0, 2);
    graph.add_directed_edge(1, 2);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1,2,3} E={{0,1}, {1,2}, {0,3}, {3,2}}")
{
    auto graph = Graph{ 4 };
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(0, 3);
    graph.add_directed_edge(3, 2);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}

TEST_CASE("V={0,1,2,3,4,5} E={{0,1}, {0,2}, {1, 2}, {1, 3}, {2, 4}, {4, 3}, {3, 5}}")
{
    auto graph = Graph{ 6 };
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(0, 2);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(1, 3);
    graph.add_directed_edge(2, 4);
    graph.add_directed_edge(4, 3);
    graph.add_directed_edge(3, 5);
    auto topological_sort = Solution{}.solve_topological_sort(graph);
    REQUIRE(checker{graph}.is_valid_topological_sort(topological_sort));
}
