#ifndef LINKLIST_HPP
#define LINKLIST_HPP

#include <iostream>

template<class T>
class LinkList {
    private:
        class Node {
            public:
                T data;
                Node* nxt;
                Node(T d): data(d), nxt(NULL) {
                }
                Node(): nxt(NULL) {}
        };
        Node* head;
    public:
        LinkList() {
            head = new Node();
        }
        ~LinkList();
        int getLength() const;
        Node* find(T d) const;
        T get(int postion) const;
        void append(T d);
        void del(T d);
        void insert(int position, T d);
        void remove(int position);
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const LinkList<U>& list);
};
    
template<class T>
LinkList<T>::~LinkList() {
    while (head) {
        Node* cur = head;
        head = head->nxt;
        delete cur;
    }
}

template<class T> 
int LinkList<T>::getLength() const {
    int length = 0;
    Node* cur = head;
    while (cur->nxt) {
        ++length;
        cur = cur->nxt;
    }
    return length;
}

template<class T>
typename LinkList<T>::Node* LinkList<T>::find(T d) const {
    Node* cur = head;
    while (cur->nxt != NULL) {
        if (cur->nxt->data == d) return cur->nxt;
        cur = cur->nxt;
    }   
    return NULL;
}

template<class T> 
T LinkList<T>::get(int position) const {
    if (position <= 0 || position > getLength()) {
        throw std::runtime_error("The position is not legal.");
    }
    Node* cur = head;
    while (position) {
        cur = cur->nxt;
        --position;
    }
    return cur->data;
}

template<class T>
void LinkList<T>::append(T d) {
    Node* newData = new Node(d);
    Node* cur = head;
    while (cur->nxt != NULL) {
        cur = cur->nxt;
    }
    cur->nxt = newData;
}

template<class T>
void LinkList<T>::del(T d) {
    Node* cur = head;
    while (cur->nxt) {
        if (cur->nxt->data == d) break;
        cur = cur->nxt;
    }
    if (cur->nxt == NULL) return ;
    Node* target = cur->nxt->nxt;
    delete cur->nxt;
    cur->nxt = target;
}

template<class T>
void LinkList<T>::insert(int position, T d) {
    if (position < 0 || position > getLength()) return ;
    Node* cur = head;
    while (position) {
        cur = cur->nxt;
        --position;
    }
    Node* newData = new Node(d);
    Node* target = cur->nxt;
    cur->nxt = newData;
    newData->nxt = target;
}

template<class T>
void LinkList<T>::remove(int position) {
    Node* cur = head;
    
    if (position <= 0 || position > getLength()) return ;
    position--;
    while (position) {
        cur = cur->nxt;
        --position;
    }
    if (position == 0) {
        Node* newData = cur->nxt;
        cur->nxt = newData->nxt;
        delete newData;
    }
}

template<class T>
std::ostream &operator<<(std::ostream &os, const LinkList<T> &list) {
    typename LinkList<T>::Node* cur = list.head->nxt;
    while (cur) {
        os << cur->data << " ";
        cur = cur->nxt;
    }
    return os;
}

#endif