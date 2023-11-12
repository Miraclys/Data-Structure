#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>

class Point {
    public:
        int x;
        int y;
        int id;
        Point(int X, int Y, int number)
            : x(X)
            , y(Y)
            , id(number) {}  
    friend bool operator<(const Point& p1, const Point& p2) {
        if (p1.x != p2.x) {
            return p1.x < p2.x;
        } else {
            return p1.y < p2.y;
        }
    }
};
int s = 10;
int t = 10;
int start;
int end;

class Polygon {
    public:
        std::vector<Point> vertices; 
};

bool equal(Point x, Point y) {
    if (x.x == y.x && x.y == y.y) {
        return true;
    } else return false;
}

// 函数来检查两线段是否相交
bool doSegmentsIntersect(const Point& p1, const Point& p2, const Point& v1, const Point& v2) {
    Point dir1(p2.x - p1.x, p2.y - p1.y, 0);
    Point dir2(v2.x - v1.x, v2.y - v1.y, 0);
    double cross1 = dir1.x * (v1.y - p1.y) - dir1.y * (v1.x - p1.x);
    double cross2 = dir1.x * (v2.y - p1.y) - dir1.y * (v2.x - p1.x);
    if (cross1 * cross2 >= 0) {
        return false;
    }
    double cross3 = dir2.x * (p1.y - v1.y) - dir2.y * (p1.x - v1.x);
    double cross4 = dir2.x * (p2.y - v1.y) - dir2.y * (p2.x - v1.x);
    if (cross3 * cross4 >= 0) {
        return false;
    }
    return true;
}

int dis(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

struct Status {
    int x, y;
    double dis;
    friend bool operator<(const Status& s1, const Status& s2) {
        if (s1.x != s2.x && s2.y != s1.y) {
            // return s1.dis + abs(s1.x - s) + abs(s1.y - t) > s2.dis + abs(s2.x - s) + abs(s2.y - t);
            return s1.dis + std::sqrt((s1.x - s) * (s1.x - s) + (s1.y - t) * (s1.y - t)) > s2.dis + std::sqrt((s2.x - s) * (s2.x - s) + (s2.y - t) * (s2.y - t));
        } else {
            return s1.x <= s2.x;
        }
    };
};

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {1, 1, 1, 0, 0, -1, -1, -1};

bool isEdgeVisible(const Point p1, const Point p2, const std::vector<Polygon> polygons) {
    for (const Polygon& polygon : polygons) {
        for (size_t i = 0; i < polygon.vertices.size(); ++i) {
            const Point& v1 = polygon.vertices[i];
            const Point& v2 = polygon.vertices[(i + 1) % polygon.vertices.size()];
            if (doSegmentsIntersect(p1, p2, v1, v2)) {
                return false; // 有相交，无可见路径
            }
        }
    }
    return true; // 没有相交，有可见路径
}

int main() {
    // dis : 14.7292
    std::vector<Polygon> polygonSet;
    Polygon polygons1;
    polygons1.vertices.push_back(Point{1, 1, 1});
    polygons1.vertices.push_back(Point{1, 2, 2});
    polygons1.vertices.push_back(Point{2, 1, 3});
    polygons1.vertices.push_back(Point{2, 2, 4});
    Polygon polygons2;
    polygons2.vertices.push_back(Point{3, 3, 5});
    polygons2.vertices.push_back(Point{3, 5, 6});
    polygons2.vertices.push_back(Point{4, 5, 7});
    polygons2.vertices.push_back(Point{4, 3, 8});
    polygonSet.push_back(polygons1);
    polygonSet.push_back(polygons2);
    int s = 10;
    int t = 10;
    std::priority_queue<Status> q;
    q.push(Status{0, 0, 0.0});
    while (!q.empty()) {
        Status cur = q.top();
        q.pop();
        int x = cur.x;
        int y = cur.y;
        if (x == s && y == t) {
            std::cout << cur.dis << "\n";
            return 0;
        }
        for (int i = 0; i < 8; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (isEdgeVisible(Point{x, y, 0}, Point{tx, ty, 0}, polygonSet)) {
                q.push(Status{tx, ty, cur.dis + std::sqrt(dx[i] * dx[i] + dy[i] * dy[i])});
            }
        } 
    }
}