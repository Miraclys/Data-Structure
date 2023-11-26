#include <iostream>
#include <cmath>

template <typename T>
class ScapegoatTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;
    int maxSize;

    static const double ALPHA;  // 定义平衡系数

    Node* buildFromArray(const T arr[], int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = start + (end - start) / 2;
        Node* newNode = new Node(arr[mid]);
        newNode->left = buildFromArray(arr, start, mid - 1);
        newNode->right = buildFromArray(arr, mid + 1, end);
        return newNode;
    }

    void deleteSubtree(Node* node) {
        if (node != nullptr) {
            deleteSubtree(node->left);
            deleteSubtree(node->right);
            delete node;
        }
    }

    int getHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    void flatten(Node* node, T arr[], int& index) const {
        if (node != nullptr) {
            flatten(node->left, arr, index);
            arr[index++] = node->data;
            flatten(node->right, arr, index);
        }
    }

    Node* buildBalancedFromArray(const T arr[], int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = start + (end - start) / 2;
        Node* newNode = new Node(arr[mid]);
        newNode->left = buildBalancedFromArray(arr, start, mid - 1);
        newNode->right = buildBalancedFromArray(arr, mid + 1, end);
        return newNode;
    }

    void rebuildTree(Node*& node, const T arr[], int start, int end) {
        int size = end - start + 1;
        T* tempArray = new T[size];
        int index = 0;
        flatten(node, tempArray, index);
        deleteSubtree(node);
        node = buildBalancedFromArray(tempArray, 0, size - 1);
        delete[] tempArray;
    }

    bool isBalanced(Node* node) const {
        if (node == nullptr) {
            return true;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return std::abs(leftHeight - rightHeight) <= ALPHA * std::max(leftHeight, rightHeight);
    }

    bool contains(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }

        if (value < node->data) {
            return contains(node->left, value);
        } else if (value > node->data) {
            return contains(node->right, value);
        } else {
            return true;
        }
    }

    void insert(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node(value);
            ++size;
            if (size > maxSize) {
                rebuildTree(root, toArray(), 0, size - 1);
                maxSize = size;
            }
        } else if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }
    }

public:
    ScapegoatTree() : root(nullptr), size(0), maxSize(0) {}

    explicit ScapegoatTree(const T arr[], int size) : size(size), maxSize(size) {
        root = buildFromArray(arr, 0, size - 1);
    }

    ~ScapegoatTree() {
        deleteSubtree(root);
    }

    void insert(const T& value) {
        insert(root, value);
    }

    bool contains(const T& value) const {
        return contains(root, value);
    }

    T* toArray() const {
        T* arr = new T[size];
        int index = 0;
        flatten(root, arr, index);
        return arr;
    }
};

template <typename T>
const double ScapegoatTree<T>::ALPHA = 0.7;

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    ScapegoatTree<int> tree(arr, size);

    // Example usage
    tree.insert(8);
    tree.insert(7);

    std::cout << "Contains 6: " << (tree.contains(6) ? "true" : "false") << std::endl;
    std::cout << "Contains 10: " << (tree.contains(10) ? "true" : "false") << std::endl;

    return 0;
}
