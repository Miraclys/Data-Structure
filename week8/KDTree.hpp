#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

int flg = 0;

class Point {
    public:
        int id;
        std::vector<double> coordinates;
        Point(std::vector<double> coordinate, int number)
            : coordinates(coordinate)
            , id(number) {}
        Point(std::vector<double> coordinate)
            : coordinates(coordinates) {} 
};

bool equal(const Point& p1, const Point& p2) {
    int dimension = p1.coordinates.size();
    for (int i = 0; i < dimension; ++i) {
        if (p1.coordinates[i] != p2.coordinates[i]) return false;
    }
    return true;
}

double distance(const Point& p1, const Point& p2) {
    double dis = 0;
    int dimension = p1.coordinates.size();
    double diff = 0;
    for (int i = 0; i < dimension; ++i) {
        diff = p1.coordinates[i] - p2.coordinates[i];
        dis += diff * diff;
    }
    return std::sqrt(dis);
}

class KDTreeNode {
    public:
        KDTreeNode* leftChild;
        KDTreeNode* rightChild;
        Point point;
        KDTreeNode(Point p)
            : point(p)
            , leftChild(nullptr)
            , rightChild(nullptr) {}
};

class KDTree {
    public:
        KDTree() : root(nullptr) {}
        void buildTree(std::vector<Point>&);
        void inOrderTraversal();
        Point find_nearest_point(Point);
        void insert(Point);
        KDTreeNode* search(KDTreeNode*);
    private:
        KDTreeNode* root;
        KDTreeNode* buildTree(std::vector<Point>&, int, int, int);
        void inOrderTraversal(KDTreeNode*);
        KDTreeNode* find_nearest_point(KDTreeNode*, Point, int);
        void insert(KDTreeNode*&, Point, int);
};

KDTreeNode* KDTree::search(KDTreeNode* cur) {
    cur = cur->leftChild;
    while (cur->leftChild)
        cur = cur->leftChild;
    return cur;
}

void KDTree::insert(Point point) {
    // root = insert(root, point, 0);
    insert(root, point, 0);
}

void KDTree::insert(KDTreeNode*& cur, Point point, int depth) {
    if (!cur) {
        cur = new KDTreeNode(point);
        return ;
    }
    int dimension = point.coordinates.size();
    int currentDim = depth % dimension;
    if (cur->point.coordinates[depth] > point.coordinates[depth]) {
        insert(cur->leftChild, point, depth + 1);
    } else if (equal(cur->point, point)) {
        flg = 1;
        // std::cout << "adasd";
        return ;
    } else {
        insert(cur->rightChild, point, depth + 1);
    }
    return ;
}

Point KDTree::find_nearest_point(Point target) {
    return find_nearest_point(root, target, 0)->point;
}

KDTreeNode* KDTree::find_nearest_point(KDTreeNode* cur, Point target, int depth) {
    if (!cur) return nullptr;
    int dimension = target.coordinates.size();
    int currentDim = depth % dimension;
    KDTreeNode* targetBranch = nullptr;
    KDTreeNode* anotherBranch = nullptr;
    if (cur->point.coordinates[currentDim] > target.coordinates[currentDim]) {
        targetBranch = cur->leftChild;
        anotherBranch = cur->rightChild;
    } else {
        targetBranch = cur->rightChild;
        anotherBranch = cur->leftChild;
    }
    KDTreeNode* ans = find_nearest_point(targetBranch, target, depth + 1);
    if (!ans || (ans && distance(ans->point, target) > distance(cur->point, target))) {
        ans = cur;
    }
    if (distance(target, ans->point) > std::abs(cur->point.coordinates[currentDim] - target.coordinates[currentDim])) {
        if (anotherBranch) {
            KDTreeNode* opposite = find_nearest_point(anotherBranch, target, depth + 1);
            if (distance(target, ans->point) > distance(target, opposite->point))
                ans = opposite;
        }
    }
    return ans;
}

void KDTree::inOrderTraversal() {
    inOrderTraversal(root);
    std::cout << "\n";
}

void KDTree::inOrderTraversal(KDTreeNode* cur) {
    if (!cur) return ;
    inOrderTraversal(cur->leftChild);
    std::cout << cur->point.id << " ";
    inOrderTraversal(cur->rightChild);
}

void KDTree::buildTree(std::vector<Point>& points) {
    root = buildTree(points, 0, points.size() - 1, 0);
}

KDTreeNode* KDTree::buildTree(std::vector<Point>& points, int left, int right, int depth) {
    if (right < left) return nullptr;
    if (right == left) {
        KDTreeNode* node = new KDTreeNode(points[left]);
        return node;
    }
    int dimension = points[0].coordinates.size();
    int currentDim = depth % dimension;
    int mid = (left + right) >> 1;
    std::nth_element(points.begin() + left, points.begin() + mid, points.begin() + right + 1, [currentDim](const Point& p1, const Point& p2) {
        return p1.coordinates[currentDim] < p2.coordinates[currentDim];
    });
    // std::sort(points.begin() + left, points.begin() + right + 1, [currentDim](const Point& p1, const Point& p2) {
    //      return p1.coordinates[currentDim] < p2.coordinates[currentDim];
    // });
    KDTreeNode* curNode = new KDTreeNode(points[mid]);
    curNode->leftChild = buildTree(points, left, mid - 1, depth + 1);
    curNode->rightChild = buildTree(points, mid + 1, right, depth + 1);
    return curNode;
}

#endif