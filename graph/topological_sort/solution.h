#pragma once
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "../graph.h"

class Solution
{
public:
    std::vector<size_t> solve_topological_sort(const Graph& graph) const
    {
        if(graph.get_vertices().empty())
            return {};

        auto visited_vertices = std::unordered_set<const Graph::Vertex*>{};
        auto reversed_result = std::vector<Graph::Vertex::id_type>{};

        for(auto& vertex : graph.get_vertices())
        {
            bool was_vertex_already_visited = (visited_vertices.find(&vertex) != visited_vertices.cend());
            if(was_vertex_already_visited)
            {
                continue;
            }

            dfs(vertex, visited_vertices, reversed_result);
        }

        std::reverse(reversed_result.begin(), reversed_result.end());
        return reversed_result;
    }

private:
    void dfs(   const Graph::Vertex& vertex,
                std::unordered_set<const Graph::Vertex*>& visited_vertices,
                std::vector<Graph::Vertex::id_type>& reversed_result) const
    {
        visited_vertices.insert(&vertex);
        for(auto* adjacent_vertex : vertex.get_adjacent_vertices())
        {
            bool was_vertex_visited = (visited_vertices.find(adjacent_vertex) != visited_vertices.cend());
            if(was_vertex_visited)
                continue;

            dfs(*adjacent_vertex, visited_vertices, reversed_result);
        }
        reversed_result.push_back(vertex.get_id());
    }
};
