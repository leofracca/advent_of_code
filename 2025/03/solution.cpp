#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

void parseInput(std::ifstream& input, std::vector<std::vector<int>>& banks)
{
    std::string line;
    while (std::getline(input, line))
    {
        banks.push_back({});
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            for (char c : word)
            {
                banks.back().push_back(c - '0');
            }
        }
    }
}

unsigned long long solution1(const std::vector<std::vector<int>>& banks)
{
    unsigned long long ans = 0;

    for (const auto& bank : banks)
    {
        int maxBattery = 0;
        int index = -1;
        int joltage = 1;
        bool backward = false;

        for (int i = 0; i < bank.size(); ++i)
        {
            if (bank[i] > maxBattery)
            {
                maxBattery = bank[i];
                index = i;
            }
        }

        // std::cout << "Starting at index " << index << " with battery " << maxBattery << std::endl;
        joltage = maxBattery;
        maxBattery = 0;
        
        if (index == bank.size() - 1)
        {
            backward = true;
            for (int i = index - 1; i >= 0; i--)
            {
                if (bank[i] > maxBattery)
                {
                    maxBattery = bank[i];
                    index = i;
                }
            }
        }
        else
        {
            joltage *= 10;
            for (int i = index + 1; i < bank.size(); i++)
            {
                if (bank[i] > maxBattery)
                {
                    maxBattery = bank[i];
                    index = i;
                }
            }
        }

        // std::cout << "Next index " << index << " with battery " << maxBattery << std::endl;

        joltage = backward ? joltage + maxBattery * 10 : joltage + maxBattery;
        // std::cout << "Joltage for this bank: " << joltage << std::endl;
        ans += joltage;
    }

    return ans;
}

unsigned long long solution2(const std::vector<std::vector<int>>& banks)
{
    unsigned long long ans = 0;
    std::stack<int> current;

    for (const auto& bank : banks)
    {
        for (int i = 0; i < bank.size(); i++)
        {
            while (!current.empty() && bank[i] > current.top() && 12 - current.size() < bank.size() - i)
            {
                current.pop();
            }
            if (current.size() < 12)
            {
                current.push(bank[i]);
            }
        }

        unsigned long long multiplier = 1;
        unsigned long long joltage = 0;
        while (!current.empty())
        {
            // std::cout << current.top() << " ";
            joltage += current.top() * multiplier;
            // std::cout << "Current joltage: " << joltage << std::endl;
            multiplier *= 10;
            current.pop();
        }
        // std::cout << std::endl;
        // std::cout << "Joltage for this bank: " << joltage << std::endl;
        ans += joltage;
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::vector<int>> banks;
    parseInput(input, banks);

    std::cout << solution1(banks) << std::endl;
    std::cout << solution2(banks) << std::endl;
}