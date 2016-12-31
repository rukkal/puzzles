#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <vector>

class Graph
{
public:
    class Vertex
    {
    public:
        using id_type = size_t;
    public:
        Vertex(id_type id) : id(id)
        {}

        id_type get_id() const
        {
            return id;
        }

        const std::vector<const Vertex*>& get_adjacent_vertices() const
        {
            return adjacent_vertices;
        }

        std::vector<const Vertex*>& get_adjacent_vertices()
        {
            return adjacent_vertices;
        }

    private:
        id_type id;
        std::vector<const Vertex*> adjacent_vertices;
    };

public:
    Graph() = default;

    Graph(size_t number_of_vertices)
    {
        vertices.reserve(number_of_vertices);
        for(size_t i=0; i<number_of_vertices; ++i)
        {
            vertices.push_back(Vertex(i));
        }
    }

    const Vertex& get_vertex(Vertex::id_type id) const
    {
        return vertices[id];
    }

    const std::vector<Vertex>& get_vertices() const
    {
        return vertices;
    }

    void add_directed_edge(Vertex::id_type from, Vertex::id_type to)
    {
        assert(is_valid_vertex_id(from));
        assert(is_valid_vertex_id(to));
        auto& from_vertex = vertices[from];
        auto& to_vertex = vertices[to];
        from_vertex.get_adjacent_vertices().push_back(&to_vertex);
    }

private:
    bool is_valid_vertex_id(Vertex::id_type id) const
    {
        return id < vertices.size();
    }

private:
    std::vector<Vertex> vertices;
};
