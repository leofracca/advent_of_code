#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <map>

constexpr int N_LETTERS = 58;
int main()
{
    std::ifstream input("input.txt");
    int sumTask1 = 0;
    int sumTask2 = 0;

    std::unordered_map<char, int> priorities;
    for (int i = 0; i < 26; i++) 
    {
        priorities['a' + i] = i + 1;
        priorities['A' + i] = i + 27;
    }

    std::array<int, N_LETTERS> occurencesFirstHalf;
    std::array<int, N_LETTERS> occurencesSecondHalf;

    std::array<int, N_LETTERS> occurencesFirstString;
    std::array<int, N_LETTERS> occurencesSecondString;
    std::array<int, N_LETTERS> occurencesThirdString;

    std::string firstString;
    std::string secondString;
    std::string thirdString;

    std::string line;
    int nLines = 0;
    while (std::getline(input, line))
    {
        // Reset occurences
        for (int i = 0; i < N_LETTERS; i++)
        {
            occurencesFirstHalf[i] = 0;
            occurencesSecondHalf[i] = 0;

            if (nLines == 0)
            {
                occurencesFirstString[i] = 0;
                occurencesSecondString[i] = 0;
                occurencesThirdString[i] = 0;
            }
        }

        // Split the string into two parts
        std::string firstHalf = line.substr(0, line.size() / 2);
        std::string secondHalf = line.substr(line.size() / 2);

        // Count the occurences of each letter in the first half
        for (char c : firstHalf)
            occurencesFirstHalf[c - 'A']++;

        // Count the occurences of each letter in the second half
        for (char c : secondHalf)
            occurencesSecondHalf[c - 'A']++;

        // Find the common character
        for (int i = 0; i < N_LETTERS; i++)
            if (occurencesFirstHalf[i] > 0 && occurencesSecondHalf[i] > 0)
                sumTask1 += priorities['A' + i];

        nLines++;

        if (nLines == 1)
            firstString = line;
        else if (nLines == 2)
            secondString = line;
        else if (nLines == 3)
        {
            thirdString = line;
            nLines = 0;
        }

        if (nLines == 0)
        {
            // Count the occurences of each letter in the first string
            for (char c : firstString)
                occurencesFirstString[c - 'A']++;

            // Count the occurences of each letter in the second string
            for (char c : secondString)
                occurencesSecondString[c - 'A']++;

            // Count the occurences of each letter in the third string
            for (char c : thirdString)
                occurencesThirdString[c - 'A']++;

            // Find the common character
            for (int i = 0; i < N_LETTERS; i++)
                if (occurencesFirstString[i] > 0 && occurencesSecondString[i] > 0 && occurencesThirdString[i] > 0)
                    sumTask2 += priorities['A' + i];
        }
    }

    std::cout << sumTask1 << std::endl;
    std::cout << sumTask2 << std::endl;
}