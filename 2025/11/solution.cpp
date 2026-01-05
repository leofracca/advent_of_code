#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

// dp[passedDac][passedFft][node] -> number of valid paths
std::unordered_map<std::string, unsigned long long> dp[2][2];
// seen[passedDac][passedFft][node] -> has this state been computed?
std::unordered_map<std::string, bool> seen[2][2];

void parseInput(std::ifstream& input, std::unordered_map<std::string, std::vector<std::string>>& devices)
{
    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream lineStream(line);
        std::string device;;
        std::getline(lineStream, device, ':');
        std::string connectionsStr;
        std::getline(lineStream, connectionsStr);
        std::istringstream connectionsStream(connectionsStr);
        std::string connection;
        std::vector<std::string> connections;
        while (connectionsStream >> connection)
        {
            connections.push_back(connection);
        }
        devices[device] = connections;
    }
}

unsigned long long dfs(const std::string& node, bool passedDac, bool passedFft, const std::unordered_map<std::string, std::vector<std::string>>& devices)
{
    if (node == "out") {
        return (passedDac && passedFft) ? 1ULL : 0ULL;
    }

    auto& seen_map = seen[passedDac][passedFft];
    auto& dp_map   = dp[passedDac][passedFft];

    if (seen_map[node]) {
        return dp_map[node];
    }
    seen_map[node] = true;

    unsigned long long total = 0;
    const auto& neighbors = devices.at(node);

    for (const auto& next : neighbors) {
        bool nextPassedDac = passedDac || (next == "dac");
        bool nextPassedFft = passedFft || (next == "fft");
        total += dfs(next, nextPassedDac, nextPassedFft, devices);
    }

    dp_map[node] = total;
    return total;
}

unsigned long long solution1(const std::unordered_map<std::string, std::vector<std::string>>& devices)
{
    unsigned long long ans = 0;
    ans = dfs("you", true, true, devices);
    return ans;
}

unsigned long long solution2(const std::unordered_map<std::string, std::vector<std::string>>& devices)
{
    unsigned long long ans = 0;
    dp[0][0].clear();
    seen[0][0].clear();
    dp[0][1].clear();
    seen[0][1].clear();
    dp[1][0].clear();
    seen[1][0].clear();
    dp[1][1].clear();
    seen[1][1].clear();

    bool passedDac = false;
    bool passedFft = false;
    if ("svr" == "dac")
    {
        passedDac = true;
    }
    if ("svr" == "fft")
    {
        passedFft = true;
    }

    ans = dfs("svr", passedDac, passedFft, devices);
    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::unordered_map<std::string, std::vector<std::string>> devices;
    parseInput(input, devices);

    // for (const auto& [device, connections] : devices)
    // {
    //     std::cout << "Device: " << device << " Connections: ";
    //     for (const auto& conn : connections)
    //     {
    //         std::cout << conn << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << solution1(devices) << std::endl;
    std::cout << solution2(devices) << std::endl;
}