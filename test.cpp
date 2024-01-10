#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const double INF = 1e10;
struct Point {
	double x, y;
	int id;//用来查询时避免同一个点求解到自身的距离（针对题目所设置）
};
typedef vector<Point> Points;
struct kdTreeNode {
	int dim;//切分维度,0是x，1是y
	kdTreeNode* left;
	kdTreeNode* right;
	Point p;
	kdTreeNode(int d, Point val) :dim(d), p(val), left(NULL), right(NULL) {};
};
double dis(Point a, Point b) {
	if (a.id == b.id) {
		return INF;
	}
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
kdTreeNode* buildTree(Points& pts, int d,int left,int right) {
	if (left > right) {
		return NULL;
	}
	d %= 2;
	int mid = (right - left) / 2 + left;
	nth_element(pts.begin() + left, pts.begin() + mid, pts.begin() + right+1, [d](Point a, Point b) {return d == 0 ? a.x < b.x :a.y < b.y; });//找到中间点，并且左边小于中间点，右边大于(快速选择算法，时间复杂度O(n))
	Point p = pts[mid];
	kdTreeNode* root = new kdTreeNode(d, p);
	root->left = buildTree(pts, d + 1, left, mid-1);
	root->right = buildTree(pts,d + 1, mid + 1,right);
	return root;
}
void query(kdTreeNode* t, Point target,double& minDis) {
	if (t == NULL) {
		return;
	}
	if (t->dim == 0) {
		if (target.x < t->p.x) {
			query(t->left, target, minDis);
		}
		else {
			query(t->right, target, minDis);
		}
		minDis = min(minDis, dis(target, t->p));
		if (minDis > abs(target.x-t->p.x)) {
			if (target.x < t->p.x) {
				query(t->right, target, minDis);
			}
			else {
				query(t->left, target, minDis);
			}
		}
	}
	else {
		if (target.y < t->p.y) {
			query(t->left, target, minDis);
		}
		else {
			query(t->right, target, minDis);
		}
		minDis = min(minDis, dis(target, t->p));
		if (minDis > abs(target.y - t->p.y)) {
			if (target.y < t->p.y) {
				query(t->right, target, minDis);
			}
			else {
				query(t->left, target, minDis);
			}
		}
	}
}
int main() {
	int n;
	cin >> n;
	Points a;
	for (int j = 0; j < n; ++j) {
		double x, y;
		cin >> x >> y;
		a.push_back({ x,y,j });
	}
	kdTreeNode* t = buildTree(a, 0, 0, a.size() - 1);
	double ans = INF;
	for (int i = 0; i < a.size(); i++) {
		double minDis = INF;
		query(t, a[i],minDis);
		ans = min(ans, minDis);
	}
	printf("%.3f", ans);
	system("pause");
	return 0;
}