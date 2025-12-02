#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

void parseInput(std::ifstream& input, std::vector<int>& codes)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            if (word[0] == 'L')
                codes.push_back(-std::stoi(word.substr(1)));
            else if (word[0] == 'R')
                codes.push_back(std::stoi(word.substr(1)));
        }
    }
}

int solution1(const std::vector<int>& codes)
{
    int ans = 0;
    int currentValue = 50;
    
    for (const auto& code: codes)
    {
        currentValue += code;
        currentValue = ((currentValue % 100) + 100) % 100;;

        if (currentValue == 0)
            ans++;
    }

    return ans;
}

int solution2(const std::vector<int>& codes)
{
    int ans = 0;
    int currentValue = 50;

    for (const auto& code: codes)
    {
        // Right
        if (code > 0)
        {
            if (currentValue + code >= 100)
            {
                ans += (currentValue + code) / 100;
                // std::cout << "Overflowing right: " << currentValue << " + " << code << " -> " << (currentValue + code) / 100 << std::endl;
            }
        }
        // Left starting from non-zero
        else if (currentValue != 0)
        {
            if (currentValue + code <= 0)
            {
                ans += 1 + (std::abs(currentValue + code) / 100);
                // std::cout << "Overflowing left: " << currentValue << " + " << code << " -> " << (std::abs(currentValue + code) / 100) + 1 << std::endl;
            }
        }
        // Left starting from zero
        else if (code <= -100)
        {
            ans += std::abs(code) / 100;
            // std::cout << "Starting at zero, left rotation: " << currentValue << " + " << code << " -> " << std::abs(code) / 100 << std::endl;
        }

        currentValue += code;
        currentValue = ((currentValue % 100) + 100) % 100;
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<int> codes;
    parseInput(input, codes);

    std::cout << solution1(codes) << std::endl;
    std::cout << solution2(codes) << std::endl;
}