#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

// https://www.reddit.com/r/adventofcode/comments/1pgnmou/2025_day_7_lets_visualize/

void parseInput(std::ifstream& input, std::vector<std::string>& diagram)
{
    std::string line;
    while (std::getline(input, line))
    {
        diagram.push_back(line);
    }
}

unsigned long long solution1(const std::vector<std::string>& diagram)
{
    unsigned long long ans = 0;
    std::vector<int> beams(diagram[0].size());

    for (const auto& row : diagram)
    {
        for (int i = 0; i < row.size(); i++)
        {
            if (row[i] == 'S')
            {
                if (beams[i] == 0)
                {
                    beams[i] = 1;
                    ans++;
                }
            }
            else if (row[i] == '^')
            {
                if (beams[i] == 1)
                {
                    beams[i - 1] = 1;
                    beams[i + 1] = 1;
                    beams[i] = 0;

                    ans++;
                }
            }
        }

        // for (int i : beams)
        // {
        //     std::cout << i;
        // }
        // std::cout << std::endl;
    }

    // for (int i : beams)
    // {
    //     std::cout << i;
    // }
    
    return ans - 1;
}

unsigned long long solution2(const std::vector<std::string>& diagram)
{
    unsigned long long ans = 0;
    std::vector<unsigned long long> beams(diagram[0].size());

    for (const auto& row : diagram)
    {
        for (int i = 0; i < row.size(); i++)
        {
            if (row[i] == 'S')
            {
                if (beams[i] == 0)
                {
                    beams[i] = 1;
                }
            }
            else if (row[i] == '^')
            {
                if (beams[i] != 0)
                {
                    beams[i - 1] += beams[i];
                    beams[i + 1] += beams[i];
                    beams[i] = 0;
                }
            }
        }

        // for (unsigned long long i : beams)
        // {
        //     std::cout << i << " ";
        // }
        // std::cout << std::endl;
    }

    for (unsigned long long i : beams)
    {
        // std::cout << i << " ";
        ans += i;
    }
    
    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> diagram;
    parseInput(input, diagram);

    // for (const auto& s : diagram)
    // {
    //     std::cout << s << std::endl;
    // }

    std::cout << solution1(diagram) << std::endl;
    std::cout << solution2(diagram) << std::endl;
}