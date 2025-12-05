#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

void parseInput(std::ifstream& input, std::vector<std::pair<unsigned long long, unsigned long long>>& ranges, std::vector<unsigned long long>& ingredients)
{
    std::string line;
    while (std::getline(input, line))
    {
        size_t dashPos = line.find('-');
        if (dashPos != std::string::npos)
        {
            unsigned long long first = std::stoull(line.substr(0, dashPos));
            unsigned long long second = std::stoull(line.substr(dashPos + 1));
            ranges.emplace_back(first, second);
            // std::cout << "Parsed range: " << first << " - " << second << std::endl;
        }
        else
        {
            if (line.empty()) continue;
            ingredients.push_back(std::stoull(line));
            // std::cout << "Parsed ingredient: " << ingredients.back() << std::endl;
        }

    }
}

unsigned long long solution1(const std::vector<std::pair<unsigned long long, unsigned long long>>& ranges, const std::vector<unsigned long long>& ingredients)
{
    unsigned long long ans = 0;

    for (const auto &ingredient : ingredients)
    {
        for (const auto& range : ranges)
        {
            if (ingredient >= range.first && ingredient <= range.second)
            {
                ans++;
                break;
            }
        }
    }

    return ans;
}

unsigned long long solution2(std::vector<std::pair<unsigned long long, unsigned long long>>& ranges)
{
    unsigned long long ans = 0;
    std::vector<std::pair<unsigned long long, unsigned long long>> merged;

    // Merge overlapping ranges
    std::sort(ranges.begin(), ranges.end());
    for (const auto& range : ranges)
    {
        if (merged.empty() || merged.back().second < range.first - 1)
        {
            merged.push_back(range);
            // std::cout << "Adding new merged range: " << range.first << " - " << range.second << std::endl;
        }
        else
        {
            merged.back().second = std::max(merged.back().second, range.second);
            // std::cout << "Merging range: " << range.first << " - " << range.second << " into " << merged.back().first << " - " << merged.back().second << std::endl;
        }
    }

    // std::cout << "Merged ranges:" << std::endl;
    // for (const auto& mrange : merged)
    // {
    //     std::cout << mrange.first << " - " << mrange.second << std::endl;
    // }

    for (const auto& mrange : merged)
    {
        ans += (mrange.second - mrange.first + 1);
    }
    
    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
    std::vector<unsigned long long> ingredients;
    parseInput(input, ranges, ingredients);

    std::cout << solution1(ranges, ingredients) << std::endl;
    std::cout << solution2(ranges) << std::endl;
}