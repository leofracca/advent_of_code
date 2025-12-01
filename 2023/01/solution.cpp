#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
#include <map>

int solution1(std::ifstream &input)
{
    std::string line;
    int result = 0;
    while (std::getline(input, line))
    {
        int first = -1, last = -1;
        for (int l = 0, r = line.size() - 1; l < line.size(), r >= 0; l++, r--)
        {
            if (std::isdigit(line[l]) && first == -1)
                first = line[l] - '0';
            if (std::isdigit(line[r]) && last == -1)
                last = line[r] - '0';

            if (first != -1 && last != -1)
                break;
        }

        first = first == -1 ? last : first;
        last = last == -1 ? first : last;

        result += first * 10 + last;
    }

    return result;
}

int solution2(std::ifstream &input)
{
    std::unordered_map<std::string, int> digits = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9}
    };
    std::string line;
    int result = 0;
    while (std::getline(input, line))
    {
        // std::cout << line << std::endl;
        auto firstStringPos = std::string::npos;
        int lastStringPos = -1;
        std::string f = "none", l = "none";
        for (auto const& [k, v] : digits)
        {
            int pos = line.find(k);
            if (pos != std::string::npos && pos < firstStringPos)
            {
                firstStringPos = pos;
                f = k;
            }

            pos = line.rfind(k);
            if (pos != std::string::npos && pos > lastStringPos)
            {
                lastStringPos = pos;
                l = k;
            }
            // std::cout << f << " " << l << std::endl;
        }
        
        if (f == "none")
            f = l;
        if (l == "none")
            l = f;
        // std::cout << f << " " << l << std::endl;
        // std::cout << digits[f] << " " << digits[l] << std::endl;

        result += digits[f] * 10 + digits[l];
    }

    return result;
}

int main()
{
    std::ifstream input("input.txt");

    std::cout << solution1(input) << std::endl;
    // Restore ifstream
    input.clear();
    input.seekg(0, std::ios::beg);
    std::cout << solution2(input) << std::endl;

    return 0;
}