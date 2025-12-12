#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

void parseInput1(std::ifstream& input, std::vector<std::vector<unsigned long long>>& numbers, std::vector<char>& operands)
{
    std::string line;
    while (std::getline(input, line))
    {
        // std::cout << line << std::endl;
        numbers.push_back({});
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            // std::cout << word << std::endl;
            if (word != "+" && word != "*")
            {
                numbers.back().push_back(std::stoull(word));
            }
            else
            {
                operands.push_back(word[0]);
            }
        }
    }

    numbers.pop_back();
}

void parseInput2(std::ifstream& input, std::vector<std::string>& numbers)
{
    std::string line;
    while (std::getline(input, line))
    {
        numbers.push_back(line);
    }

    numbers.pop_back();
}

unsigned long long solution1(const std::vector<std::vector<unsigned long long>>& numbers, const std::vector<char>& operands)
{
    unsigned long long ans = 0;
    // std::cout << numbers.size() << std::endl;
    // std::cout << numbers[0].size() << std::endl;

    for (int i = 0; i < numbers[0].size(); i++)
    {
        unsigned long long current = operands[i] == '+' ? 0 : 1;
        // std::cout << operands[i] << std::endl;
        for (int j = 0; j < numbers.size(); j++)
        {
            // std::cout << numbers[j][i] << std::endl;
            if (operands[i] == '+')
            {
                current += numbers[j][i];
            }
            else
            {
                current *= numbers[j][i];
            }
        }

        ans += current;
    }

    return ans;
}

unsigned long long solution2(std::vector<std::string>& numbers, const std::vector<char>& operands)
{
    unsigned long long ans = 0;

    int opIndex = operands.size() - 1;
    int consecutiveSpaces = 0;
    int currentNumber = 0;
    unsigned long long current = operands[opIndex] == '+' ? 0 : 1;
    std::vector<unsigned long long> currents;

    for (int i = numbers[0].size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < numbers.size(); j++)
        {
            if (numbers[j][i] == ' ')
            {
                numbers[j][i] = '0';
                consecutiveSpaces++;
            }
            else
            {
                // std::cout << currentNumber << " " << numbers[j][i] << std::endl;
                consecutiveSpaces = 0;
                currentNumber = currentNumber * 10 + (numbers[j][i] - '0');
                // std::cout << currentNumber << std::endl;
            }
            // std::cout << numbers[j][i] << " " << operands[opIndex] << " ";
        }
        
        // std::cout << currentNumber << std::endl;
        if (operands[opIndex] == '+')
        {
            current += currentNumber;
        }
        else
        {
            current *= currentNumber;
        }
        if (consecutiveSpaces == numbers.size())
        {
            opIndex--;
            consecutiveSpaces = 0;
        }

        currents.push_back(current);
        
        // std::cout << current << std::endl;
        current = operands[opIndex] == '+' ? 0 : 1;
        currentNumber = 0;
    }

    opIndex = operands.size() - 1;
    unsigned long long res = operands[opIndex] == '+' ? 0 : 1;
    for (int i = 0; i < currents.size(); i++)
    {
        if (currents[i] == 0)
        {
            ans += res;
            // std::cout << "Ans " << ans << std::endl;
            res = operands[--opIndex] == '+' ? 0 : 1;
            continue;
        }

        if (operands[opIndex] == '+')
        {
            res += currents[i];
        }
        else
        {
            res *= currents[i];
        }

        // std::cout << "Res " << res << std::endl;
    }

    ans += res;

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::vector<unsigned long long>> numbers;
    std::vector<char> operands;
    parseInput1(input, numbers, operands);
    // for (auto& row : numbers)
    // {
    //     row.clear();
    // }
    // numbers.clear();
    std::ifstream input2("input.txt");
    std::vector<std::string> numberRows;
    parseInput2(input2, numberRows);

    // for (int i = 0; i < numbers[0].size(); i++)
    // {
    //     // std::cout << operands[i] << std::endl;
    //     for (int j = 0; j < numbers.size(); j++)
    //     {
    //         std::cout << numbers[j][i] << std::endl;
    //     }
    // }

    // for (auto& line : numberRows)
    // {
    //     std::cout << line << std::endl;
    // }

    std::cout << solution1(numbers, operands) << std::endl;
    std::cout << solution2(numberRows, operands) << std::endl;
}