#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

void parseInput(std::ifstream& input, std::vector<std::pair<unsigned long long, unsigned long long>>& ids)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            size_t dashPos = token.find('-');
            if (dashPos != std::string::npos)
            {
                unsigned long long first = std::stoull(token.substr(0, dashPos));
                unsigned long long second = std::stoull(token.substr(dashPos + 1));
                ids.emplace_back(first, second);
            }
        }
    }
}

unsigned long long solution1(const std::vector<std::pair<unsigned long long, unsigned long long>>& ids)
{
    unsigned long long ans = 0;

    for (const auto& id : ids)
    {
        unsigned long long first = id.first;
        unsigned long long second = id.second;

        for (unsigned long long i = first; i <= second; i++)
        {
            std::string str = std::to_string(i);
            // std::cout << "Checking " << str << std::endl;
            bool invalid = true;
            if (str.size() % 2 == 0)
            {
                for (int pos = 0; pos < str.size() / 2; pos++)
                {
                    if (str[pos] != str[pos + str.size() / 2])
                    {
                        // std::cout << "Failed at pos " << pos << std::endl;
                        // std::cout << "Chars: " << str[pos] << " " << str[pos + str.size() / 2] << std::endl;
                        invalid = false;
                        break;
                    }
                }
                if (invalid)
                {
                    // std::cout << "Valid: " << str << std::endl;
                    ans += i;
                    // std::cout << "Adding " << i << ", total now " << ans << std::endl;
                }
            }
        }
    }

    return ans;
}

unsigned long long solution2(const std::vector<std::pair<unsigned long long, unsigned long long>>& ids)
{
    unsigned long long ans = 0;

    for (const auto& id : ids)
    {
        unsigned long long first = id.first;
        unsigned long long second = id.second;

        for (unsigned long long i = first; i <= second; i++)
        {
            std::string str = std::to_string(i);
            // std::cout << "Checking " << str << std::endl;
            bool invalid = false;
            
            for (int pos = 0; pos <= str.size() / 2; pos++)
            {
                std::string firstPart = str.substr(0, pos + 1);
                // std::cout << "First part: " << firstPart << std::endl;

                if (firstPart.size() == str.size())
                    break;

                std::string toCheck;
                while (toCheck.size() < str.size())
                {
                    toCheck += firstPart;

                    if (toCheck == str)
                    {
                        ans += i;
                        // std::cout << "Adding " << i << ", total now " << ans << std::endl;
                        invalid = true;
                        break;
                    }
                }

                if (invalid)
                    break;
            }
        }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::pair<unsigned long long, unsigned long long>> ids;
    parseInput(input, ids);

    std::cout << solution1(ids) << std::endl;
    std::cout << solution2(ids) << std::endl;
}