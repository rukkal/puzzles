#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <unordered_set>


class Digraph
{
public:
    using VertexID = size_t;

public:
    Digraph() = default;

    Digraph(size_t number_of_vertices)
        : number_of_vertices(number_of_vertices)
        , adjacency_matrix(number_of_vertices * number_of_vertices)
    {}

    const std::vector<VertexID> get_vertex_ids() const
    {
        auto vertex_ids = std::vector<VertexID>{};
        for(VertexID id = 0; id < get_number_of_vertices(); ++id)
        {
            vertex_ids.push_back(id);
        }
        return vertex_ids;
    }

    const std::vector<VertexID> get_adjacent_vertex_ids(VertexID from) const
    {
        auto adjacent_vertex_ids = std::vector<VertexID>{};
        for(VertexID to = 0; to < get_number_of_vertices(); ++to)
        {
            if(get_adjacency_matrix_entry(from, to))
            {
                adjacent_vertex_ids.push_back(to);
            }
        }
        return adjacent_vertex_ids;
    }

    void add_edge(VertexID from, VertexID to)
    {
        assert(is_valid_vertex_id(from));
        assert(is_valid_vertex_id(to));
        set_adjacency_matrix_entry(from, to, true);
    }

    bool has_path(Digraph::VertexID from, Digraph::VertexID to) const
    {
        assert(is_valid_vertex_id(from));
        assert(is_valid_vertex_id(to));
        auto visited_vertices = std::unordered_set<Digraph::VertexID>{};
        return has_path_dfs(from, to, visited_vertices);
    }

    size_t get_number_of_vertices() const
    {
        return number_of_vertices;
    }

private:
    bool is_valid_vertex_id(VertexID id) const
    {
        return id < get_number_of_vertices();
    }

    bool get_adjacency_matrix_entry(VertexID from, VertexID to) const
    {
        return adjacency_matrix[from * get_number_of_vertices() + to];
    }

    void set_adjacency_matrix_entry(VertexID from, VertexID to, bool entry_value)
    {
        adjacency_matrix[from * get_number_of_vertices() + to] = entry_value;
    }

    bool has_path_dfs(Digraph::VertexID from, Digraph::VertexID to, std::unordered_set<Digraph::VertexID>& visited_vertices) const
    {
        if(from == to)
        {
            return true;
        }

        visited_vertices.insert(from);
        for(auto adj : get_adjacent_vertex_ids(from))
        {
            bool was_vertex_visited = (visited_vertices.find(adj) != visited_vertices.cend());
            if(was_vertex_visited)
            {
                continue;
            }

            if(has_path_dfs(adj, to, visited_vertices))
            {
                return true;
            }
        }
        return false;
    }


private:
    size_t number_of_vertices;
    std::vector<bool> adjacency_matrix;
};
