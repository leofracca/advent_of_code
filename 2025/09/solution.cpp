#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>

void parseInput(std::ifstream& input, std::vector<std::pair<int, int>>& floorTiles)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<int> tmp(2);
        int i = 0;
        while (std::getline(ss, token, ','))
        {
            tmp[i++] = std::stoi(token);
        }
        floorTiles.push_back({tmp[0], tmp[1]});
    }
}

unsigned long long solution1(const std::vector<std::pair<int, int>>& floorTiles)
{
    unsigned long long ans = 0;

    // Find largest area rectangle that can fit in the floor tiles
    unsigned long long maxArea = 0;
    for (const auto& tile1 : floorTiles)
    {
        for (const auto& tile2 : floorTiles)
        {
            if (tile1 == tile2) continue;
            unsigned long long length = std::abs(tile1.first - tile2.first) + 1;
            unsigned long long width = std::abs(tile1.second - tile2.second) + 1;
            unsigned long long area = length * width;
            maxArea = std::max(maxArea, area);
            // std::cout << "Tile1: (" << tile1.first << "," << tile1.second << ") "
            //           << "Tile2: (" << tile2.first << "," << tile2.second << ") "
            //           << "Area: " << area << std::endl;
        }
    }

    ans = maxArea;
    return ans;
}

unsigned long long solution2(const std::vector<std::pair<int, int>>& floorTiles)
{
    unsigned long long ans = 0;
    
    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::pair<int, int>> floorTiles;
    parseInput(input, floorTiles);

    for (const auto& row : floorTiles)
    {
        std::cout << row.first << " " << row.second << std::endl;
    }

    std::cout << solution1(floorTiles) << std::endl;
    std::cout << solution2(floorTiles) << std::endl;
}