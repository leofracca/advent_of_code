#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

void parseInput(std::ifstream& input, std::vector<std::string>& grid)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        grid.push_back("." + line + ".");
    }

    grid.push_back(std::string(grid[0].size(), '.'));
    grid.insert(grid.begin(), std::string(grid[0].size(), '.'));
}

unsigned long long solution1(const std::vector<std::string>& grid)
{
    unsigned long long ans = 0;

    for (size_t i = 1; i < grid.size() - 1; i++)
    {
        for (size_t j = 1; j < grid[i].size() - 1; j++)
        {
            if (grid[i][j] == '@')
            {
                int adjacentCount = 0;
                for (int di = -1; di <= 1; di++)
                {
                    for (int dj = -1; dj <= 1; dj++)
                    {
                        if (di == 0 && dj == 0) continue;
                        if (grid[i + di][j + dj] == '@')
                        {
                            adjacentCount++;
                        }
                    }
                }

                if (adjacentCount < 4)
                {
                    ans++;
                }
            }
        }
    }

    return ans;
}

unsigned long long solution2(std::vector<std::string>& grid)
{
    unsigned long long ans = 0;
    bool removed = true;
    
    while (removed)
    {
        removed = false;
        for (size_t i = 1; i < grid.size() - 1; i++)
        {
            for (size_t j = 1; j < grid[i].size() - 1; j++)
            {
                if (grid[i][j] == '@')
                {
                    int adjacentCount = 0;
                    for (int di = -1; di <= 1; di++)
                    {
                        for (int dj = -1; dj <= 1; dj++)
                        {
                            if (di == 0 && dj == 0) continue;
                            if (grid[i + di][j + dj] == '@')
                            {
                                adjacentCount++;
                            }
                        }
                    }

                    if (adjacentCount < 4)
                    {
                        ans++;
                        grid[i][j] = '.';
                        removed = true;
                    }
                }
            }
        }

        // for (auto & row : grid)
        // {
        //     std::cout << row << std::endl;
        // }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> grid;
    parseInput(input, grid);

    // for (const auto& row : grid)
    // {
    //     std::cout << row << std::endl;
    // }

    std::cout << solution1(grid) << std::endl;
    std::cout << solution2(grid) << std::endl;
}