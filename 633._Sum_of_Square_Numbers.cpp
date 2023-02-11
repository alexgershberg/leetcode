//
// Created by alexgershberg on 11/02/23.
//

//https://leetcode.com/problems/sum-of-square-numbers/

#include <cmath>

class Solution {
public:
    bool judgeSquareSum(int c) {
        if (c == 0 || c == 1)
            return true;

        for(int i = 0; i < sqrt(c); i++)
        {
            int square = i * i;
            double first_op = c - square;

            auto isPerectSquare = ceil(std::sqrt(first_op)) == floor(std::sqrt(first_op));
            if (isPerectSquare)
                return true;
        }
        return false;
    }
};