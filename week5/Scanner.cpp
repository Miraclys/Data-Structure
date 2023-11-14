#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nodes;
    for (int i = 0; i < 27; ++i) {
        nodes.push_back(i);
    }

    int maxPathLength = 0;
    std::vector<int> maxPath;

    do {
        bool isValidPath = true;
        for (int i = 0; i < nodes.size() - 1; ++i) {
            int from = nodes[i];
            int to = nodes[i + 1];
            bool isConnected = false;
            for (const ScannerNode& neighbor : nodes[from].to) {
                if (neighbor.number == to) {
                    isConnected = true;
                    break;
                }
            }
            if (!isConnected) {
                isValidPath = false;
                break;
            }
        }

        if (isValidPath) {
            int pathLength = nodes.size();
            if (pathLength > maxPathLength) {
                maxPathLength = pathLength;
                maxPath = nodes;
            }
        }
    } while (std::next_permutation(nodes.begin(), nodes.end()));

    std::cout << maxPathLength << std::endl;
    for (int i = 0; i < maxPath.size(); ++i) {
        std::cout << nodes[maxPath[i]].light << " ";
    }
    std::cout << std::endl;

    return 0;
}
