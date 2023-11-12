#include <iostream>
#include <vector>

class DisjointSet {
    public:
        DisjointSet(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            size.resize(n, 1);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        void Union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                return;
            }
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
                rank[rootX]++;
            }
        }
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        int getSize(int x) {
            return size[find(x)];
        }
        bool isSameUnion(int x, int y) {
            return find(x) == find(y);
        }
    // private:
        std::vector<int> parent;
        std::vector<int> rank;
        std::vector<int> size;
};

int main() {
    int n = 5;
    DisjointSet ds(n);
    ds.Union(0, 1);
    ds.Union(2, 3);
    ds.Union(0, 4);
    std::cout << ds.isSameUnion(2, 4) << std::endl;
    std::cout << ds.getSize(3) << std::endl;
    std::cout << ds.getSize(0) << std::endl;
    std::cout << (ds.parent[0] == 0) << std::endl;
    return 0;
}