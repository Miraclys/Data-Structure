#include <cstdlib>
#include <ctime>

const int MAX_LEVEL = 16;

struct Node {
    int value;
    Node* next;
    Node* up[MAX_LEVEL];
    Node(int v = 0, int level = MAX_LEVEL) : value(v), next(nullptr) {
        for (int i = 0; i < level; ++i) {
            up[i] = nullptr;
        }
    }
};

class Skiplist {
public:
    Skiplist() : head(new Node()), tail(nullptr), level(1) {
        std::srand(std::time(nullptr));
        for (int i = 0; i < MAX_LEVEL; ++i) {
            head->up[i] = nullptr;
        }
    }

    ~Skiplist() {
        Node* p = head;
        while (p) {
            Node* q = p->next;
            delete p;
            p = q;
        }
    }

    Node* find(int value) const {
        Node* p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->up[i] && p->up[i]->value < value) {
                p = p->up[i];
            }
        }
        p = p->next;
        if (p && p->value == value) {
            return p;
        } else {
            return nullptr;
        }
    }

    Node* insert(int value) {
        Node* p = head;
        Node* q = nullptr;
        Node* newNode = nullptr;
        int newLevel = 1;
        while (std::rand() % 2 && newLevel < MAX_LEVEL) {
            ++newLevel;
        }
        newNode = new Node(value, newLevel);
        for (int i = level - 1; i >= 0; --i) {
            while (p->up[i] && p->up[i]->value < value) {
                p = p->up[i];
            }
            if (i < newLevel) {
                q = new Node(value);
                q->next = p->next;
                p->next = q;
                q->up[i] = newNode;
                newNode->up[i] = q;
            }
        }
        if (newLevel > level) {
            tail = newNode;
            level = newLevel;
        }
        return newNode;
    }

    bool remove(int value) {
        Node* p = head;
        Node* q = nullptr;
        bool found = false;
        for (int i = level - 1; i >= 0; --i) {
            while (p->up[i] && p->up[i]->value < value) {
                p = p->up[i];
            }
            if (p->next && p->next->value == value) {
                found = true;
                q = p->next;
                p->next = q->next;
                delete q;
            }
        }
        return found;
    }

    int getRank(int value) const {
        int rank = 0;
        Node* p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->up[i] && p->up[i]->value < value) {
                rank += (1 << i);
                p = p->up[i];
            }
        }
        p = p->next;
        while (p && p->value <= value) {
            if (p->value == value) {
                ++rank;
                break;
            } else {
                ++rank;
                p = p->next;
            }
        }
        return rank;
    }

private:
    Node* head;
    Node* tail;
    int level;
};
