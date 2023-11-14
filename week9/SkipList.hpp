#include <vector>
#include <iostream>

class SkipListNode {
    public:
        int value;
        std::vector<SkipListNode*> nxt;
        SkipListNode(int val, int level)
            : value(val)
            , nxt(level, nullptr) {}
};

class Skiplist {
public:
    int maxLevel = 32;
    int level;
    SkipListNode* head;
    Skiplist() {
        level = 1;
        head = new SkipListNode(0, maxLevel);
    }
    int randomLevel() {
        int level = 1;
        while (level < maxLevel && (rand() % 2 == 0)) {
            level++;
        }
        return level;
    }
    bool search(int target) {
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < target) {
                current = current->nxt[i];
            }
        }
        if (current && current->nxt[0] && current->nxt[0]->value == target) {
            return true;
        }
        return false;
    }
    
    void add(int num) {
        std::vector<SkipListNode*> update(maxLevel, nullptr);
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < num) {
                current = current->nxt[i];
            }
            update[i] = current;
        }
        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level; i < newLevel; ++i) {
                update[i] = head;
            }
            level = newLevel;
        }
        SkipListNode* newNode = new SkipListNode(num, newLevel);
        for (int i = 0; i < newLevel; ++i) {
            newNode->nxt[i] = update[i]->nxt[i];
            update[i]->nxt[i] = newNode;
        }
    }
    
    bool erase(int num) {
        SkipListNode* current = head;
        std::vector<SkipListNode*> update(maxLevel, nullptr);
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < num) {
                current = current->nxt[i];
            }
            update[i] = current;
        }
        if (!current || !current->nxt[0] || current->nxt[0]->value != num) {
            return false;
        }
        if (current->nxt[0] && current->nxt[0]->value == num) {
            SkipListNode* toRemove = current->nxt[0];
            for (int i = 0; i < level; ++i) {
                if (update[i]->nxt[i] != toRemove) { // 不能直接判断 value 因为可能出现多个相同数值的情况
                    break;
                }
                update[i]->nxt[i] = toRemove->nxt[i];
            }
            delete toRemove;
        }   
        // 更新 level
        while (level > 1 && head->nxt[level - 1] == nullptr)
            level--;
        return true;
    }
};
