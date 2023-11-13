#include "LinkList.hpp"

template<class T>
class Stack {
    private:
        LinkList<T> list;
    public:
        Stack() {}
        void push(T d);
        T pop();
        T top() const;
        T get(int index) const;
        int size() const;
        bool empty() const;
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);
};

template<class T>
void Stack<T>::push(T d) {
    list.append(d);
}

template<class T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    int length = list.getLength();
    T ans = list.get(length);
    list.remove(length);
    return ans;
}

template<class T>
T Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    int length = list.getLength();
    return list.get(length);
}

template<class T>
T Stack<T>::get(int index) const {
    return list.get(index);
}

template<class T>
int Stack<T>::size() const {
    return list.getLength();
}

template<class T>
bool Stack<T>::empty() const {
    return list.getLength() == 0;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    os << stack.list;
    return os;
}