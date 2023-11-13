#include "Stack.hpp"

int main() {
    // 输出：
    // 判断为空：
    // 1
    // 输出栈中元素：
    // 1 2 3 
    // 输出栈顶元素：
    // 3
    // 判断不为空：
    // 0
    // pop 栈顶：
    // 1 2 
    // 获得当前长度：
    // 2
    Stack<int> s;
    // std::cout << "空的时候 pop：" << std::endl;
    // std::cout << s.pop() << std::endl;
    std::cout << "判断为空：" << std::endl; 
    std::cout << s.empty() << std::endl;
    std::cout << "输出栈中元素：" << std::endl;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << s << std::endl;
    std::cout << "输出栈顶元素：" << std::endl;
    std::cout << s.top() << std::endl;
    std::cout << "判断不为空：" << std::endl;
    std::cout << s.empty() << std::endl;
    std::cout << "pop 栈顶：" << std::endl;
    s.pop();
    std::cout << s << std::endl;
    std::cout << "获得当前长度：" << std::endl;
    std::cout << s.size() << std::endl;
    return 0;
}