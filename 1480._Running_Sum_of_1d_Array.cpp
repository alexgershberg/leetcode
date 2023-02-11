//
// Created by alexgershberg on 11/02/23.
//

//https://leetcode.com/problems/running-sum-of-1d-array/?envType=study-plan&id=level-1

#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> runningSum(std::vector<int>& nums)
    {
        std::vector<int> output;

        int prev = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            int current = nums[i];
            int temp = current + prev;
            output.push_back(temp);
            prev = temp;
        }
        return output;
    }
};