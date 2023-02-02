//
// Created by alexgershberg on 02/02/23.
//

//https://leetcode.com/problems/two-sum/

#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::vector<int> result;

        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                auto a = nums.at(i);
                auto b = nums.at(j);

                if ((a + b) == target)
                {
                    result.push_back(i);
                    result.push_back(j);
                    return result;
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums{2, 7, 11, 15};
    auto res = sol.twoSum(nums, 9);
    std::cout << "[" << res.at(0) << "]" << "[" <<  res.at(1) <<"]\n";
}