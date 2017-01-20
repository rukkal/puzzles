#pragma once

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <digraph.h>

class Solution
{
public:
    std::vector<std::vector<int>> solve_floyd_warshall(const Digraph& graph) const
    {
        auto costs = graph.get_weights_matrix();
        auto n = graph.get_number_of_vertices();

        for(size_t k=0; k<n; ++k)
        {
            for(size_t i=0; i<n; ++i)
            {
                for(size_t j=0; j<n; ++j)
                {
                    if(costs[i][k] == Digraph::WEIGHT_INFINITE || costs[k][j] == Digraph::WEIGHT_INFINITE)
                    {
                        continue;
                    }
                    costs[i][j] = std::min(costs[i][j], costs[i][k] + costs[k][j]);
                }
            }
        }

        return costs;
    }
};
