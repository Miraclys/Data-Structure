#include <iostream>
#include <functional>
#include <utility>
#include <algorithm>
#include <string>
#include <cstring>
#include "../AVLTree.hpp"

int main() {
    auto compare = [](const std::pair<int, std::string>& x, const std::pair<int, std::string>& y) {
        if (x.first < y.first) return -1;
        else if (x.first == y.first) return 0;
        else return 1;
    };
    Tree<int, std::string> t(compare);
    t.insert(std::pair<int, std::string>(1, "abc"));
    t.insert(std::pair<int, std::string>(2, "111"));
    std::cout << t.getRank(std::pair<int, std::string>(2, "")) << "\n";
    t.remove(std::pair<int, std::string>(1, "abc"));
    std::cout << t.getRank(std::pair<int, std::string>(0, "")) << "\n";

    return 0;
}
