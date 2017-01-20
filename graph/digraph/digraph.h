#pragma once

#include <cassert>
#include <cstddef>
#include <limits>
#include <algorithm>
#include <vector>
#include <unordered_set>

class Digraph
{
public:
    using VertexID = size_t;
    using weight_type = int;

    static const weight_type WEIGHT_INFINITE = std::numeric_limits<weight_type>::max();

public:
    Digraph() = default;

    Digraph(size_t number_of_vertices)
        : number_of_vertices(number_of_vertices)
        , adjacency_matrix(number_of_vertices * number_of_vertices)
        , weights_matrix(number_of_vertices * number_of_vertices, weight_type(WEIGHT_INFINITE))
    {
    }

    void add_edge(VertexID from, VertexID to)
    {
        assert(is_valid_vertex_id(from));
        assert(is_valid_vertex_id(to));
        set_matrix_entry(adjacency_matrix, from, to, true);
    }

    void set_weight(VertexID from, VertexID to, weight_type weight)
    {
        assert(is_valid_vertex_id(from));
        assert(is_valid_vertex_id(to));
        set_matrix_entry(weights_matrix, from, to, weight);
    }

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
            if(get_matrix_entry(adjacency_matrix, from, to))
            {
                adjacent_vertex_ids.push_back(to);
            }
        }
        return adjacent_vertex_ids;
    }

    std::vector<std::vector<weight_type>> get_weights_matrix() const
    {
        auto matrix = std::vector<std::vector<weight_type>>{};
        auto n = get_number_of_vertices();

        for(size_t i=0; i<n; ++i)
        {
            auto weight_begin = weights_matrix.begin() + i*n;
            auto weight_end = weights_matrix.begin() + i*n + n;
            auto row = std::vector<weight_type>(weight_begin, weight_end);
            matrix.emplace_back(std::move(row));
        }

        return matrix;
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

    template<class T>
    T get_matrix_entry(const std::vector<T>& matrix, VertexID i, VertexID j) const
    {
        return matrix[i * get_number_of_vertices() + j];
    }

    template<class T>
    void set_matrix_entry(std::vector<T>& matrix, VertexID i, VertexID j, const T& value)
    {
        matrix[i * get_number_of_vertices() + j] = value;
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
    std::vector<weight_type> weights_matrix;
};
