#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
class Heap {
    public:
        std::vector<T> heap; // 堆 的特殊性质所以我们可以使用 vector 来模拟
        std::function<bool(const T&, const T&)> compare;
        void heapUp(int index);
        void heapDown(int index);
        bool empty() const;
        void insert(T element);
        T get(int index) const;
        T top() const;
        void pop();
        int size() const;
        void decreaseValue(int, int);
        Heap() {}
        Heap(std::function<bool(const T&, const T&)> comp) : compare(comp) {}
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, Heap<U>& cur) {
            for (const auto& element : cur.heap) {
                os << element << " ";
            }
            return os;
        }
};

template<class T>
void Heap<T>::heapUp(int index) {
    while (index > 0) {
        int parent = (index - 1) >> 1;
        if (compare(heap[index], heap[parent])) { // 返回 true 表示应该交换
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

template<class T>
void Heap<T>::heapDown(int index) {
    while (true) {
        int leftChild = (index << 1) + 1;
        int rightChild = (index << 1) + 2;
        int smallestIndex = index;

        if (leftChild < heap.size() && compare(heap[leftChild], heap[smallestIndex])) { // 返回 true 表示应该交换
            smallestIndex = leftChild;
        }

        if (rightChild < heap.size() && compare(heap[rightChild], heap[smallestIndex])) { // 返回 true 表示应该交换
            smallestIndex = rightChild;
        }

        if (smallestIndex != index) {
            std::swap(heap[index], heap[smallestIndex]);
            index = smallestIndex;
        } else {
            break;
        }
    }
}

template<class T>
bool Heap<T>::empty() const {
    return heap.size() == 0;
}

template<class T>
void Heap<T>::insert(T element) {
    heap.push_back(element);
    heapUp(heap.size() - 1);
}

template<class T>
T Heap<T>::get(int index) const {
    if (index < 0 || index > heap.size() - 1) {
        throw std::runtime_error("this index is illegal.");
    }
    return heap[index];
}

template<class T>
T Heap<T>::top() const {
    if (!heap.size()) {
        throw std::runtime_error("this heap is empty.");
    }
    return heap[0];
}

template<class T>
void Heap<T>::pop() {
    if (!heap.size()) {
        throw std::runtime_error("this heap is empty.");
    }
    heap[0] = heap.back();
    heap.pop_back();
    heapDown(0);
}

template<class T>
int Heap<T>::size() const {
    return heap.size();
}

template<class T>
void Heap<T>::decreaseValue(int index, int value) {
    if (index < 0 || index > heap.size() - 1) {
        throw std::runtime_error("this index is illegal.");
    }
    heap[index] -= value;
    heapUp(index);
}

#endif