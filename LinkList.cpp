#include "LinkList.hpp"
#include <iostream>

int main() {
    // 输出：
    // 向链表末尾添加元素：
    // 0 2 1 5 
    // 按 data 查找元素：
    // 5
    // 按 data 查找不存在元素
    // 0
    // 按 data 删除元素：
    // 0 1 5 
    // 按 data 删除不存在元素：
    // 按 索引（位置） 删除元素：
    // 0 5 
    // 按 非法索引 删除元素：
    // 0 5 
    // 中间 insert：
    // 0 2 5 
    // 最后 insert：
    // 0 2 5 7 
    // 非法 insert：
    // 0 2 5 7 
    LinkList<int> myList;
    // std::cout << myList.getLength() << std::endl;
    std::cout << "向链表末尾添加元素：" << std::endl;
    myList.append(0);
    myList.append(2);
    myList.append(1);
    myList.append(5);
    std::cout << myList << std::endl;

    std::cout << "按 data 查找元素：" << std::endl;
    std::cout << myList.find(5)->data << std::endl;

    std::cout << "按 data 查找不存在元素" << std::endl;
    std::cout << myList.find(10) << std::endl;

    std::cout << "按 data 删除元素：" << std::endl;
    myList.del(2);
    std::cout << myList << std::endl;

    std::cout << "按 data 删除不存在元素：" << std::endl;
    myList.del(10);

    std::cout << "按 索引（位置） 删除元素：" << std::endl;
    myList.remove(2);
    std::cout << myList << std::endl;

    std::cout << "按 非法索引 删除元素：" << std::endl;
    myList.remove(10);
    std::cout << myList << std::endl;

    std::cout << "中间 insert：" << std::endl; 
    myList.insert(1, 2);
    std::cout << myList << std::endl;

    std::cout << "最后 insert：" << std::endl;
    myList.insert(3, 7);
    std::cout << myList << std::endl;

    std::cout << "非法 insert：" << std::endl;
    myList.insert(5, 10);
    std::cout << myList << std::endl;
    
    LinkList<char> my;
    my.append('c');
    std::cout << my << std::endl;
    return 0;
}

