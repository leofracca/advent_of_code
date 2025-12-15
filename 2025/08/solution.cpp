#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>

struct Point
{
    int x;
    int y;
    int z;

    // Allow priority_queue to order by distance
    bool operator<(const Point& other) const
    {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }
};

struct PointsAndDistance
{
    unsigned long long distance;
    Point p;
    Point q;

    // Allow priority_queue to order by distance
    bool operator<(const PointsAndDistance& other) const
    {
        return distance < other.distance;
    }
};

void parseInput(std::ifstream& input, std::vector<Point>& junctionBoxes)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<int> tmp(3);
        int i = 0;
        while (std::getline(ss, token, ','))
        {
            tmp[i++] = std::stoi(token);
        }
        junctionBoxes.emplace_back(tmp[0], tmp[1], tmp[2]);
    }
}

unsigned long long calculateDistance(Point p, Point q)
{
    // No need to take the square root for comparison purposes
    return std::pow(p.x - q.x, 2) + std::pow(p.y - q.y, 2) + std::pow(p.z - q.z, 2);
}

unsigned long long solution1(const std::vector<Point>& junctionBoxes)
{
    unsigned long long ans = 1;
    struct Compare {
        bool operator()(const PointsAndDistance& a, const PointsAndDistance& b) const
        {
            // Make a min-heap by returning true when a is "greater" than b
            return a.distance > b.distance;
        }
    };
    std::priority_queue<PointsAndDistance, std::vector<PointsAndDistance>, Compare> distances;
    std::map<Point, std::set<Point>> graph;

    for (int i = 0; i < junctionBoxes.size(); i++)
    {
        for (int j = 0; j < junctionBoxes.size(); j++)
        {
            if (i == j) continue;
            unsigned long long distance = calculateDistance(junctionBoxes[i], junctionBoxes[j]);

            distances.push(PointsAndDistance{distance, junctionBoxes[i], junctionBoxes[j]});
        }
    }

    int i = 0;
    while (!distances.empty() && i++ < 2000)
    {
        const auto d = distances.top();
        // std::cout << "p.x: " << d.p.x << ", p.y: " << d.p.y << ", p.z: " << d.p.z << " | " 
        //           << "q.x: " << d.q.x << ", q.y: " << d.q.y << ", q.z: " << d.q.z << " | "
        //           << "distance: " << d.distance << std::endl;
        distances.pop();

        graph[d.p].insert(d.q);
        graph[d.q].insert(d.p);
    }

    // Get the 3 largest circuits
    std::vector<int> circuitSizes;
    std::set<Point> visited;
    for (const auto& [point, _] : graph)
    {
        if (visited.find(point) != visited.end()) continue;
        std::queue<Point> q;
        q.push(point);
        visited.insert(point);
        int circuitSize = 0;

        while (!q.empty())
        {
            Point current = q.front();
            q.pop();
            circuitSize++;

            for (const auto& neighbor : graph[current])
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        circuitSizes.push_back(circuitSize);
    }

    std::sort(circuitSizes.rbegin(), circuitSizes.rend());
    for (int j = 0; j < std::min(3, (int)circuitSizes.size()); j++)
    {
        ans *= circuitSizes[j];
    }

    return ans;
}

unsigned long long solution2(const std::vector<Point>& junctionBoxes)
{
    unsigned long long ans = 1;
    struct Compare {
        bool operator()(const PointsAndDistance& a, const PointsAndDistance& b) const
        {
            // Make a min-heap by returning true when a is "greater" than b
            return a.distance > b.distance;
        }
    };
    std::priority_queue<PointsAndDistance, std::vector<PointsAndDistance>, Compare> distances;
    std::map<Point, std::set<Point>> graph;
    std::set<Point> allPoints;

    for (int i = 0; i < junctionBoxes.size(); i++)
    {
        for (int j = 0; j < junctionBoxes.size(); j++)
        {
            if (i == j) continue;
            unsigned long long distance = calculateDistance(junctionBoxes[i], junctionBoxes[j]);

            distances.push(PointsAndDistance{distance, junctionBoxes[i], junctionBoxes[j]});
        }
    }

    while (!distances.empty())
    {
        const auto d = distances.top();
        // std::cout << "p.x: " << d.p.x << ", p.y: " << d.p.y << ", p.z: " << d.p.z << " | " 
        //           << "q.x: " << d.q.x << ", q.y: " << d.q.y << ", q.z: " << d.q.z << " | "
        //           << "distance: " << d.distance << std::endl;
        distances.pop();

        graph[d.p].insert(d.q);
        graph[d.q].insert(d.p);
        allPoints.insert(d.p);
        allPoints.insert(d.q);

        // Early exit if we have a large connected component
        if (allPoints.size() == junctionBoxes.size())
        {
            // std::cout << "Point p: " << d.p.x << "," << d.p.y << "," << d.p.z << std::endl;
            // std::cout << "Point q: " << d.q.x << "," << d.q.y << "," << d.q.z << std::endl;
            return static_cast<unsigned long long>(d.p.x) * static_cast<unsigned long long>(d.q.x);
        }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<Point> junctionBoxes;
    parseInput(input, junctionBoxes);

    // for (const auto& p : junctionBoxes)
    // {
    //     std::cout << p.x << ",";
    //     std::cout << p.y << ",";
    //     std::cout << p.z << std::endl;
    // }

    std::cout << solution1(junctionBoxes) << std::endl;
    std::cout << solution2(junctionBoxes) << std::endl;
}