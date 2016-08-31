#include <vector>
#include <algorithm>

void solution(std::vector<std::vector<int>>& m)
{
    if(m.empty() || m[0].empty())
        return;

    auto first_row_contains_zero =
        std::any_of(m[0].begin(), m[0].end(), [](auto elt){ return elt==0; });

    auto first_col_contains_zero =
        std::any_of(m.begin(), m.end(), [](const auto& row){ return row[0]==0; });

    for(auto i=1ul; i<m.size(); ++i)
        for(auto j=1ul; j<m[0].size(); ++j)
            if(m[i][j]==0)
            {
                m[0][j]=0;
                m[i][0]=0;
            }
    

    for(auto i=1ul; i<m.size(); ++i)
        for(auto j=1ul; j<m[0].size(); ++j)
            if(m[0][j]==0 || m[i][0]==0)
            {
                m[i][j] = 0;
            }
    
    if(first_row_contains_zero)
    {
        std::fill(m[0].begin(), m[0].end(), 0);
    }

    if(first_col_contains_zero)
    {
        std::for_each(m.begin(), m.end(), [](auto& row){ row[0]=0; });
    }
}



