//
// Created by alexgershberg on 11/02/23.
//

#include <string>
#include <vector>
#include <iostream>
#include <set>

class Solution {
public:
    bool buddyStrings(std::string s, std::string goal) {
        if (s.length() != goal.length())
            return false;

        if (s == goal && std::set<char>(s.begin(), s.end()).size() < s.size())
            return true;

        std::vector<int> diffs;
        for(int i = 0; i < s.length(); ++i)
        {
            if (s[i] != goal[i])
                diffs.push_back(i);
        }

        if (diffs.size() != 2)
            return false;

        return s[diffs[0]] == goal[diffs[1]] && s[diffs[1]] == goal[diffs[0]];
    }
};

int main()
{
    Solution sol;
    std::string s = "eeeeab";
    std::string goal = "eeeeca";
    auto res = sol.buddyStrings(s, goal);
    std::cout << "res: " << res << std::endl;
}