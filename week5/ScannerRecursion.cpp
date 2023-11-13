#include <iostream>
#include <vector>

int maxPathLength = 0;
std::vector<int> maxPath;

class ScannerNode {
public:
    std::string light;
    std::vector<ScannerNode> to;
    int vis;
    int number;

    ScannerNode() : light(""), vis(0) {}
    ScannerNode(std::string val) : light(val), vis(0) {}
} node[30];

void dfs(int cur, int step, std::vector<int>& path) {
    if (step > maxPathLength) {
        maxPathLength = step;
        maxPath = path;
    }

    for (int i = 0; i < node[cur].to.size(); ++i) {
        int next = node[cur].to[i].number;
        if (node[next].vis == 0) {
            node[next].vis = 1;
            path.push_back(next);
            dfs(next, step + 1, path);
            path.pop_back();
            node[next].vis = 0;
        }
    }
}

int main() {
    node[0].light = "RRR";
    node[1].light = "RRG";
    node[2].light = "RRB";
    node[3].light = "RGR";
    node[4].light = "RGG";
    node[5].light = "RGB";
    node[6].light = "RBR";
    node[7].light = "RBG";
    node[8].light = "RBB";
    node[9].light = "GRR";
    node[10].light = "GRG";
    node[11].light = "GRB";
    node[12].light = "GGR";
    node[13].light = "GGG";
    node[14].light = "GGB";
    node[15].light = "GBR";
    node[16].light = "GBG";
    node[17].light = "GBB";
    node[18].light = "BRR";
    node[19].light = "BRG";
    node[20].light = "BRB";
    node[21].light = "BGR";
    node[22].light = "BGG";
    node[23].light = "BGB";
    node[24].light = "BBR";
    node[25].light = "BBG";
    node[26].light = "BBB";
    // ... 光序列初始化和连接建立代码 ...
    for (int i = 0; i < 27; ++i)
        node[i].number = i;
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < 27; ++j) {
            if (i == j) continue;
            if (node[i].light[1] == node[j].light[0] && node[i].light[2] == node[j].light[1]) {
                node[i].to.push_back(node[j]);
            }
        }
    }
    for (int i = 0; i <= 8; ++i) {
        std::vector<int> path;
        path.push_back(i);
        node[i].vis = 1;
        dfs(i, 1, path);
        node[i].vis = 0;
    }
    std::cout << maxPathLength << std::endl;
    std::cout << node[maxPath[0]].light;
    for (int i = 1; i < maxPath.size(); ++i) {
        std::cout << node[maxPath[i]].light.substr(2);
    }
    std::cout << std::endl;
    return 0;
}
