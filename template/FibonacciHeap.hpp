#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

template<class T>
class FibonacciHeapNode {
    public:
        T value;
        int degree;
        bool marked;
        FibonacciHeapNode<T>* parent;
        FibonacciHeapNode<T>* child;
        FibonacciHeapNode<T>* nxt;
        FibonacciHeapNode<T>* prev;
        FibonacciHeapNode(T val)
            : value(val)
            , degree(0)
            , marked(false)
            , parent(nullptr)
            , child(nullptr)
            , nxt(this)
            , prev(this) {}
};

template<class T>
class FibonacciHeap {
    public:
        FibonacciHeapNode<T>* minNode; 
        // 外部访问接口
        void insert(T);
        void pop();
        T top();
        bool empty() const ;
        FibonacciHeapNode<T>* extractMin();
        void merge(FibonacciHeap<T>&);
        void remove(FibonacciHeapNode<T>*);
        bool contain(T key);
        void update(FibonacciHeapNode<T>*, int);
        FibonacciHeap()
            : minNode(nullptr)
            , size(0)
            , maxDegree(0) {}
    private: // 内部实现细节函数
        int size;
        int maxDegree;
        void insertNode(FibonacciHeapNode<T>*);
        void consolidate();
        void cutNode(FibonacciHeapNode<T>*, FibonacciHeapNode<T>*);
        void cascading(FibonacciHeapNode<T>*);
        FibonacciHeapNode<T>* search(FibonacciHeapNode<T>*, T);
        void decrease(FibonacciHeapNode<T>*, int);
        void increase(FibonacciHeapNode<T>*, int);
        
        void listLink(FibonacciHeapNode<T>*);
        void listAdd(FibonacciHeapNode<T>*);
        void listRemove(FibonacciHeapNode<T>*);
};

template<class T>
bool FibonacciHeap<T>::empty() const {
    return size == 0;
}

template<class T>
T FibonacciHeap<T>::top() {
    return minNode->value;
}

template<class T>
void FibonacciHeap<T>::insert(T value) {
    insertNode(new FibonacciHeapNode<T>(value));
}

template<class T>
void FibonacciHeap<T>::insertNode(FibonacciHeapNode<T>* newNode) {
    if (!minNode) {
        size = 1;
        minNode = newNode;
        minNode->prev = minNode;
        minNode->nxt = minNode;
        return ;
    }
    listAdd(newNode);
    if (newNode->value < minNode->value)
        minNode = newNode;
    size += 1;
}

template<class T>   
void FibonacciHeap<T>::consolidate() {
    int maxDegreePossible = static_cast<int>(log2(size)) + 1;
    std::vector<FibonacciHeapNode<T>*> degreeTable(maxDegreePossible, nullptr);
    std::vector<FibonacciHeapNode<T>*> preparedNodes;
    FibonacciHeapNode<T>* cur = minNode;
    do {
        preparedNodes.push_back(cur);
        cur = cur->nxt;
    } while (cur != minNode);
    // std::cout << preparedNodes.size() << "\n";
    for (FibonacciHeapNode<T>*& node : preparedNodes) {
        int degree = node->degree;
        // std::cout << " adasd" << degree << "\n";
        while (degreeTable[degree] != nullptr) {
            // std::cout << "1323";
            FibonacciHeapNode<T>* other = degreeTable[degree];
            if (other->value < node->value) {
                FibonacciHeapNode<T>* temp = other;
                other = node;
                node = temp;
            }
            nodeAdd(other, node);
            // list
            degreeTable[degree] = nullptr;
            ++degree;
        }
        degreeTable[degree] = node;
    }
    minNode = nullptr;
    for (int i = 0; i < maxDegreePossible; ++i) {
        if (!degreeTable[i]) continue;
        if (!minNode) {
            minNode = degreeTable[i];
            minNode->nxt = minNode;
            minNode->prev = minNode;
            // minNode->degree = 0;
        } else {
            insertNode(degreeTable[i]);
        }
    }
}   

template<class T>
void FibonacciHeap<T>::cutNode(FibonacciHeapNode<T>* cur, FibonacciHeapNode<T>* parent) {
    listRemove(cur);
    cur->parent->degree -= 1;
    if (cur == cur->nxt) {
        parent->child = nullptr;
    } else {
        parent->child = cur->nxt;
    }
    cur->parent = nullptr;
    cur->prev = cur->nxt = cur;
    cur->marked = 0;
    listAdd(cur);
}

template<class T>
void FibonacciHeap<T>::cascading(FibonacciHeapNode<T>* cur) {
    FibonacciHeapNode<T>* parent = cur->parent;
    if (parent != nullptr)
        return ;
    if (cur->marked == 0)
        cur->marked = 1;
    else {
        cutNode(cur, parent);
        cascading(parent);
    }
}

template<class T>
FibonacciHeapNode<T>* FibonacciHeap<T>::search(FibonacciHeapNode<T>* cur, T value) {
    FibonacciHeapNode<T>* root = cur;
    FibonacciHeapNode<T>* ans = nullptr;
    if (minNode == nullptr || cur == nullptr) {
        return nullptr;
    }
    do {
        if (root->value == value) return root;
        else {
            if ((ans = search(root->child, value)) != nullptr) break;
        }
        root = root->nxt;
    } while (root != minNode);
    return ans;
} // 感觉这个 search 复杂度好高，好像不是 线性 的

template<class T>
bool FibonacciHeap<T>::contain(T key) {
    return search(minNode, key) != nullptr;
}

template<class T>
void FibonacciHeap<T>::update(FibonacciHeapNode<T>* cur, int key) {
    if (key > 0) increase(cur, key);
    else decrease(cur, -key);
}

template<class T>
void FibonacciHeap<T>::pop() {
    extractMin();
}

template<class T>
FibonacciHeapNode<T>* FibonacciHeap<T>::extractMin() {
    if (!minNode) {
        throw std::runtime_error("The heap is empty!");
        return nullptr;
    }
    while (minNode->child) {
        FibonacciHeapNode<T>* child = minNode->child;
        minNode->child = child->nxt;
        if (minNode->child == child)
            minNode->child = nullptr;
        listRemove(child);
        listAdd(child);
        child->parent = nullptr;
    }
    minNode->degree = 0;
    listRemove(minNode);
    FibonacciHeapNode<T>* temp = minNode;
    if (minNode->nxt == minNode) {
        minNode = nullptr;
    } else {
        minNode = minNode->nxt;
        consolidate();
    }
    size -= 1;
    return temp; // 注意这里返回 temp
}

template<class T>
void FibonacciHeap<T>::merge(FibonacciHeap<T>& h) {
    if (!h.minNode) return;
    listLink(h.minNode);
    if (minNode->value > h.minNode->value)
        minNode = h.minNode;
    size += h.size;
}

// template<class T>
// void FibonacciHeap<T>::update(FibonacciHeapNode<T>* cur, int key) {
//     if (key == 0) return ;
//     else if (key < 0) decrease(cur, -key);
//     else cur->value += key;
// }

template<class T>
void FibonacciHeap<T>::decrease(FibonacciHeapNode<T>* cur, int key) {
    FibonacciHeapNode<T>* parent;
    if (minNode == nullptr || cur == nullptr || cur->value < key) {
        throw std::runtime_error("illegal decreasing!");
    }
    cur->value -= key;
    parent = cur->parent;
    if (parent != nullptr && cur->value < parent->value) {
        cutNode(cur, parent);
        cascading(parent);
    }
    if (cur->value < minNode->value) {
        minNode = cur;
    }
}

template<class T>
void FibonacciHeap<T>::increase(FibonacciHeapNode<T>* cur, int key) {
    FibonacciHeapNode<T>* child;
    FibonacciHeapNode<T>* right;
    FibonacciHeapNode<T>* parent;
    if (cur == nullptr || minNode == nullptr || key < 0) {
        throw std::runtime_error("illegal increasing!");
    }
    while (cur->child != nullptr) {
        child = cur->child;
        listRemove(child);
        if (child->nxt == child)
            cur->child = nullptr;
        else {
            cur->child = child->nxt;
        }
        listAdd(child);
        child->parent = nullptr;
    }
    cur->degree = 0;
    cur->value += key; // 感觉可以改成 cutNode
    parent = cur->parent;
    if (parent != nullptr) {
        cutNode(cur, parent);
        cascading(parent);
    } else if (minNode == cur) {
        right = cur->nxt;
        while (right != cur) {
            if (minNode->value > right->value)
                minNode = right;
            right = right->nxt;
        }
    }
}

template<class T>
void FibonacciHeap<T>::remove(FibonacciHeapNode<T>* cur) {
    decrease(cur, -1000000);
    extractMin();
}

template<class T>
void FibonacciHeap<T>::listLink(FibonacciHeapNode<T>* p2) {
    FibonacciHeapNode<T>* p1 = minNode;
    FibonacciHeapNode<T>* temp = p2->prev;
    p2->prev = p1->prev;
    p1->prev->nxt = p2;
    p1->prev = temp;
    temp->nxt = p1;
}

template<class T>
void FibonacciHeap<T>::listAdd(FibonacciHeapNode<T>* newNode) {
    newNode->prev = minNode->prev;
    newNode->nxt = minNode;
    minNode->prev->nxt = newNode;
    minNode->prev = newNode;
}

template<class T>
void FibonacciHeap<T>::listRemove(FibonacciHeapNode<T>* removeNode) {
    removeNode->prev->nxt = removeNode->nxt;
    removeNode->nxt->prev = removeNode->prev;
}

template<class T>
void nodeAdd(FibonacciHeapNode<T>* p1, FibonacciHeapNode<T>* p2) {
    p1->parent = p2;
    if (!p2->child) {
        p2->child = p1;
        p1->nxt = p1;
        p1->prev = p1;
    } else {
        p1->nxt = p2->child->nxt;
        p1->prev = p2->child;
        p2->child->nxt = p1;
        p1->nxt->prev = p1;
    }
    p2->degree += 1;
    p1->marked = false;
}

#endif