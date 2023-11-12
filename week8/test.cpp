#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <queue>
#include <limits>
#include <map>

#define Max 1000

//算法还需进一步优化，主要问题集中与线段之间的距离关系如何通过一个点量化的问题，目前基本功能都能实现但是算法复杂度还是有问题

struct Point
{
    double x;
    double y;
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Point &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};

struct Edge
{
    Point from;
    Point to;
};

struct EdgeDistance
{
    Edge edge;
    double distance;

    EdgeDistance(const Edge &e, double d)
        : edge(e), distance(d)
    {
    }

    bool operator<(const EdgeDistance &other) const
    {
        return distance < other.distance;
    }
};

struct Path
{
    Point front;
    Point back;
    double weight;
};


//是否在一条直线上
bool onSegment(const Point &p, const Point &q, const Point &r)
{
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

//以极角排序
bool sortByAngle(const Point &p, const Point &q, const Point &reference)
{
    double angleP = atan2(p.y - reference.y, p.x - reference.x);
    double angleQ = atan2(q.y - reference.y, q.x - reference.x);
    if (angleP < angleQ)
        return true;
    if (angleP > angleQ)
        return false;
    return std::hypot(p.x - reference.x, p.y - reference.y) < std::hypot(q.x - reference.x, q.y - reference.y);
}

//两个点之间的距离
double euclideanDistance(const Point &a, const Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

//计算两条线段的交点坐标
Point calculateIntersection(const Point &p1, const Point &q1, const Point &p2, const Point &q2)
{
    double A1 = q1.y - p1.y;
    double B1 = p1.x - q1.x;
    double C1 = A1 * p1.x + B1 * p1.y;

    double A2 = q2.y - p2.y;
    double B2 = p2.x - q2.x;
    double C2 = A2 * p2.x + B2 * p2.y;
    double determinant = A1 * B2 - A2 * B1;

    if (determinant == 0)
    {
        return Point{0.0, 0.0};
    }
    else
    {
        double x = (B2 * C1 - B1 * C2) / determinant;
        double y = (A1 * C2 - A2 * C1) / determinant;
        return Point{x, y};
    }
}

//返回所有点
std::vector<Point> combinePolygonPoints(const std::vector<std::vector<Point>> &polygonPoints)
{
    std::vector<Point> allPoints;

    for (const auto &polygon : polygonPoints)
    {
        allPoints.insert(allPoints.end(), polygon.begin(), polygon.end());
    }

    return allPoints;
}

//找到障碍体的所有边
std::vector<Edge> convertPointToEdges(const std::vector<Point> &polygonPoint)
{
    std::vector<Edge> polygonEdges;
    if (polygonPoint.size() < 3)
    {
        std::cerr << "Error: A polygon must have at least 3 points." << std::endl;
        return polygonEdges;
    }

    for (size_t i = 0; i < polygonPoint.size() - 1; ++i)
    {
        Edge edge;
        edge.from = polygonPoint[i];
        edge.to = polygonPoint[i + 1];
        polygonEdges.push_back(edge);
    }
    Edge closingEdge;
    closingEdge.from = polygonPoint.back();
    closingEdge.to = polygonPoint.front();
    polygonEdges.push_back(closingEdge);
    return polygonEdges;
}

//找到障碍体的所有边
std::vector<Edge> convertPointsToEdges(const std::vector<std::vector<Point>> &polygonPoints)
{
    std::vector<Edge> polygonEdges;
for(const std::vector<Point> polygonPoint:polygonPoints)
    {
        if (polygonPoint.size() < 3)
        {
            std::cerr << "Error: A polygon must have at least 3 points." << std::endl;
            return polygonEdges;
        }

        for (size_t i = 0; i < polygonPoint.size() - 1; ++i)
        {
            Edge edge;
            edge.from = polygonPoint[i];
            edge.to = polygonPoint[i + 1];
            polygonEdges.push_back(edge);
        }
        Edge closingEdge;
        closingEdge.from = polygonPoint.back();
        closingEdge.to = polygonPoint.front();
        polygonEdges.push_back(closingEdge);
    }
    return polygonEdges;
}

//线段是否在其左侧
bool isLeftSide(const Point &p1, const Point &p2, const Point &p3, const Point &p4)
{
    double v1x = p2.x - p1.x;
    double v1y = p2.y - p1.y;
    double v2x = p4.x - p3.x;
    double v2y = p4.y - p3.y;
    double crossProduct = v1x * v2y - v1y * v2x;
    return crossProduct > 0; 
}

//两线段是否相交
bool doIntersect(const Point &p1, const Point &q1, const Point &p2, const Point &q2)
{
    auto orientation = [](const Point &p, const Point &q, const Point &r)
    {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0)
            return 0;
        return (val > 0) ? 1 : 2;
    };
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 == 0 && onSegment(p1, p2, q1))
        return false;
    if (o2 == 0 && onSegment(p1, q2, q1))
        return false;
    if (o3 == 0 && onSegment(p2, p1, q2))
        return false;
    if (o4 == 0 && onSegment(p2, q1, q2))
        return false;
    if (o1 != o2 && o3 != o4)
        return true;

    return false;
}

//是否在图形内部
bool isInsideObstacleLocally(const Point &p, const std::vector<Point> &obstacle)
{
    int n = obstacle.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        Point p1 = obstacle[i];
        Point p2 = obstacle[(i + 1) % n];
        if (onSegment(p1, p, p2))
            return false;
        if ((p1.y <= p.y && p2.y > p.y) || (p2.y <= p.y && p1.y > p.y))
        {
            double intersectX = (p1.x + (p.y - p1.y) / (p2.y - p1.y) * (p2.x - p1.x));
            if (p.x < intersectX)
            {
                count++;
            }
        }
    }
    return (count % 2 == 1);
}

//两点之间是否直接可见
bool isVisible(const Point &p, const Point &q, const std::vector<std::vector<Point>> &obstacles)
{
    for (const auto &obstacle : obstacles)
    {
        for (size_t i = 0; i < obstacle.size(); ++i)
        {
            const Point &edgeStart = obstacle[i];
            const Point &edgeEnd = obstacle[(i + 1) % obstacle.size()];
            if (doIntersect(p, q, edgeStart, edgeEnd))
            {
                return false;
            }
        }
    }
    return true;
}

//所有点搜索顺序先后排序
std::set<EdgeDistance> findEdgesIntersectedByHalfline(const Point &p, const std::vector<std::vector<Point>> &obstacles)
{
std::set<EdgeDistance> intersectedEdges;
for(const std::vector<Point> &obstacle : obstacles){
        std::vector<Edge> getedge = convertPointToEdges(obstacle);
        for (const Edge &edge : getedge)
        {
            if (doIntersect(p, Point{p.x + Max, p.y}, edge.from, edge.to))
            {
                Point intersection = calculateIntersection(p, Point{p.x + Max, p.y}, edge.from, edge.to);
                double distance = euclideanDistance(p, intersection);
                intersectedEdges.insert(EdgeDistance{edge, distance});
            }
    }
};
    return intersectedEdges;
}

//生成所有路径图
std::vector<Path> VISIBLEVERTICES(const Point &start, const Point &end, const std::vector<std::vector<Point>> &obstacles)
{
    std::vector<Path> shortpath;
    std::vector<Edge> insertEdges;                                  
    std::vector<Point> allpoints = combinePolygonPoints(obstacles); 
    allpoints.push_back(start);
    allpoints.push_back(end);
    std::sort(allpoints.begin(), allpoints.end());
    for (const Point &firstpoint : allpoints)
    {
        for (const Point &secondpoint : allpoints)
        {
            if (firstpoint != secondpoint)
            {
                if (isVisible(firstpoint, secondpoint, obstacles))
                {
                    insertEdges.push_back({firstpoint, secondpoint});
                }
            }
        }
    }

    for (const Edge &edge : insertEdges)
    {
        double weight = euclideanDistance(edge.from, edge.to);
        shortpath.push_back({edge.from, edge.to, weight});
    }

    return shortpath;
}

//dijkstra算法实现
std::vector<Path> dijkstra(const std::vector<Path> &edges, Point start, Point end)
{
    std::set<Point> unvisited;
    for (const Path &edge : edges)
    {
        unvisited.insert(edge.front);
        unvisited.insert(edge.back);
    }

    std::map<Point, double> distance;
    for (const Point &point : unvisited)
    {
        distance[point] = std::numeric_limits<double>::max();
    }
    distance[start] = 0.0;

    std::map<Point, Point> previous;

    while (!unvisited.empty())
    {
        Point current = *unvisited.begin();
        for (const Point &point : unvisited)
        {
            if (distance[point] < distance[current])
                current = point;
        }

        unvisited.erase(current);

        if (current == end)
        {
            std::vector<Path> shortestPath;
            while (current != start)
            {
                Point prev = previous[current];
                for (const Path &edge : edges)
                {
                    if ((edge.front == prev && edge.back == current) || (edge.back == prev && edge.front == current))
                    {
                        shortestPath.push_back(edge);
                        break;
                    }
                }
                current = prev;
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        for (const Path &edge : edges)
        {
            if (edge.front == current || edge.back == current)
            {
                Point neighbor = (edge.front == current) ? edge.back : edge.front;
                double alt = distance[current] + edge.weight;
                if (alt < distance[neighbor])
                {
                    distance[neighbor] = alt;
                    previous[neighbor] = current;
                }
            }
        }
    }

    return std::vector<Path>();
}


int main()
{
    Point start = {0, 0};
    Point end = {10, 10};
    std::vector<std::vector<Point>> obstacles = {
        {{1,1},{1,2},{2,2},{2,1}},{{3,3},{3,5},{4,5},{4,3}}
    };
    for(const std::vector<Point> obstacle:obstacles){
        if (isInsideObstacleLocally(start, obstacle) || isInsideObstacleLocally(end, obstacle)){
            std::cout << "the point is in the obstacle" << std::endl;
            return 0;
        }
    }

    if(isVisible(start,end,obstacles)){
        std::cout << "from start to end, distance is:" << euclideanDistance(start, end) << std::endl;
    }else{
        std::vector<Path> indexpath = VISIBLEVERTICES(start, end, obstacles);
        std::vector<Path> shortestpath = dijkstra(indexpath, start, end);
        double distance;
        for (const Path &edge : shortestpath)
        {
            std::cout << "From (" << edge.front.x << ", " << edge.front.y << ") to (" << edge.back.x << ", " << edge.back.y << ") with weight " << edge.weight << std::endl;
            distance += edge.weight;
        }
        std::cout << "The whole path weight is: " << distance << std::endl;
    }

    return 0;
}

