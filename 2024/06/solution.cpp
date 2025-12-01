#include <vector>
#include <fstream>
#include <iostream>
#include <set>

constexpr int SIZE = 10 + 2; // Actual size + borders

std::pair<int, int> parseInput(std::ifstream& input, char map[SIZE][SIZE])
{
    std::pair<int, int> guardPosition;
    std::string line;
    int i = 1;
    while (std::getline(input, line))
    {
        int j = 1;
        for (char c : line)
        {
            map[i][j] = c;

            if (c == '^')
                guardPosition = {i, j};
            j++;
        }
        i++;
    }

    // Padding
    for (int i = 0; i < SIZE; i++)
    {
        map[i][0] = '0';
        map[i][SIZE - 1] = '0';
    }
    for (int i = 0; i < SIZE; i++)
    {
        map[0][i] = '0';
        map[SIZE - 1][i] = '0';
    }

    return guardPosition;
}

void resetMap(char map[SIZE][SIZE], const std::pair<int, int>& guardPosition)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            if (map[i][j] == 'X')
                map[i][j] = '.';
    }

    map[guardPosition.first][guardPosition.second] = '^';
}

int solution1(char map[SIZE][SIZE], const std::pair<int, int>& guardPosition)
{
    int ans = 0;

    int y = guardPosition.first, x = guardPosition.second;
    char guardDirection = map[y][x];
    char cell = map[y][x];

    while (cell != '0')
    {
        switch (guardDirection)
        {
        case '^':
            if (map[y - 1][x] != '#')
            {
                map[y][x] = 'X';
                y--;
            }
            else
                guardDirection = '>';
            break;
        case '>':
            if (map[y][x + 1] != '#')
            {
                map[y][x] = 'X';
                x++;
            }
            else
                guardDirection = 'v';
            break;
        case 'v':
            if (map[y + 1][x] != '#')
            {
                map[y][x] = 'X';
                y++;
            }
            else
                guardDirection = '<';
            break;
        case '<':
            if (map[y][x - 1] != '#')
            {
                map[y][x] = 'X';
                x--;
            }
            else
                guardDirection = '^';
            break;
        default:
            break;
        }

        cell = map[y][x];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            if (map[i][j] == 'X')
                ans++;
    }

    return ans;
}

int solution2(char map[SIZE][SIZE], const std::pair<int, int>& guardPosition)
{
    int ans = 0;

    int y = guardPosition.first, x = guardPosition.second;
    char guardDirection = map[y][x];
    char cell = map[y][x];
    std::pair<int, int> cellLoopStart;
    std::set<std::pair<std::pair<int, int>, char>> alreadyVisitedWithSameDirectionFromStart, alreadyVisitedWithSameDirectionCurrentLoop;
    bool placedObstacle = false;

    while (cell != '0' && !placedObstacle)
    {
        std::cout << "Obstacle " << placedObstacle << std::endl;
        if (alreadyVisitedWithSameDirectionCurrentLoop.count(std::make_pair(std::make_pair(y, x), guardDirection)))
        {
            alreadyVisitedWithSameDirectionCurrentLoop = alreadyVisitedWithSameDirectionFromStart;
            y = cellLoopStart.first;
            x = cellLoopStart.second;
            placedObstacle = false;
            ans++;
        }

        if (placedObstacle)
            alreadyVisitedWithSameDirectionCurrentLoop.insert(std::make_pair(std::make_pair(y, x), guardDirection));
        else
            alreadyVisitedWithSameDirectionFromStart.insert(std::make_pair(std::make_pair(y, x), guardDirection));

        while (!placedObstacle)
        {
            std::cout << placedObstacle << std::endl;
            switch (guardDirection)
            {
            case '^':
                if (map[y - 1][x] != '#' && map[y - 1][x] != '0')
                {
                    placedObstacle = true;
                    guardDirection = '>';
                }
                else
                    guardDirection = '>';
                break;
            case '>':
                if (map[y][x + 1] != '#' && map[y][x + 1] != '0')
                {
                    placedObstacle = true;
                    guardDirection = 'v';
                }
                else
                    guardDirection = 'v';
                break;
            case 'v':
                if (map[y + 1][x] != '#' && map[y + 1][x] != '0')
                {
                    placedObstacle = true;
                    guardDirection = '<';
                }
                else
                    guardDirection = '<';
                break;
            case '<':
                if (map[y][x - 1] != '#' && map[y][x - 1] != '0')
                {
                    placedObstacle = true;
                    guardDirection = '^';
                }
                else
                    guardDirection = '^';
                break;
            default:
                break;
            }

            cellLoopStart = std::make_pair(y, x);
        }

        while (cell != '0')
        {
            std::cout << cell << std::endl;
            if (alreadyVisitedWithSameDirectionCurrentLoop.count(std::make_pair(std::make_pair(y, x), guardDirection)))
            {
                alreadyVisitedWithSameDirectionCurrentLoop = alreadyVisitedWithSameDirectionFromStart;
                y = cellLoopStart.first;
                x = cellLoopStart.second;
                placedObstacle = false;
                ans++;
            }
            switch (guardDirection)
            {
            case '^':
                if (map[y - 1][x] != '#')
                {
                    y--;
                }
                else
                    guardDirection = '>';
                break;
            case '>':
                if (map[y][x + 1] != '#')
                {
                    x++;
                }
                else
                    guardDirection = 'v';
                break;
            case 'v':
                if (map[y + 1][x] != '#')
                {
                    y++;
                }
                else
                    guardDirection = '<';
                break;
            case '<':
                if (map[y][x - 1] != '#')
                {
                    x--;
                }
                else
                    guardDirection = '^';
                break;
            default:
                break;
            }

            cell = map[y][x];
        }

        cell = map[y][x];
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    char map[SIZE][SIZE];
    std::pair<int, int> guardPosition = parseInput(input, map);

    // std::cout << solution1(map, guardPosition) << std::endl;
    // resetMap(map, guardPosition);
    std::cout << solution2(map, guardPosition) << std::endl;
}