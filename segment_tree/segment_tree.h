#pragma once

#include <cassert>
#include <cmath>
#include <vector>

class SegmentTree
{
public:
    SegmentTree(const std::vector<int>& values)
        : number_of_leafs(values.size())
    {
        if(number_of_leafs == 0)
        {
            return;
        }

        auto n = static_cast<float>(values.size());
        auto last_level_size = pow(2, ceil(log2(n)));
        auto tree_size = 2*last_level_size - 1;
        tree.resize(tree_size);

        build_tree(values);
    }

    void update_element(size_t element_idx, int element_value)
    {
        update_element_rec(element_idx, element_value, 0, 0, number_of_leafs-1);
    }

    int get_range_sum(size_t query_start, size_t query_end) const
    {
        assert(query_start <= query_end);
        assert(query_end < number_of_leafs);

        return get_range_sum_rec(query_start, query_end, 0, 0, number_of_leafs-1);
    }

private:
    void build_tree(const std::vector<int>& values)
    {
        build_tree_rec(values, 0, 0, number_of_leafs-1);
    }

    int build_tree_rec(const std::vector<int>& values, size_t node_idx, size_t range_start, size_t range_end)
    {
        if(range_start == range_end)
        {
            tree[node_idx] = values[range_start];
            return values[range_start];
        }

        auto value_left = build_tree_rec(values, left_child_idx(node_idx), range_start, (range_start + range_end) / 2);
        auto value_right = build_tree_rec(values, right_child_idx(node_idx), (range_start + range_end) / 2 + 1, range_end);

        auto value_current_node = value_left + value_right;
        tree[node_idx] = value_current_node;

        return value_current_node;
    }

    void update_element_rec(size_t element_idx, int element_value, size_t node_idx, size_t range_start, size_t range_end)
    {
        if(range_start == range_end)
        {
            assert(range_start == element_idx);
            tree[node_idx] = element_value;
            return;
        }

        auto left_child_range_end = (range_start + range_end) / 2;

        if(element_idx <= left_child_range_end)
        {
            update_element_rec(element_idx, element_value, left_child_idx(node_idx), range_start, left_child_range_end);
        }
        else
        {
            update_element_rec(element_idx, element_value, right_child_idx(node_idx), left_child_range_end+1, range_end);
        }

        tree[node_idx] = tree[left_child_idx(node_idx)] + tree[right_child_idx(node_idx)];
    }

    int get_range_sum_rec(size_t query_start, size_t query_end, size_t node_idx, size_t range_start, size_t range_end) const
    {
        if(query_start <= range_start && range_end <= query_end)
        {
            return tree[node_idx];
        }

        int range_sum = 0;
        auto left_child_range_end = (range_start + range_end) / 2;

        if(query_start <= left_child_range_end)
        {
            range_sum += get_range_sum_rec(query_start, query_end, left_child_idx(node_idx), range_start, left_child_range_end);
        }

        if(query_end > left_child_range_end)
        {
            range_sum += get_range_sum_rec(query_start, query_end, right_child_idx(node_idx), left_child_range_end+1, range_end);
        }

        return range_sum;
    }

    size_t left_child_idx(size_t idx) const
    {
        return idx*2+1;
    }

    size_t right_child_idx(size_t idx) const
    {
        return idx*2+2;
    }

private:
    size_t number_of_leafs;
    std::vector<int> tree;
};
