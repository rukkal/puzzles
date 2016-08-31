#include <vector>
#include <algorithm>

void solution(std::vector<std::vector<int>>& m)
{
    if(m.empty())
        return;

    for(auto rowbeg=0ul; rowbeg<m.size()/2; ++rowbeg)
    {
        auto rowend = m.size()-1-rowbeg;
        auto colbeg = rowbeg;
        auto colend = colbeg + (rowend - rowbeg);
        
        for(auto col=colbeg; col<colend; ++col)
        {
            auto& elt1 = m[rowbeg][col];
            auto& elt2 = m[rowbeg+(col-colbeg)][colend];
            auto& elt3 = m[rowend][colend-(col-colbeg)];
            auto& elt4 = m[rowend-(col-colbeg)][colbeg];
            std::swap(elt1, elt2);
            std::swap(elt3, elt4);
            std::swap(elt1, elt3);
        }
    }
}



