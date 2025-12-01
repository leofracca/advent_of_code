#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdint>

void parseInput(std::ifstream& input, std::vector<uint64_t>& stones)
{
    std::string line;
    while(std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
            stones.push_back(std::stoull(word));
    }
}

uint64_t blink(std::unordered_map<uint64_t, uint64_t>& memo, uint64_t nBlinks, uint64_t stone)
{
    if (nBlinks == 0)
    {
        return 1;
    }

    if (memo.count(stone) != 0)
    {
        // memo[stone] += 1;
        return memo[stone];
    }

    if (stone == 0)
        memo[stone] = blink(memo, nBlinks - 1, 1);
    else if (std::to_string(stone).size() % 2 == 0)
    {
        std::string curr = std::to_string(stone);

        uint64_t firstHalf = std::stoull(curr.substr(0, curr.size() / 2));
        uint64_t secondHalf = std::stoull(curr.substr(curr.size() / 2));

        memo[stone] = blink(memo, nBlinks - 1, firstHalf) + blink(memo, nBlinks - 1, secondHalf);
    }
    else
        memo[stone] = blink(memo, nBlinks - 1, stone * 2024);

    return memo[stone];
}

uint64_t solution1(std::vector<uint64_t>& stones, std::unordered_map<uint64_t, uint64_t>& memo, int nBlinks)
{
    uint64_t ans = 0;

    for (const uint64_t stone : stones)
        ans += blink(memo, nBlinks, stone);

    return ans;
}

uint64_t solution2(std::vector<uint64_t>& stones, std::unordered_map<uint64_t, uint64_t>& memo, int nBlinks)
{
    uint64_t ans = 0;

    for (const uint64_t stone : stones)
        ans += blink(memo, nBlinks, stone);

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<uint64_t> stones;
    std::unordered_map<uint64_t, uint64_t> memo; // Stone number, number of splits
    parseInput(input, stones);

    // for (const int stone : stones)
    //     memo[stone] = 1;

    std::cout << solution1(stones, memo, 25) << std::endl;

    // int ans = 0;
    // for (const auto& [k, v] : memo)
    // {
    //     std::cout << k << " - " << v << std::endl;
    //     ans += v;
    // }
    // std::cout << ans << std::endl;
    memo.clear();
    std::cout << solution2(stones, memo, 75) << std::endl;
}
