#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <fstream>

void parseInput(std::ifstream& input, std::vector<std::string>& grid)
{
    std::string line;
    while(std::getline(input, line))
    {
        grid.push_back(line);
    }
}

// Direction data
const char DIRECTIONS[4] = {'E', 'S', 'W', 'N'};
const std::pair<int, int> DELTAS[4] = {
    {0, 1},  // East
    {1, 0},  // South
    {0, -1}, // West
    {-1, 0}  // North
};

struct Node
{
    int score;
    int x;
    int y;
    int direction;

    bool operator<(const Node& other) const
    {
        return score < other.score;
    }
};

int dijkstra(const std::vector<std::string>& grid, std::pair<int, int>& start, std::pair<int, int>& end, std::set<Node>& scores)
{
    auto compare = [&](Node a, Node b) { return a.score > b.score; };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> pq(compare);
    pq.push({0, start.first, start.second, 0});

    std::set<std::tuple<int, int, int>> visited;

    while (!pq.empty())
    {
        auto [score, x, y, direction] = pq.top();
        pq.pop();

        // If we reach the end tile, return the score
        if (x == end.first && y == end.second)
        {
            return score;
        }

        // Avoid revisiting the same state
        if (visited.count({x, y, direction}))
        {
            continue;
        }
        visited.insert({x, y, direction});

        // Move forward in the current direction
        int dx = DELTAS[direction].first;
        int dy = DELTAS[direction].second;
        int nx = x + dx, ny = y + dy;
        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] != '#')
        {
            pq.push({score + 1, nx, ny, direction});
            scores.insert({score + 1, nx, ny, direction});
        }

        // Turn clockwise and counterclockwise
        for (int turn : {-1, 1})
        {
            int newDirection = (direction + turn + 4) % 4; // Wrap around 0-3
            pq.push({score + 1000, x, y, newDirection});
            scores.insert({score + 1000, x, y, newDirection});
        }
    }

    return -1;
}

void findStartAndEnd(const std::vector<std::string>& grid, std::pair<int, int>& start, std::pair<int, int>& end)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 'S')
                start = {i, j};
            if (grid[i][j] == 'E')
                end = {i, j};
        }
    }
}

int solution1(const std::vector<std::string>& grid, std::pair<int, int>& start, std::pair<int, int>& end)
{
    int ans = 0;
    std::set<Node> fromStoE;
    ans = dijkstra(grid, start, end, fromStoE);
    return ans;
}

int solution2(const std::vector<std::string>& grid, std::pair<int, int>& start, std::pair<int, int>& end)
{
    int ans = 0;
    std::set<Node> fromStoE;
    std::set<Node> fromEtoS;

    for (int i = 0; i < 4; i++)
    {
        fromStoE.insert({0, start.first, start.second, i});
        fromEtoS.insert({0, end.first, end.second, i});
    }

    int scoreFromStartToEnd = dijkstra(grid, start, end, fromStoE);
    int scoreFromEndToStart = dijkstra(grid, end, start, fromEtoS);

    std::cout << "Score from start to end: " << scoreFromStartToEnd << std::endl;
    std::cout << "Score from end to start: " << scoreFromEndToStart << std::endl;

    // Print scores
    for (auto node : fromStoE)
    {
        std::cout << "Score: " << node.score << " X: " << node.x << " Y: " << node.y << " Direction: " << DIRECTIONS[node.direction] << std::endl;
    }

    for (auto node : fromEtoS)
    {
        std::cout << "Score: " << node.score << " X: " << node.x << " Y: " << node.y << " Direction: " << DIRECTIONS[node.direction] << std::endl;
    }

    for (auto node : fromStoE)
    {
        Node reverseNode = {node.score - 1000, node.x, node.y, (node.direction + 2) % 4};
        if (fromEtoS.count(reverseNode) && node.score + reverseNode.score == scoreFromStartToEnd)
        {
            ans++;
        }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> grid;
    parseInput(input, grid);

    std::pair<int, int> start, end;
    findStartAndEnd(grid, start, end);

    std::cout << solution1(grid, start, end) << std::endl;
    std::cout << solution2(grid, start, end) << std::endl;
}
