#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>

struct Element
{
    std::string lightDiagram;
    std::vector<std::vector<int>> schematics;
    std::vector<int> joltageRequirements;
};

void parseInput(std::ifstream& input, std::vector<Element>& machines)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream lineStream(line);
        Element element;

        // Read light diagram
        lineStream >> element.lightDiagram;
        // Remove brackets
        element.lightDiagram = element.lightDiagram.substr(1, element.lightDiagram.size() - 2);

        // Read schematics
        std::string schematicStr;
        while (lineStream >> schematicStr && schematicStr.front() == '(')
        {
            schematicStr = schematicStr.substr(1, schematicStr.size() - 2); // Remove parentheses
            std::istringstream schematicStream(schematicStr);
            std::vector<int> schematic;
            std::string indexStr;
            while (std::getline(schematicStream, indexStr, ','))
            {
                schematic.push_back(std::stoi(indexStr));
            }
            element.schematics.push_back(schematic);
        }

        // Read joltage requirements
        if (schematicStr.front() == '{')
        {
            schematicStr = schematicStr.substr(1, schematicStr.size() - 2); // Remove braces
            std::istringstream joltageStream(schematicStr);
            std::string joltageStr;
            while (std::getline(joltageStream, joltageStr, ','))
            {
                element.joltageRequirements.push_back(std::stoi(joltageStr));
            }
        }

        machines.push_back(element);
    }
}

// Get all the combinations of schematics
std::vector<std::vector<std::vector<int>>> allCombinations(const std::vector<std::vector<int>>& v) {
    std::vector<std::vector<std::vector<int>>> result;
    const int n = v.size();

    for (int k = 1; k <= n; ++k) {
        std::vector<bool> mask(n);
        std::fill(mask.begin(), mask.begin() + k, true);

        do {
            auto subset_view =
                std::ranges::views::iota(0, n)
              | std::ranges::views::filter([&](int i) { return mask[i]; })
              | std::ranges::views::transform([&](int i) { return v[i]; });

            result.emplace_back(subset_view.begin(), subset_view.end());
        } while (std::prev_permutation(mask.begin(), mask.end()));
    }

    return result;
}

unsigned long long solution1(const std::vector<Element>& machines)
{
    unsigned long long ans = 0;

    for (int i = 0; i < machines.size(); ++i)
    {
        const Element& machine = machines[i];
        
        // Initialize light diagram representation
        std::string lightDiagram = "";
        for (int j = 0; j < machine.lightDiagram.size(); ++j)
        {
            lightDiagram += '.';
        }
        // std::cout << "Initial Light Diagram: " << lightDiagram << std::endl;

        auto combos = allCombinations(machine.schematics);
        // for (const auto& combo : combos)
        // {
        //     for (const auto& schematic : combo)
        //     {
        //         std::cout << "(";
        //         for (const auto& index : schematic)
        //         {
        //             std::cout << index << " ";
        //         }
        //         std::cout << ") ";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << combos.size() << std::endl;

        bool found = false;
        for (const auto& combo : combos)
        {
            for (const auto& schematic : combo)
            {
                for (const auto& index : schematic)
                {
                    if (lightDiagram[index] == '.')
                    {
                        lightDiagram[index] = '#';
                    }
                    else
                    {
                        lightDiagram[index] = '.';
                    }
                }

                // std::cout << "Current Light Diagram: " << lightDiagram << std::endl;
                if (lightDiagram == machine.lightDiagram)
                {
                    ans += combo.size();
                    found = true;
                    // std::cout << "Found solution for machine " << i << " with " << combo.size() << " button presses." << std::endl;
                    break;
                }
            }

            if (found)
            {
                break;
            }
            
            // Reset light diagram representation
            for (int j = 0; j < machine.lightDiagram.size(); ++j)
            {
                lightDiagram[j] = '.';
            }
        }
        // std::cout << "Reset Light Diagram: " << lightDiagram << std::endl;
    }

    return ans;
}

unsigned long long solution2(const std::vector<Element>& machines)
{
    unsigned long long ans = 0;
    
    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<Element> machines;
    parseInput(input, machines);

    // for (const auto& machine : machines)
    // {
    //     std::cout << "Machine Light Diagram: " << machine.lightDiagram << std::endl;
    //     std::cout << "Schematics:" << std::endl;
    //     for (const auto& schematic : machine.schematics)
    //     {
    //         for (const auto& index : schematic)
    //         {
    //             std::cout << index << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << "Joltage Requirements: ";
    //     for (const auto& joltage : machine.joltageRequirements)
    //     {
    //         std::cout << joltage << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << solution1(machines) << std::endl;
    std::cout << solution2(machines) << std::endl;
}