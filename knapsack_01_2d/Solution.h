#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>

class Solution
{
public:
   struct Item
   {
      int value;
      int weight1;
      int weight2;
   };

public:
   int solveKnappsack(const std::vector<Item>& items, int limit0, int limit1) const
   {
      assert(limit0 > 0);
      assert(limit1 > 0);

      auto totalValuesCrtItem = std::vector<int>((limit0+1) * (limit1+1));
      auto totalValuesPrevItem = std::vector<int>((limit0+1) * (limit1+1));

      for(const auto& item : items)
      {
         std::swap(totalValuesCrtItem, totalValuesPrevItem);
         std::fill(totalValuesCrtItem.begin(), totalValuesCrtItem.end(), 0);

         for(int crtLimit0=1; crtLimit0<=limit0; ++crtLimit0)
         {
            for(int crtLimit1=1; crtLimit1<=limit1; ++crtLimit1)
            {
               int totalValueWithoutCrtItem = totalValuesPrevItem[crtLimit0*limit1 + crtLimit1];
               int totalValueWithCrtItem;
               if(item.weight1 > crtLimit0 || item.weight2 > crtLimit1)
               {
                  totalValueWithCrtItem = 0;
               }
               else
               {
                  totalValueWithCrtItem =
                     totalValuesPrevItem[(crtLimit0-item.weight1)*limit1 + (crtLimit1-item.weight2)]
                     + item.value;
               }
               auto totalValueCrtItem = std::max(totalValueWithoutCrtItem, totalValueWithCrtItem);
               totalValuesCrtItem[crtLimit0*limit1 + crtLimit1] = totalValueCrtItem;
            }
         }
      }

      return totalValuesCrtItem[limit0*limit1 + limit1];
   }
};
