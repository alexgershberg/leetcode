//
// Created by alexgershberg on 11/02/23.
//

//https://leetcode.com/problems/find-pivot-index/?envType=study-plan&id=level-1

#include <vector>

class Solution
{
public:
    int sum(std::vector<int>& nums)
    {
        int output = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            output += nums[i];
        }
        return output;
    }

    int pivotIndex(std::vector<int>& nums)
    {
        int left_sum = 0;
        int right_sum = sum(nums);
        for (int index = 0; index < nums.size(); ++index)
        {
            if(left_sum == right_sum - nums[index])
                return index;
            left_sum += nums[index];
            right_sum -= nums[index];
        }
        return -1;
    }
};