#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include "./AVLTree.hpp"


template<class K, class V>
class MapIterator {
    public:
        AVLTreeNode<K, V>* current;
        // 构造函数
        MapIterator(AVLTreeNode<K, V>* node) : current(node) {}

        // 前向迭代
        MapIterator& operator++() {
            if (current == nullptr) {
                return *this;
            }
            if (current->rightChild) {
                current = current->rightChild;
                while (current->leftChild) {
                    current = current->leftChild;
                }
            } else {
                AVLTreeNode<K, V>* parent = current->parent;
                while (parent != nullptr && current == parent->rightChild) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return *this;
        }


        // 后向迭代
        MapIterator& operator--() {
            // 实现后向遍历逻辑
            // 更新current指针
            // 返回当前迭代器
            return *this;
        }

        // 获取当前元素
        std::pair<K, V>& operator*() {
            return current->value;
        }
        bool operator==(const MapIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const MapIterator& other) const {
            return !(*this == other);
        }
};

template<class K, class V>
class Map {
    public: 
        std::function<int(const std::pair<K, V>&, const std::pair<K, V>&)> compare;
        Tree<K, V> tree;
        Map(std::function<int(const std::pair<K, V>&, const std::pair<K, V>&)> comp) {
            tree.compare = comp;
            tree.root = nullptr;
        }
        Map() {
            tree.root = nullptr;
        }
        void insert(std::pair<K, V> val);
        void remove(K key);
        V find(K key) const;
        bool contain(K key) const;
        int size() const;
        MapIterator<K, V> begin() {
            AVLTreeNode<K, V>* current = tree.root;
            while (current && current->leftChild) {
                current = current->leftChild;
            }
            return MapIterator<K, V>(current);
        }
        MapIterator<K, V> end() {
            return MapIterator<K, V>(nullptr);
        }
};

template<class K, class V>
void Map<K, V>::insert(std::pair<K, V> val) {
    tree.insert(val);
}

template<class K, class V>
void Map<K, V>::remove(K key) {
    std::pair<K, V> cur(key, V{});
    tree.remove(cur);
}

template<class K, class V>
V Map<K, V>::find(K key) const {
    return tree.find(key).second;
}

template<class K, class V>
bool Map<K, V>::contain(K key) const {
    return tree.contain(std::pair<K, V>(key, V{}));
}

template<class K, class V>
int Map<K, V>::size() const {
    return tree.root ? tree.root->getSize() : 0;
}

#endif
