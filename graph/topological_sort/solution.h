#pragma once

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <digraph.h>

class Solution
{
public:
    std::vector<Digraph::VertexID> solve_topological_sort(const Digraph& graph) const
    {
        if(graph.get_number_of_vertices() == 0)
            return {};

        auto visited_vertices = std::unordered_set<Digraph::VertexID>{};
        auto reversed_result = std::vector<Digraph::VertexID>{};

        for(auto vertex : graph.get_vertex_ids())
        {
            bool was_vertex_already_visited = (visited_vertices.find(vertex) != visited_vertices.cend());
            if(was_vertex_already_visited)
            {
                continue;
            }

            dfs(vertex, graph, visited_vertices, reversed_result);
        }

        std::reverse(reversed_result.begin(), reversed_result.end());
        return reversed_result;
    }

private:
    void dfs(   const Digraph::VertexID vertex,
                const Digraph& graph,
                std::unordered_set<Digraph::VertexID>& visited_vertices,
                std::vector<Digraph::VertexID>& reversed_result) const
    {
        visited_vertices.insert(vertex);
        for(auto adjacent_vertex : graph.get_adjacent_vertex_ids(vertex))
        {
            bool was_vertex_visited = (visited_vertices.find(adjacent_vertex) != visited_vertices.cend());
            if(was_vertex_visited)
                continue;

            dfs(adjacent_vertex, graph, visited_vertices, reversed_result);
        }
        reversed_result.push_back(vertex);
    }
};
