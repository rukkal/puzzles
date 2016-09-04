#include <cassert>
#include <vector>
#include <algorithm>

//This solution runs in O(log(n)*log(m)) time.
//Simpler and faster O(log(min(n, m))) solutions are available online though.
class Solution
{
public:
    double findMedianSortedArrays(std::vector<int>& a, std::vector<int>& b) const
    {
        if(a.empty())
            return calculateMedian(b);
        else if(b.empty())
            return calculateMedian(a);
        
        bool found;
        double median;
        
        std::tie(found, median) = findMedian(a, b);
        if(found)
            return median;
        
        std::tie(found, median) = findMedian(b, a);
        assert(found);
        return median;
    }
    
private:
    std::pair<bool, double> findMedian(const std::vector<int>& a, const std::vector<int>& b) const
    {
        int low = 0;
        int high = a.size()-1;
        
        while(low <= high)
        {
            int mid = (low+high) / 2;
            
            auto numOfElementsLowerInB = countElementsLower(b, a[mid]);
            auto numOfElementsLowerOrEqualInB = countElementsLowerOrEqual(b, a[mid]);
            
            auto posMedian = static_cast<int>((a.size()+b.size()) / 2);
            
            if(mid + numOfElementsLowerInB == posMedian)
            {
                return {true, calculateMedian(a, b, mid, numOfElementsLowerInB)};
            }
            else if(mid + numOfElementsLowerInB <= posMedian
                && mid + numOfElementsLowerOrEqualInB >= posMedian)
            {
                return {true, a[mid]};
            }
            else if(mid + numOfElementsLowerInB < posMedian)
            {
                low = mid+1;
            }
            else
            {
                high = mid-1;
            }
        }
        
        return {false, 0.0};
    }
    
    int countElementsLower(const std::vector<int>& nums, int value) const
    {
        auto pos = std::lower_bound(nums.cbegin(), nums.cend(), value);
        return static_cast<int>(std::distance(nums.cbegin(), pos));
    }
    
    int countElementsLowerOrEqual(const std::vector<int>& nums, int value) const
    {
        auto pos = std::upper_bound(nums.cbegin(), nums.cend(), value);
        return static_cast<int>(std::distance(nums.cbegin(), pos));
    }
    
    double calculateMedian(const std::vector<int>& nums) const
    {
        if(nums.size() % 2 == 1)
        {
            return static_cast<double>(nums[nums.size()/2]);
        }
        else
        {
            return static_cast<double>(nums[nums.size()/2 - 1] + nums[nums.size()/2]) / 2.0;
        }
    }
    
    double calculateMedian(const std::vector<int>& a, const std::vector<int>& b, int midA, int numOfElementsLowerInB) const
    {
        if((a.size()+b.size()) % 2 == 1)
        {
            return static_cast<double>(a[midA]);
        }
        else
        {
            int elementBeforeMid;
            if(midA == 0)
            {
                assert(numOfElementsLowerInB);
                elementBeforeMid = b[numOfElementsLowerInB-1];
            }
            else if(numOfElementsLowerInB == 0)
            {
                elementBeforeMid = a[midA-1];
            }
            else
            {
                elementBeforeMid = std::max(a[midA-1], b[numOfElementsLowerInB-1]);
            }
            return (static_cast<double>(a[midA]) + static_cast<double>(elementBeforeMid)) / 2.0;
        }
    }
};
