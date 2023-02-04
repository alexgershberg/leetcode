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
        std::map<std::pair<std::string, std::string>, int> memo;
        return solve(word1, word2, memo);
    }
};


int main()
{
    std::string word1 = "plasma";
    std::string word2 = "altruism";

    Solution sol;
    auto res = sol.minDistance(word1, word2);
    std::cout << res << std::endl;
}