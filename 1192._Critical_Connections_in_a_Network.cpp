//
// Created by alexgershberg on 04/02/23.
//

//https://leetcode.com/problems/critical-connections-in-a-network/


#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <set>
#include <fstream>

std::map<int, std::vector<int>> makeGraph(const std::vector<std::vector<int>>& edges)
{
    std::map<int, std::vector<int>> graph;

    std::for_each(edges.begin(), edges.end(), [&graph](auto& edge)
    {
      int a = edge.at(0);
      int b = edge.at(1);

      if (graph.find(a) == graph.end())
          graph[a] = {};
      if (graph.find(b) == graph.end())
          graph[b] = {};

      graph[a].push_back(b);
      graph[b].push_back(a);
    });

    return graph;
}

void printGraph(const std::map<int, std::vector<int>>& graph)
{
    std::for_each(graph.begin(), graph.end(), [](const auto& pair)
    {
      auto& key = pair.first;
      auto& values = pair.second;

      std::cout << key << ": ";
      std::for_each(values.begin(), values.end(), [](const int val)
      {
        std::cout << val << " ";
      });

      std::cout << std::endl;
    });
};

void addSingleEdge(const std::map<int, std::vector<int>>& graph, std::vector<std::vector<int>>& output)
{
    std::for_each(graph.begin(), graph.end(), [&](const std::pair<int, std::vector<int>>& key_val)
    {
      const auto& key = key_val.first;
      const auto& val = key_val.second;

      if (val.size() == 1)
      {
          std::vector<int> temp{ key, val.at(0) };
          output.push_back(std::move(temp));
      }
    });
}

bool dfs(int node, const std::map<int, std::vector<int>>& graph, std::set<int>& visited)
{
    if (visited.find(node) != visited.end())
        return false;

    visited.insert(node);

    const std::vector<int>& neighbours = graph.at(node);

    std::for_each(neighbours.begin(), neighbours.end(), [&](int neighbour)
    {
      dfs(neighbour, graph, visited);
    });

    return true;
}

bool ping(int servers, const std::map<int, std::vector<int>>& graph)
{
    //Maybe use unordered_set?
    std::set<int> visited;

    int islands = 0;
    for (const auto& key_val : graph)
    {
        int node = key_val.first;
        if (dfs(node, graph, visited))
            islands++;

        if (islands > 1)
            return false;

    }

    return (islands == 1) && visited.size() == servers;
}

std::vector<std::vector<int>> solve(int servers, std::vector<std::vector<int>>& connections)
{
    std::vector<std::vector<int>> final_result;

    //addSingleEdge(graph, final_result);

    std::vector<std::vector<int>> connections_copy;
    std::copy(connections.begin(), connections.end(), std::back_inserter(connections_copy));

    for (int i = 0; i < connections.size(); i++)
    {
        std::vector<int> temp = connections_copy.at(i);
        connections_copy.erase(connections_copy.begin() + i);
        auto graph = makeGraph(connections_copy);
        if (!ping(servers, graph))
        {
            final_result.push_back(temp);
        }
        connections_copy.insert(connections_copy.begin() + i, temp);
    }

    return final_result;
}

class Solution
{
public:
    std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>>& connections)
    {
        return solve(n, connections);
    };
};

std::fstream file("output.txt");

void generateBigTestCase(int n)
{
    int root = 0;
    file << "[";
    for (int i = 1; i < n; i++)
    {
        file << "[" << root << "," << i << "],";
    }
    file << "]" << std::endl;
}

int main()
{
    generateBigTestCase(100000);


    std::vector<std::vector<int>> connections{
        { 1, 2 }, { 1, 3 }, { 2, 4 }, { 3, 4 },
        { 3, 0 }, { 5, 0 }, { 0, 6 }, { 7, 6 },
        { 7, 8 }, { 9, 8 }, { 11, 9 }, { 9, 10 }};

    auto final_result = solve(12, connections);

    std::cout << "===============" << std::endl;
    std::for_each(final_result.begin(), final_result.end(), [](auto& val)
    {

      std::cout << "[" << val.at(0) << ", " << val.at(1) << "] ";

    });
    std::cout << std::endl;
}



//int main()
//{
//    std::vector<std::vector<int>> connections{
//        { 1, 2 }, { 1, 3 }, { 2, 4 }, { 3, 4 },
//        { 3, 0 }, { 5, 0 }, { 0, 6 },
//        { 7, 8 }, { 9, 8 }, { 11, 9 }, { 9, 10 }};
//
//
//    if (ping(makeGraph(connections)))
//    {
//        std::cout << "Just fine!!!" << std::endl;
//    }
//    else
//    {
//        std::cout << "Oh no" << std::endl;
//    }
//
//}








/*
 Connections = Edges
 Traverse the graph, count how many edges each server has, if a server has only 1 edge, it is critical.

 [[1, 2] [1, 3], [2, 4], [3, 4], [3, 0], [0, 5], [0, 6], [7, 6], [7, 8], [9, 8], [11, 9], [9, 10]]

 Answer: [[3, 0], [0, 5], [0, 6], [6, 7], [7, 8], [8, 9], [9, 10], [9, 11]]


            1--------2
            |        |
            3--------4
            |
            0-----5     11
            |            |
            6            9-----10
            |            |
            7------------8


              1
               \    2---6
                \  /
                 0---3
               /  \
             4     5

 [[0, 1], [0, 2], [0,3], [0, 4], [0, 5], [2,6]]



             1----2----3----4
             |              |
             0----7----6----5

 [[0,1],[1,2],[2,3],[3,4],[4,5],[5,6],[7,6],[7,0]]

 */


