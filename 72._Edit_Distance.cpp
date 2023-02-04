//
// Created by alexgershberg on 03/02/23.
//

//https://leetcode.com/problems/edit-distance/

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <iostream>

/*
                                                                  *             ^
                 ' '  h   o   r   s   e                            \            |
            ' '   0   1   2   3   4   5                           replacing deleting
             r    1   1   2   2   3   4                      <-   inserting   [x]
             o    2   2   1   2   3   4
             s    3   3   2   2   2   3
*/

//Tabulation
int solveTabulation(std::string word1, std::string word2)
{
    auto t = word1.size();
    int rowSize = static_cast<int>(word1.length());
    int colSize = static_cast<int>(word2.length());

    std::vector<std::vector<int>> table(rowSize + 1, std::vector<int>(colSize + 1, 0));
//    table.resize(rowSize + 1, std::vector<int>(colSize + 1, 0));


    for (int i = 0; i <= rowSize; i++)
        table[i][0] = i;

    for (int j = 0; j <= colSize; j++)
        table[0][j] = j;

    for (int i = 1; i <= rowSize; i++)
    {
        for (int j = 1; j <= colSize; j++)
        {
            auto letter_1 = word1[i - 1];
            auto letter_2 = word2[j - 1];

            if (letter_1 == letter_2)
                table[i][j] = table[i - 1][j - 1];
            else
            {
                table[i][j] = 1 + std::min(table[i - 1][j], std::min(table[i][j - 1], table[i - 1][j - 1]));
            }
        }
    }

    return table[rowSize - 1][colSize - 1];
}

//Recursive
int solve(std::string word1, std::string word2, std::map<std::pair<std::string, std::string>, int>& memo)
{
    if (word1.empty())
        return word2.length();

    if (word2.empty())
        return word1.length();

    std::pair<std::string, std::string> key(word1, word2);
    if (memo.find(key) != memo.end())
        return memo[key];

    if (word1 == word2)
    {
        memo[key] = 0;
        return 0;
    }

    auto insert = 0, remove = 0, replace = 0;

    if (word1.at(word1.length() - 1) == word2.at(word2.length() - 1))
    {
        auto same_letter = solve(word1.substr(0, word1.length() - 1), word2.substr(0, word2.length() - 1), memo);
        memo[key] = same_letter;
        return same_letter;
    }

    insert = solve(word1, word2.substr(0, word2.length() - 1), memo);
    remove = solve(word1.substr(0, word1.length() - 1), word2, memo);
    replace = solve(word1.substr(0, word1.length() - 1), word2.substr(0, word2.length() - 1), memo);

    auto result = std::min(insert, std::min(remove, replace)) + 1;
    memo[key] = result;
    return result;
}

class Solution
{
public:
    int minDistance(std::string word1, std::string word2)
    {
//      std::map<std::pair<std::string, std::string>, int> memo;
//      return solve(word1, word2, memo);

        return solveTabulation(word1, word2);
    }
};

int main()
{
    std::string word1 = "horse";
    std::string word2 = "ros";

    Solution sol;
    auto res = sol.minDistance(word1, word2);

//    auto res = lcSolution(word2, word1);
    std::cout << res << std::endl;
}