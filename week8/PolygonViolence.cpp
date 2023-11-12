#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>
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
Point s(0, 0, 0);
Point t(10, 10, 0);
int start;
int end;

class Polygon {
    public:
        std::vector<Point> vertices; 
};

class VisibilityGraph {
    public:
        std::vector<Point> nodes;
        std::vector<std::vector<Point>> nodes_nodes;
};
std::map<Point, int> vis;
int cnt = 0;
VisibilityGraph graph;
const int N = 1005;
int head[N], tot = 0;

struct Edge {
    int to, nxt;
    int w;
} e[N * N / 2];

void add(int x, int y, int w) {
    e[++tot].to = y;
    e[tot].nxt = head[x];
    e[tot].w = w;
    head[x] = tot;
}

// 函数来检查两线段是否相交
bool doSegmentsIntersect(const Point& p1, const Point& p2, const Point& v1, const Point& v2) {
    // 计算向量
    Point dir1(p2.x - p1.x, p2.y - p1.y, 0);
    Point dir2(v2.x - v1.x, v2.y - v1.y, 0);
    
    // 计算叉积
    double cross1 = dir1.x * (v1.y - p1.y) - dir1.y * (v1.x - p1.x);
    double cross2 = dir1.x * (v2.y - p1.y) - dir1.y * (v2.x - p1.x);
    
    // 检查叉积符号
    if (cross1 * cross2 >= 0) {
        return false; // 叉积同号，不相交
    }
    
    // 计算叉积
    double cross3 = dir2.x * (p1.y - v1.y) - dir2.y * (p1.x - v1.x);
    double cross4 = dir2.x * (p2.y - v1.y) - dir2.y * (p2.x - v1.x);
    
    // 再次检查叉积符号
    if (cross3 * cross4 >= 0) {
        return false; // 叉积同号，不相交
    }
    
    return true; // 叉积异号，相交
}

int dis(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool arePointsCollinear(const Point& p1, const Point& p2, const Point& p3) {
    // 计算向量
    int vector1X = p2.x - p1.x;
    int vector1Y = p2.y - p1.y;
    int vector2X = p3.x - p1.x;
    int vector2Y = p3.y - p1.y;

    // 计算叉积
    int crossProduct = vector1X * vector2Y - vector1Y * vector2X;

    // 如果叉积为0，三点共线
    return (crossProduct == 0) && (dis(p1, p3) < dis(p1, p2));
}

bool isEdgeVisible(const Point& p1, const Point& p2, const std::vector<Polygon> polygons) {
    for (const Polygon& polygon : polygons) {
        for (size_t i = 0; i < polygon.vertices.size(); ++i) {
            const Point& v1 = polygon.vertices[i];
            const Point& v2 = polygon.vertices[(i + 1) % polygon.vertices.size()];
            
            // 检查线段p1-p2是否与边v1-v2相交
            if (doSegmentsIntersect(p1, p2, v1, v2)) {
                return false; // 有相交，无可见路径
            }
        }
    }
    return true; // 没有相交，有可见路径
}

bool equal(Point x, Point y) {
    if (x.x == y.x && x.y == y.y) {
        return true;
    } else return false;
}

void buildVisibilityGraph(std::vector<Polygon> polygonSet) {
    // std::cout << polygonSet.size() << " ";
    for (int i = 0; i < polygonSet.size(); ++i) {
        int size_i = polygonSet.size();
        for (int j = 0; j < polygonSet[i].vertices.size(); ++j) {
            for (int k = 0; k < polygonSet.size(); ++k) {
                if (i == k) continue;
                int size_k = polygonSet.size();
                for (int l = 0; l < polygonSet[k].vertices.size(); ++l) {
                    if (isEdgeVisible(polygonSet[i].vertices[j], polygonSet[k].vertices[l], polygonSet)) {
                        int flg = 1;
                        for (int p = 0; p < polygonSet.size(); ++p) {
                            int size_p = polygonSet[p].vertices.size();
                            for (int n = 0; n < polygonSet[p].vertices.size(); ++n) {
                                if ((p == i && n == j) || (p == k && n == l)) continue;
                                if (!arePointsCollinear(polygonSet[i].vertices[j], polygonSet[k].vertices[l], polygonSet[p].vertices[n])) {
                                    continue;
                                } else {
                                    flg = 0;
                                    break;
                                }
                            }
                            if (!flg) {
                                // std::cout << "adda";
                                break;
                            }
                        }
                        // std::cout << "a";
                        if (flg) {
                            // std::cout << "Visible Edge: (" << polygonSet[i].vertices[j].x << ", " << polygonSet[i].vertices[j].y << ") to (" << polygonSet[k].vertices[l].x << ", " << polygonSet[k].vertices[l].y << ")\n";
                            if (!vis[polygonSet[i].vertices[j]]) {
                                ++cnt;
                                vis[polygonSet[i].vertices[j]] = cnt;
                                if (equal(polygonSet[i].vertices[j], s)) {
                                    start = cnt;
                                } else if (equal(polygonSet[i].vertices[j], t)) {
                                    end = cnt;
                                }
                            }
                            if (!vis[polygonSet[k].vertices[l]]) {
                                ++cnt;
                                vis[polygonSet[k].vertices[l]] = cnt;
                                if (equal(polygonSet[k].vertices[l], s)) {
                                    start = cnt;
                                } else if (equal(polygonSet[k].vertices[l], t)) {
                                    end = cnt;
                                }
                            }
                            add(vis[polygonSet[i].vertices[j]], vis[polygonSet[k].vertices[l]], dis(polygonSet[i].vertices[j], polygonSet[k].vertices[l]));
                            // add(vis[polygonSet[k].vertices[l]], vis[polygonSet[i].vertices[j]], dis(polygonSet[i].vertices[j], polygonSet[k].vertices[l]));
                            // std::cout << vis[polygonSet[i].vertices[j]] << " " << vis[polygonSet[k].vertices[l]] << " " << dis(polygonSet[i].vertices[j], polygonSet[k].vertices[l]) << "\n";
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < polygonSet.size(); ++i) {
        if (polygonSet[i].vertices.size() == 1) continue;
        for (int j = 0; j < polygonSet[i].vertices.size(); ++j) {
            // std::cout << "A";
            add(vis[polygonSet[i].vertices[j]], vis[polygonSet[i].vertices[(j + 1) % polygonSet[i].vertices.size()]], dis(polygonSet[i].vertices[j], polygonSet[i].vertices[(j + 1) % polygonSet[i].vertices.size()]));
            // add(vis[polygonSet[i].vertices[(j + 1) % polygonSet[i].vertices.size()]], vis[polygonSet[i].vertices[j]], dis(polygonSet[i].vertices[j], polygonSet[i].vertices[(j + 1) % polygonSet[i].vertices.size()]));
            if (j == 0) continue;
            // add(vis[polygonSet[i].vertices[j]], vis[polygonSet[i].vertices[(j - 1) % polygonSet[i].vertices.size()]], dis(polygonSet[i].vertices[j], polygonSet[i].vertices[(j - 1) % polygonSet[i].vertices.size()]));
            add(vis[polygonSet[i].vertices[(j - 1) % polygonSet[i].vertices.size()]], vis[polygonSet[i].vertices[j]], dis(polygonSet[i].vertices[j], polygonSet[i].vertices[(j - 1) % polygonSet[i].vertices.size()]));
        }
    }
}

struct Status {
    int id;
    double dis;
    friend bool operator<(const Status& s1, const Status& s2) {
        return s1.dis > s2.dis;
    }
};

const int INF = 0x7fffffff;
double ans = INF;
double distance[N];
int visit[N];
void Dijkstra() {
    for (int i = 1; i <= cnt; ++i)
        distance[i] = INF;
    distance[start] = 0;
    std::priority_queue<Status> q;
    q.push(Status{start, 0});
    while (!q.empty()) {
        // std::cout << "ada";
        Status cur = q.top();
        q.pop();
        if (visit[cur.id]) continue;
        visit[cur.id] = 1;
        for (int i = head[cur.id]; i ; i = e[i].nxt) {
            int to = e[i].to;
            // if (visit[to]) continue;s
            if (distance[to] > distance[cur.id] + std::sqrt(e[i].w)) {
                distance[to] = distance[cur.id] + std::sqrt(e[i].w);
                q.push(Status{to, distance[to]});
                // std::cout << distance[to] << "\n";
            }
        }
    }
    ans = distance[end];
}

int main() {
    // dis : 14.284
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
    Polygon polygons3;
    polygons3.vertices.push_back(s);
    Polygon polygons4;
    polygons4.vertices.push_back(t);
    polygonSet.push_back(polygons1);
    polygonSet.push_back(polygons2);
    polygonSet.push_back(polygons3);
    polygonSet.push_back(polygons4);
    buildVisibilityGraph(polygonSet);
    Dijkstra();
    std::cout << ans << "\n";
    return 0;
}