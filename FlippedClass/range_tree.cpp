#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int x, y;
};

class RangeTreeNode {
    public:
        Point p;
        int size;
        int range;
        RangeTreeNode* left;
        RangeTreeNode* right;
        std::vector<Point> points;
        RangeTreeNode* associate;
        RangeTreeNode(Point p, int size, int range, RangeTreeNode* left, RangeTreeNode* right) {
            this->p = p;
            this->size = size;
            this->left = left;
            this->right = right;
            this->range = range;
            this->associate = nullptr;
        }
        void traverse() {
            if (left) {
                left->traverse();
            }
            if (right) {
                right->traverse();
            }
            if (points.size() == 1) {
                std::cout << points[0].x << "\n";
            }
        }
};

void build_range_tree(RangeTreeNode* cur, int l, int r, int range, std::vector<Point> points) {
    if (l == r) {
        cur->points.push_back(points[l]);
        cur->p = points[l];
        cur->size = 1;
        cur->range = range;
        RangeTreeNode* node = new RangeTreeNode(points[l], 1, 1, nullptr, nullptr);
        cur->associate = node;
        return;
    }
    int mid = (l + r) / 2;
    cur->p = points[mid];
    cur->range = range;
    cur->points.assign(points.begin() + l, points.begin() + r + 1);
    cur->left = new RangeTreeNode(points[mid], mid - l + 1, range, nullptr, nullptr);
    cur->right = new RangeTreeNode(points[mid + 1], r - mid, range, nullptr, nullptr);
    build_range_tree(cur->left, l, mid, range, points);
    build_range_tree(cur->right, mid + 1, r, range, points);
    if (range == 2) {
        RangeTreeNode* node = new RangeTreeNode(points[mid], cur->points.size(), 1, nullptr, nullptr);
        cur->associate = node;
        node->points = cur->points;
        std::sort(node->points.begin(), node->points.end(), [](Point a, Point b) {
            return a.y < b.y;
        });
        mid = (l + r) / 2;
        cur->associate->left = new RangeTreeNode(points[mid], mid - l + 1, range, nullptr, nullptr);
        cur->associate->right = new RangeTreeNode(points[mid + 1], r - mid, range, nullptr, nullptr);
        mid = (0 + cur->associate->points.size() - 1) / 2;
        build_range_tree(cur->associate->left, 0, mid, 1, node->points);
        build_range_tree(cur->associate->right, mid + 1, cur->associate->points.size() - 1, 1, node->points);
    }
}

RangeTreeNode* get_split(RangeTreeNode* cur, int range, int l, int r) {
    if (cur->range == 2) {
        if (cur->p.x >= l && cur->p.x <= r) {
            return cur;
        }
        if (cur->p.x < l) {
            return get_split(cur->right, range, l, r);
        } else {
            return get_split(cur->left, range, l, r);
        }
    } else {
        if (cur->p.y >= l && cur->p.y <= r) {
            return cur;
        }
        if (cur->p.y < l) {
            return get_split(cur->right, range, l, r);
        } else {
            return get_split(cur->left, range, l, r);
        }
    }
    return nullptr;
}

int main() {
    std::vector<Point> points = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 1},
        {5, 5},
        {6, 0}
    };
    std::sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    int len = points.size();
    RangeTreeNode* root = new RangeTreeNode(points[0], len, 2, nullptr, nullptr);
    build_range_tree(root, 0, len - 1, 2, points);
    root->traverse();
    // std::cout << root->right->p.x << "\n";
    // std::cout << get_split(root, 2, 4, 9)->p.x << "\n";
    return 0;
}