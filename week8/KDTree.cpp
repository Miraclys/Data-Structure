#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Point {
    public:
        std::vector<double> coordinate;
        int id;
        Point(int identifier)
            : id(identifier) {}
        Point(std::vector<double> coords, int identifier)
            : coordinate(coords)
            , id(identifier) {};
};

double distance(const Point& p1, const Point& p2) {
    double dis = 0.0;
    for (int i = 0; i < p1.coordinate.size(); ++i) {
        double diff = p1.coordinate[i] - p2.coordinate[i];
        dis += diff * diff;
    }
    return dis;
}

class KDTreeNode {
    public:
        Point point;
        KDTreeNode* parent;
        KDTreeNode* leftChild;
        KDTreeNode* rightChild;
        KDTreeNode(Point p)
            : point(p)
            , parent(nullptr)
            , leftChild(nullptr)
            , rightChild(nullptr) {}
};

class KDTree {
    public: 
        void buildTree(std::vector<Point>&);
        KDTree() : root(nullptr) {}
        Point findNearestPoint(Point);
        void inOrderTraversal();
    private:
        KDTreeNode* root;
        Point findNearestPoint(KDTreeNode*, Point, int);
        KDTreeNode* buildTree(std::vector<Point>&,  int, int, int);
        void inOrderTraversal(KDTreeNode*);
};

void KDTree::inOrderTraversal() {
    inOrderTraversal(root);
    std::cout << "\n";
}

void KDTree::inOrderTraversal(KDTreeNode* cur) {
    if (cur == nullptr) return ;
    inOrderTraversal(cur->leftChild);
    std::cout << cur->point.id << " ";
    inOrderTraversal(cur->rightChild);
}

Point KDTree::findNearestPoint(Point curNode) {
    return findNearestPoint(root, curNode, 0);
}

bool equal(const Point& p1, const Point& p2) {
    int dimension = p1.coordinate.size();
    for (int i = 0; i < dimension; ++i) {
        if (p1.coordinate[i] != p2.coordinate[i]) return 0;
    }
    return 1;
}

/// @brief 找出距离 target 最近的 point
/// @param curNode 当前递归到哪一个 KDTreeNode
/// @param target 目标的 Point
/// @param depth 当前的维度
/// @return 距离 Target 最近的 Point
Point KDTree::findNearestPoint(KDTreeNode* curNode, Point target, int depth) {
    // std::cout << "bug";
    if (curNode == nullptr) return Point(-1);
    int dimension = curNode->point.coordinate.size();
    int currentDim = depth % dimension;
    KDTreeNode* nextBranch = nullptr;
    KDTreeNode* oppositeBranch = nullptr;
    if (target.coordinate[currentDim] < curNode->point.coordinate[currentDim]) {
        nextBranch = curNode->leftChild;
        oppositeBranch = curNode->rightChild;
    } else {
        nextBranch = curNode->rightChild;
        oppositeBranch = curNode->leftChild;
    }
    Point best = findNearestPoint(nextBranch, target, depth + 1);
    if (best.id != -1 && distance(target, best) > std::abs(target.coordinate[currentDim] - curNode->point.coordinate[currentDim])) {
        Point opposite = findNearestPoint(oppositeBranch, target, depth + 1);
        if (opposite.id != -1 && distance(target, opposite) < distance(target, best)) {
            best = opposite;
        }
    }
    if (!equal(target, curNode->point) && best.id != -1 && distance(target, curNode->point) < distance(target, best)) {
        best = curNode->point;
    } else if (best.id == -1 && !equal(target, curNode->point)) best = curNode->point;
    return best;
}

void KDTree::buildTree(std::vector<Point>& points) {
    root = buildTree(points, 0, points.size() - 1, 0);
}

/// @brief 实现构建 KD 树
/// @param points 
/// @param curNode 表示当前区间的首个位置的迭代器
/// @param length 
/// @param depth 
/// @return 
KDTreeNode* KDTree::buildTree(std::vector<Point>& points, int left, int right, int depth) {
    if (left > right) return nullptr;
    if (left == right) {
        KDTreeNode* node = new KDTreeNode(points[left]);
        return node;
    }
    int dimension = points[0].coordinate.size();
    int currentDim = depth % dimension;
    std::sort(points.begin() + left, points.begin() + right + 1, [currentDim](const Point& p1, const Point& p2) {
         return p1.coordinate[currentDim] < p2.coordinate[currentDim];
    });
    int median = (left + right) >> 1;
    KDTreeNode* node = new KDTreeNode(points[median]);
    node->leftChild = buildTree(points, left, median - 1, depth + 1);
    node->rightChild = buildTree(points, median + 1, right, depth + 1);
    return node;
}

#endif

#include <cmath>

int main() {
    // freopen("P1429_4.in", "r", stdin);
    // freopen("ans.txt", "w", stdout);
    std::vector<Point> points;
    points.push_back(Point({2, 3}, 0));
    points.push_back(Point({5, 4}, 1));
    points.push_back(Point({9, 6}, 2));
    points.push_back(Point({4, 7}, 3));
    points.push_back(Point({8, 1}, 4));
    points.push_back(Point({7, 2}, 5));
    KDTree kdt;
    kdt.buildTree(points);
    kdt.inOrderTraversal();
    Point target({5, 5}, -1);
    // kdt.inOrderTraversal();
    // // std::cout << "adad";
    Point nearest = kdt.findNearestPoint(target);
    // // std::cout << "1312";
    std::cout << "Nearest neighbor to target: Point " << nearest.id << std::endl;
    // std::vector<Point> points;
    // int n;
    // std::cin >> n;
    // double x, y;
    // for (int i = 1; i <= n; ++i) {
    //     std::cin >> x >> y;
    //     points.push_back(Point{{x, y}, i - 1});
    // }
    // std::vector<Point> cur(points);
    // // for (auto element : cur) {
    // //     std::cout << element.id << " ";
    // // }
    // KDTree kdt;
    // kdt.buildTree(points);
    // double Min = 99999999;
    // for (int i = 0; i < cur.size(); ++i) {
    //     // std::cout << distance(cur[i], kdt.findNearestPoint(cur[i])) << "\n";
    //     Min = std::min(Min, std::sqrt(distance(cur[i], kdt.findNearestPoint(cur[i]))));
    // }
    // printf("%.4lf\n", Min);
    return 0;
}