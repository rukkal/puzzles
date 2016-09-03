#include <vector>
#include <functional>
#include <unordered_map>

struct MyPoint
{
    int x, y;
};

bool operator==(const MyPoint& p1, const MyPoint& p2)
{
   return p1.x==p2.x && p1.y==p2.y;
}

namespace std
{
    template<> struct hash<MyPoint>
    {
        typedef MyPoint argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& p) const
        {
            return p.x + p.y;
        }
    };
}

class Solution
{
public:
    bool isRectangleCover(std::vector<std::vector<int>>& rectangles)
    {
        makePointsMap(rectangles);
        if(!arePointsOccurrencesCorrect())
            return false;
        
        auto expectedArea = calculateExpectedArea();
        auto actualArea = calculateActualArea(rectangles);
        if(actualArea != expectedArea)
            return false;
        
        return true;
    }
    
    void makePointsMap(std::vector<std::vector<int>>& rectangles)
    {
        for(const auto& r : rectangles)
        {
            {
                MyPoint p{r[0], r[1]};
                ++map[p];
            }
            {
                MyPoint p{r[0], r[3]};
                ++map[p];
            }
            {
                MyPoint p{r[2], r[1]};
                ++map[p];
            }
            {
                MyPoint p{r[2], r[3]};
                ++map[p];
            }
        }
    }
    
    bool arePointsOccurrencesCorrect()
    {
        size_t oddOccurrences = 0;
        for(auto it=map.cbegin(); it!=map.cend(); ++it)
        {
            const auto occurrences = it->second;
            if(occurrences % 2 != 0)
            {
                if(occurrences != 1)
                    return false;
                ++oddOccurrences;
            }
        }
        return oddOccurrences == 4;
    }
    
    unsigned long long calculateExpectedArea()
    {
        auto corners = std::vector<MyPoint>{};
        for(auto it=map.cbegin(); it!=map.cend(); ++it)
        {
            if(it->second == 1)
                corners.push_back(it->first);
        }
        assert(corners.size() == 4);
        
        unsigned long long left = std::min_element(corners.cbegin(), corners.cend(), [](const MyPoint& c1, const MyPoint& c2){ return c1.x < c2.x; } )->x;
        unsigned long long right = std::max_element(corners.cbegin(), corners.cend(), [](const MyPoint& c1, const MyPoint& c2){ return c1.x < c2.x; } )->x;
        
        unsigned long long bottom = std::min_element(corners.cbegin(), corners.cend(), [](const MyPoint& c1, const MyPoint& c2){ return c1.y < c2.y; } )->y;
        unsigned long long top = std::max_element(corners.cbegin(), corners.cend(), [](const MyPoint& c1, const MyPoint& c2){ return c1.y < c2.y; } )->y;
        
        return (right - left) * (top - bottom);
    }
    
    unsigned long long calculateActualArea(const std::vector<std::vector<int>>& rectangles)
    {
        unsigned long long area = 0;
        for(const auto& r : rectangles)
        {
            unsigned long long width = r[2]-r[0];
            unsigned long long height = r[3]-r[1];
            area += width*height;
        }
        return area;
    }
    
private:
    std::unordered_map<MyPoint, size_t> map;
};
