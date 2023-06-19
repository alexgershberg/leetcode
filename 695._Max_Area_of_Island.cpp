
//
// Created by alexgershberg on 19/06/23.
//

//https://leetcode.com/problems/max-area-of-island/

#include <vector>
#include <unordered_set>
#include <utility>


class Solution2 {
private:
    int rows, cols;
    int trav (std::vector<std::vector<int>>& grid, int row, int col)
    {
        if (row < 0 || col < 0 || row >= rows || col >= cols || !grid[row][col]) return 0;

        grid[row][col] = 0;
        return 1 + trav(grid, row - 1, col) + trav(grid, row, col - 1) + trav(grid, row + 1, col) + trav(grid, row, col + 1);
    }

public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid)
    {
        rows = grid.size(), cols = grid[0].size();

        int ans = 0;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (grid[i][j]) ans = std::max(ans, trav(grid, i, j));
        return ans;
    }
};

class Solution {
private:
    struct pair_hash {
        inline size_t operator()(const std::pair<int,int> & v) const {
            return v.first * 31 + v.second;
        }
    };

    int islandSize(std::vector<std::vector<int>>& grid, int row, int col, std::unordered_set<std::pair<int, int>, pair_hash>& visited)
    {
        bool rowInBounds = (0 <= row) && (row < grid.size());
        bool colInBounds = (0 <= col) && (col < grid[0].size());

        if (!colInBounds || !rowInBounds)
        {
            return 0;
        }

        auto key = std::make_pair(row, col);

        if (visited.count(key) != 0)
        {
            return 0;
        }

        visited.insert(key);

        int current = grid[row][col];
        if (current == 0)
        {
            return 0;
        }

        int size = 0;

        size += islandSize(grid, row, col + 1, visited);
        size += islandSize(grid, row + 1, col, visited);
        size += islandSize(grid, row, col - 1, visited);
        size += islandSize(grid, row - 1, col, visited);

        return size + 1;
    }

public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        int max_size = 0;
        auto hash = [](std::pair<int, int> pair)
        { return pair.first * 31 + pair.second; };

        std::unordered_set<std::pair<int, int>, pair_hash> visited;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                int size = islandSize(grid, i, j, visited);
                max_size = std::max(max_size, size);
            }
        }
        return max_size;
    }
};