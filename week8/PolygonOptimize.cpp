#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <queue>

class Point {
    public:
        int x;
        int y;
        int id;
        bool operator==(Point other) {
            return x == other.x && y == other.y;
        }
        bool operator!=(Point other) {
            if (x == other.x && y == other.y) return 0;
            else return 1;
        }
        bool operator<(Point p2) {
            if (x != p2.x) {
                return x < p2.x;
            } else {
                return y < p2.y;
            }
        }
        Point(int X, int Y, int number)
            : x(X)
            , y(Y)
            , id(number) {}  
    
};
Point start(0, 0, 0);
Point end(10, 10, 0);

class Segment {
    public:
        Point start;
        Point end;
        Segment(const Point& p1, const Point& p2)
            : start(p1)
            , end(p2) {}
        bool operator<(Segment other) {
            return start < other.start;
        }
};

class Polygon {
    public:
        std::vector<Point> vertices; 
        Polygon() {}
        Polygon(std::vector<Point> v)
            : vertices(v) {}
};

bool equal(Point x, Point y) {
    if (x.x == y.x && x.y == y.y) {
        return true;
    } else return false;
}

bool isPointInside(const Point& point, const Polygon& polygon) {
        int numVertices = polygon.vertices.size();
        int intersectionCount = 0;
        for (int i = 0; i < numVertices; i++) {
            const Point& p1 = polygon.vertices[i];
            const Point& p2 = polygon.vertices[(i + 1) % numVertices];  // 下一个顶点
            // 检查点是否在线段上
            if (point.x == p1.x && point.y == p1.y) {
                return true;  // 点在多边形的顶点上
            }
            // 检查射线与线段的交点
            if ((p1.y > point.y) != (p2.y > point.y) &&
                point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x) {
                intersectionCount++;
            }
        }
        return (intersectionCount % 2) == 1;  // 奇数个交点表示点在多边形内部
}

// 函数来检查两线段是否相交
bool doSegmentsIntersect2(Point p1, Point p2, Point v1, Point v2) {
    Point dir1(p2.x - p1.x, p2.y - p1.y, 0);
    Point dir2(v2.x - v1.x, v2.y - v1.y, 0);
    double cross1 = dir1.x * (v1.y - p1.y) - dir1.y * (v1.x - p1.x);
    double cross2 = dir1.x * (v2.y - p1.y) - dir1.y * (v2.x - p1.x);
    if (cross1 * cross2 >= 0) {
        return false; // 叉积同号，不相交
    }
    double cross3 = dir2.x * (p1.y - v1.y) - dir2.y * (p1.x - v1.x);
    double cross4 = dir2.x * (p2.y - v1.y) - dir2.y * (p2.x - v1.x);
    
    if (cross3 * cross4 >= 0) {
        return false; // 叉积同号，不相交
    }
    return true; // 叉积异号，相交
}

int dis(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool isPointInsidePolygon(const Point& point, const Polygon& polygon) {
    int numVertices = polygon.vertices.size();
    int intersectionCount = 0;
    for (int i = 0; i < numVertices; i++) {
        const Point& p1 = polygon.vertices[i];
        const Point& p2 = polygon.vertices[(i + 1) % numVertices];  // 下一个顶点
        if (point.x == p1.x && point.y == p1.y) {
            return true;  
        }
        if ((p1.y > point.y) != (p2.y > point.y) &&
            point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x) {
            intersectionCount++;
        }
    }

    return (intersectionCount % 2) == 1;  // 奇数个交点表示点在多边形内部
}

bool areNotAdjacentVertices(Point p1, Point p2, std::vector<Polygon> polygonSet) {
    for (const Polygon&  polygon : polygonSet) {
        std::vector<Point> polygonVertices = polygon.vertices;
        int p1Index = -1; // 初始化为无效值
        int p2Index = -1; // 初始化为无效值
        for (int i = 0; i < polygonVertices.size(); ++i) {
            if (polygonVertices[i] == p1) {
                p1Index = i;
            }
            if (polygonVertices[i] == p2) {
                p2Index = i;
            }
        }
        if (p1Index == -1 || p2Index == -1) {
            return false;
        }
        if (std::abs(p1Index - p2Index) != 1 && std::abs(p1Index - p2Index) != polygonVertices.size() - 1) {
            return true;
        }
    }
    return false;
}

bool VISIBLE(const Point& wi, const Point& p, const std::set<Segment>& edgeSet, std::vector<Polygon> polygonSet) {
    std::vector<Point> pa;
    if (areNotAdjacentVertices(wi, p, polygonSet)) {
        return false;
    }
    if (edgeSet.empty()) {
        return true;
    }
    auto it = edgeSet.begin();
    if (!equal(it->start, p)) {
        return false;
    }
    while (it != edgeSet.end() && !equal(it->end, p)) {
        if (!equal(it->start, p)) {
            return false;
        }
        ++it;
    }
    return it == edgeSet.end();
}

std::vector<Point> visiblePoints(Point cur, std::vector<Polygon> polygonSet) {
    std::vector<Point> sortedVertices;
    for (const Polygon& polygon : polygonSet) {
        for (const Point& point : polygon.vertices) {
            sortedVertices.push_back(point);
        }
    }
    std::sort(sortedVertices.begin(), sortedVertices.end(), [&](const Point& p1, const Point& p2) {
        double angle1 = atan2(p1.y - cur.y, p1.x - cur.x);
        double angle2 = atan2(p2.y - cur.y, p2.x - cur.x);
        return angle1 < angle2;
    });
    std::set<Segment> edgeSet;
    std::vector<Point> W;
    // return sortedVertices;
    for (const Point& wi : sortedVertices) {
        if (VISIBLE(wi, cur, edgeSet, polygonSet)) {
            W.push_back(wi);
        }
        auto it = edgeSet.lower_bound(Segment(cur, wi));
        if (it != edgeSet.begin() && !equal((--it)->end, wi)) {
            it = edgeSet.erase(it);
        }
        while (it != edgeSet.end() && doSegmentsIntersect2(cur, wi, it->start, it->end)) {
            it = edgeSet.erase(it);
        }

        edgeSet.insert(Segment(cur, wi));
    }
    return W;
}

const int N = 1005;
const int inf = 0x7fffffff;
int head[N];
int cnt = 0, vis[N], tot = 0;
double distance[N];
struct Edge {
    int to, nxt;
    double w;
} e[N * (N - 1)];

void add(int x, int y, int w) {
    e[++cnt].to = y;
    e[cnt].w = w;
    e[cnt].nxt = head[x];
    head[x] = cnt;
}

struct Status {
    int id;
    double dis;
    bool operator<(const Status& s) {
        return dis > s.dis;
    }
};

int s, t;
int ans = inf;

void Dijkstra() {
    std::priority_queue<Status> q;
    for (int i = 1; i <= tot; ++i)
        distance[i] = inf;
    distance[s] = 0;
    while (!q.empty()) {
        Status cur = q.top();
        q.pop();
        if (vis[cur.id]) continue;
        vis[cur.id] = 1;
        for (int i = head[cur.id]; i ; i = e[i].nxt) {
            int to = e[i].to;
            if (distance[to] > distance[cur.id] + e[i].w) {
                distance[to] = distance[cur.id] + e[i].w;
                q.push(Status{to, distance[to]});
            }
        }
    }
}

int main() {
    std::vector<Polygon> polygonsSet;
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
    polygonsSet.push_back(polygons1);
    polygonsSet.push_back(polygons2);
    // std::vector<std::vector<Point>> edge;
    // std::vector<Point> v = visiblePoints(start, polygonsSet);
    // for (auto element : v) {
    //     std::cout << element.x << " " << element.y << "\n";
    // }
    std::vector<Point> pointSet;
    std::vector<Point> sortedVertices;
    for (const Polygon& polygon : polygonsSet) {
        for (const Point& point : polygon.vertices) {
            pointSet.push_back(point);
        }
    }
    std::vector<std::vector<Point>> edge;
    for (const Point& point : pointSet) {
        edge[point.id] = visiblePoints(point, polygonsSet);
    }
    Dijkstra();
    std::cout << ans << " ";
    return 0;
}