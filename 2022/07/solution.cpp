#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

void up(std::unordered_map<std::string, unsigned int> &sizePerDirectory, std::vector<std::string> &currentPath)
{
    // Save the size of the directory
    sizePerDirectory[currentPath[currentPath.size() - 2]] += sizePerDirectory[currentPath[currentPath.size() - 1]];
    // Go up a level
    currentPath.pop_back();
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> currentPath; // Contains the path of the current directory; the last one is the current (the first is "/")
    std::unordered_map<std::string, unsigned int> sizePerDirectory; // Key: directory, value: size
    
    constexpr int LIMIT = 100000, TOTAL = 70000000, MIN_REQUIRED = 30000000;

    std::string line;
    while (std::getline(input, line))
    {
        std::vector<std::string> command;
        std::stringstream stream(line);
        std::string tmp;
        while (stream >> tmp)
            command.push_back(tmp);

        if (command[0] == "$")
        {
            if (command[1] == "cd")
            {
                if (command[2] == "..")
                {
                    up(sizePerDirectory, currentPath);
                }
                else
                {
                    std::string path = currentPath.size() == 0 ? "/" : (currentPath[currentPath.size() - 1] + command[2]);
                    // Go down a level
                    currentPath.push_back(path);
                    sizePerDirectory.emplace(path, 0);
                }
            }
        }
        else
        {
            if (command[0] != "dir")
            {
                // Sum the size
                int size = std::stoi(command[0]);
                sizePerDirectory[currentPath[currentPath.size() - 1]] += size;
            }
        }
    }

    while (currentPath.size() > 1)
    {
        // Save the size of the last visited directories
        up(sizePerDirectory, currentPath);
    }

    unsigned int task1 = 0, task2 = TOTAL;

    // Find the minimun space to free
    int currentAvailable = TOTAL - sizePerDirectory["/"];
    int spaceToFree = MIN_REQUIRED - currentAvailable;

    for (auto const &[key, val] : sizePerDirectory)
    {
        if (val <= LIMIT)
            task1 += val;

        if (val >= spaceToFree && val < task2)
            task2 = val;
    }

    std::cout << task1 << std::endl;
    std::cout << task2 << std::endl;

    return 0;
}