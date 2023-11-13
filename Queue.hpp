#include "LinkList.hpp"

template<class T>
class Queue {
    private:
        LinkList<T> list;
    public:
        void enqueue(T d);
        void dequeue();
        bool empty() const;
        int size() const;
        T first() const;
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const Queue<U>& q);
};  

template<class T>
void Queue<T>::enqueue(T d) {
    list.append(d);
}

template<class T>
void Queue<T>::dequeue() {
    if (empty()) {
        throw std::runtime_error("Queue is empty.");
    }
    list.remove(1);
}

template<class T>
bool Queue<T>::empty() const {
    return size() == 0;
}

template<class T>
int Queue<T>::size() const {
    return list.getLength();
}

template<class T>
T Queue<T>::first() const {
    return list.get(1);
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q) {
    os << q.list;
    return os;
}