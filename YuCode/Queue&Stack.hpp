#include "./LinkedList.hpp"

template<typename T>
class Deque : public LinkedList<T> {
    public:
        void pushFront(T x) {
            this->addFirst(x);
        }

        void pushBack(T x) {
            this->addLast(x);
        }

        T& popBack() {
            return this->removeLast();
        }

        T& popFront() {
            return this->removeFirst();
        }

        T& front() {
            return this->getFirst();
        }

        T& back() {
            return this->getLast();
        }
};

template<typename T>
class Queue : public Deque<T> {
    public:
        void push(T x) {
            this->pushBack(x);
        }

        T& pop() {
            return this->popFront();
        }
};

template<typename T>
class Stack : public Deque<T> {
    public:
        void push(T x) {
            this->pushFront(x);
        }

        T& pop() {
            return this->popFront();
        }

        T& top() {
            return this->front();
        }
};