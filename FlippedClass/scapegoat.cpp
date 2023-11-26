#include <vector>
using namespace std;

namespace Scapegoat_Tree {
#define MAXN (100000 + 10)
	const double alpha = 0.75;
	struct Node {
	Node * ch[2];
	int key, size, cover; // size为有效节点的数量，cover为节点总数量 
	bool exist;	// 是否存在（即是否被删除） 
	void PushUp(void) {
		size = ch[0]->size + ch[1]->size + (int)exist;
		cover = ch[0]->cover + ch[1]->cover + 1;
	}
	bool isBad(void) { // 判断是否需要重构 
		return ((ch[0]->cover > cover * alpha + 5) || 
				(ch[1]->cover > cover * alpha + 5));
		}
	};
	struct STree {
	protected:
		Node mem_poor[MAXN]; //内存池，直接分配好避免动态分配内存占用时间 
		Node *tail, *root, *null; // 用null表示NULL的指针更方便，tail为内存分配指针，root为根 
		Node *bc[MAXN]; int bc_top; // 储存被删除的节点的内存地址，分配时可以再利用这些地址 

		Node * NewNode(int key) {
			Node * p = bc_top ? bc[--bc_top] : tail++;
			p->ch[0] = p->ch[1] = null;
			p->size = p->cover = 1; p->exist = true;
			p->key = key;
			return p;
		}
		void Travel(Node * p, vector<Node *>&v) {
			if (p == null) return;
			Travel(p->ch[0], v);
			if (p->exist) v.push_back(p); // 构建序列 
			else bc[bc_top++] = p; // 回收 
			Travel(p->ch[1], v);
		}
		Node * Divide(vector<Node *>&v, int l, int r) {
			if (l >= r) return null;
			int mid = (l + r) >> 1;
			Node * p = v[mid];
			p->ch[0] = Divide(v, l, mid);
			p->ch[1] = Divide(v, mid + 1, r);
			p->PushUp(); // 自底向上维护，先维护子树 
			return p;
		}
		void Rebuild(Node * &p) {
			static vector<Node *>v; v.clear();
			Travel(p, v); p = Divide(v, 0, v.size());
		}
		Node ** Insert(Node *&p, int val) {
			if (p == null) {
				p = NewNode(val);
				return &null;
			}
			else {
				p->size++; p->cover++;
				
				// 返回值储存需要重构的位置，若子树也需要重构，本节点开始也需要重构，以本节点为根重构 
				Node ** res = Insert(p->ch[val >= p->key], val);
				if (p->isBad()) res = &p;
				return res;
			}
		}
		void Erase(Node *p, int id) {
			p->size--;
			int offset = p->ch[0]->size + p->exist;
			if (p->exist && id == offset) {
				p->exist = false;
				return;
			}
			else {
				if (id <= offset) Erase(p->ch[0], id);
				else Erase(p->ch[1], id - offset);
			}
		}
	public:
		void Init(void) {
			tail = mem_poor;
			null = tail++;
			null->ch[0] = null->ch[1] = null;
			null->cover = null->size = null->key = 0;
			root = null; bc_top = 0;
		}
		STree(void) { Init(); }

		void Insert(int val) {
			Node ** p = Insert(root, val);
			if (*p != null) Rebuild(*p);
		}
		int Rank(int val) {
			Node * now = root;
			int ans = 1;
			while (now != null) { // 非递归求排名 
				if (now->key >= val) now = now->ch[0];
				else {
					ans += now->ch[0]->size + now->exist;
					now = now->ch[1];
				}
			}
			return ans;
		}
		int Kth(int k) {
			Node * now = root;
			while (now != null) { // 非递归求第K大 
				if (now->ch[0]->size + 1 == k && now->exist) return now->key;
				else if (now->ch[0]->size >= k) now = now->ch[0];
				else k -= now->ch[0]->size + now->exist, now = now->ch[1];
			}
		}
		void Erase(int k) {
			Erase(root, Rank(k));
			if (root->size < alpha * root->cover) Rebuild(root);
		}
		void Erase_kth(int k) {
			Erase(root, k);
			if (root->size < alpha * root->cover) Rebuild(root);
		}
	};
#undef MAXN

}