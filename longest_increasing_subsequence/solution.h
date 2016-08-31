#include <vector>
#include <algorithm>

std::vector<int>::iterator find_last_lower(   std::vector<int>::iterator begin,
                                                std::vector<int>::iterator end,
                                                int num)
{
    if(begin == end)
        return end;

    auto it = std::lower_bound(begin, end, num);
    
    if(it == end)
    {
        return end-1;
    }
    else if(it==begin)
    {
        return end;
    }
    else
    {
        return it-1;
    }
}

std::size_t solution(const std::vector<int>& nums)
{
    auto mins = std::vector<int>{};

    for(auto num : nums)
    {
        auto it = find_last_lower(mins.begin(), mins.end(), num);
        
        if(it==mins.cend())
        {
            if(mins.empty())
            {
                mins.push_back(num);
            }
            else if(mins[0] > num)
            {
                mins[0] = num;
            }
        }
        else
        {
            if(it+1 == mins.cend())
            {
                mins.push_back(num);
            }
            else if(*(it+1) > num)
            {
                *(it+1) = num;
            }
        }
    }

    return mins.size();
}

