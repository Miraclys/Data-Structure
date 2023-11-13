#include <bits/stdc++.h>
using namespace std;

template <class T>
class LinkList;

template <typename T>
class Node {
    private:
        T data;
        Node* nxt;
    public:
        Node() {
            nxt = NULL;
        }
        Node(T d) : data(d), nxt(NULL) {
        }
    friend class LinkList<T>;
};

template <typename T>
class LinkList {
    private:
        Node<T>* head;
        int length;
    public:
        LinkList() : length(0) {
            head = new Node<T>();
        }
        void append(T d) {
            Node<T>* cur = head;
            while (cur->nxt != NULL) cur = cur->nxt;
            Node<T>* newData = new Node(d);
            cur->nxt = newData;
            ++length;
        }
        void insertHead(T d) {
            Node<T>* newData = new Node<T>(d);
            newData->nxt = head->nxt;
            head->nxt = newData;
            ++length;
        }
        Node<T>* find(T d) {
            Node<T>* cur = head;
            while (cur->nxt != NULL) {
                if (cur->nxt->data == d) return cur; 
                cur = cur->nxt;
            }
            return NULL;
        }
        void remove(T d) {
            Node<T>* cur = find(d);
            if (cur == NULL) return ;
            Node<T>* removeData = cur->nxt;
            cur->nxt = removeData->nxt;
            delete removeData;
            --length;
        }
        int getLength() {
            return length;
        }
        void printList() {
            Node<T>* cur = head->nxt;
            while (cur != NULL) {
                cout << cur->data << " ";
                cur = cur->nxt;
            }
            cout << endl;
        }
};

int main() {
    LinkList<int> l;
    l.append(1);
    l.append(2);
    l.append(3);
    l.printList();
    l.remove(1);
    l.printList();
    l.insertHead(1);
    l.printList();
    // 输出：
    // 1 2 3
    // 2 3
    // 1 2 3
    LinkList<char> r;
    r.append('a');
    r.append('b');
    r.append('c');
    r.printList();
    r.remove('a');
    r.printList();
    r.insertHead('a');
    r.printList();
    // 输出：
    // a b c
    // b c
    // a b c
    return 0;
}