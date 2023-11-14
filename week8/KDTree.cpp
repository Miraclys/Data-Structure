#include "./KDTree.hpp"
#include <cmath>

int main() {
    // freopen("P1429_1.in", "r", stdin);
    // freopen("ans.txt", "w", stdout);
    std::vector<Point> points;
    points.push_back(Point({2, 3}, 0));
    points.push_back(Point({5, 4}, 1));
    points.push_back(Point({9, 6}, 2));
    points.push_back(Point({4, 7}, 3));
    points.push_back(Point({8, 1}, 4));
    points.push_back(Point({7, 2}, 5));
    KDTree kdt;
    for (const auto& element : points) {
        kdt.insert(element);
    }
    kdt.buildTree(points);
    kdt.inOrderTraversal();
    std::cout << kdt.find_nearest_point(Point{{5, 5}, -1}).id;
    return 0;
}