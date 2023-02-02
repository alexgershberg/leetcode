//
// Created by alexgershberg on 02/02/23.
//

//https://leetcode.com/problems/median-of-two-sorted-arrays/

#include <vector>
#include <cmath>
#include <iostream>

void merge(std::vector<int>& vec1, std::vector<int>& vec2, std::vector<int>& output)
{
    auto vec1_it = vec1.begin();
    auto vec2_it = vec2.begin();

    while (vec1_it != vec1.end() && vec2_it != vec2.end())
    {
        auto vec1_val = *vec1_it;
        auto vec2_val = *vec2_it;

        if (vec1_val <= vec2_val)
        {
            output.push_back(vec1_val);
            vec1_it++;
        }
        else
        {
            output.push_back(vec2_val);
            vec2_it++;
        }
    }

    while (vec1_it != vec1.end())
    {
        auto vec1_val = *vec1_it;
        output.push_back(vec1_val);
        vec1_it++;
    }

    while (vec2_it != vec2.end())
    {
        auto vec2_val = *vec2_it;
        output.push_back(vec2_val);
        vec2_it++;
    }
}

class Solution
{
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::vector<int> merge_result;
        merge(nums1, nums2, merge_result);

        auto size = static_cast<int>(merge_result.size());

        if (merge_result.size() % 2)
        {
            //odd
             int index = floor(size/2);
             return merge_result.at(index);
        }
        else
        {
            //even
            int index = floor(size/2);
            auto result = (merge_result.at(index) + merge_result.at(index - 1)) / 2.0;
            return result;
        }
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums1{1, 2};
    std::vector<int> nums2{3, 4};
    auto res = sol.findMedianSortedArrays(nums1, nums2);
    std::cout << res << std::endl;
}