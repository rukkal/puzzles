#include <cassert>
#include <vector>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

class Solution
{
public:
    // Find a valid sequence by searching an eulear cycle in the De Bruijn Graph.
    // note: there is a much faster and simpler way to calculate De Bruijn sequences.
    // See Frank Ruskey's algorithm on wikipedia (https://en.wikipedia.org/wiki/De_Bruijn_sequence)
    std::vector<size_t> solveDeBruijnSequence(size_t alphabet_size, size_t sequence_order) const
    {
        if(sequence_order==0)
        {
            return { };
        }

        assert(alphabet_size > 0);
        if(sequence_order==1)
        {
           return { 0 };
        }

        auto sequence = std::forward_list<size_t>{};
        auto it = sequence.cbefore_begin();
        for(size_t i=0; i<sequence_order-1; ++i)
        {
            it = sequence.insert_after(it, 0);
        }

        auto graph = std::unordered_map<vertex_id, vertex_state>{};
        graph[0].insert_position = it;
        auto to_be_revisited = std::unordered_set<vertex_id>{ 0 };

        while(!to_be_revisited.empty())
        {
            vertex_id crt_vertex = *to_be_revisited.cbegin();
            while(graph[crt_vertex].num_of_out_arcs_so_far < alphabet_size)
            {
                auto crt_symbol = graph[crt_vertex].num_of_out_arcs_so_far++;
                auto next_insert_position = sequence.insert_after(graph[crt_vertex].insert_position, crt_symbol);

                if(graph[crt_vertex].num_of_out_arcs_so_far < alphabet_size)
                {
                    to_be_revisited.insert(crt_vertex);
                }
                else
                {
                    to_be_revisited.erase(to_be_revisited.find(crt_vertex));
                }

                vertex_id next_vertex = get_next_vertex_id(crt_vertex, crt_symbol, alphabet_size, sequence_order);
                auto& next_state = graph[next_vertex];
                next_state.insert_position = next_insert_position;

                crt_vertex = next_vertex;
            }
        }

        // remove trailing order-1 symbols (they are redundant if you consider that the sequence wraps around)
        auto sequence_vec = std::vector<size_t>(sequence.cbegin(), sequence.cend());
        sequence_vec.erase(sequence_vec.cend()-sequence_order+1, sequence_vec.cend());
        return sequence_vec;
    }

private:
    using vertex_id = size_t;

    struct vertex_state
    {
        size_t num_of_out_arcs_so_far{ 0 };
        typename std::forward_list<size_t>::const_iterator insert_position;
    };

    vertex_id get_next_vertex_id(vertex_id crt_id, size_t crt_symbol, size_t alphabet_size, size_t subsequence_length) const
    {
        size_t max_id_plus_one = 1;
        for(size_t i=0; i<subsequence_length-1; ++i)
        {
            max_id_plus_one *= alphabet_size;
        }
        size_t next_id = crt_id;
        next_id *= alphabet_size;
        next_id %= max_id_plus_one;
        next_id += crt_symbol;
        return next_id;
    }
};
