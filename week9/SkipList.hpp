<<<<<<< HEAD
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
=======
#include <vector>
#include <iostream>

class SkipListNode {
    public:
        int value;
        int span[1005];
        std::vector<SkipListNode*> nxt;
        SkipListNode(int val, int level)
            : value(val)
            , nxt(level, nullptr) {
                for (int i = 0; i < level; ++i) {
                    span[i] = 1;
                }
            }
};

class SkipList {
public:
    int maxLevel = 32;
    int level;
    int length;
    SkipListNode* head;
    SkipList() {
        level = 1;
        head = new SkipListNode(0, maxLevel);
        length = 0;
    }
    int randomLevel() {
        int level = 1;
        while (level < maxLevel && (rand() % 2 == 0)) {
            level++;
        }
        return level;
    }
    void print() {
        for (int i = level - 1; i >= 0; --i) {
            std::cout << head->value << " ";
            SkipListNode* current = head->nxt[i];
            while (current) {
                std::cout << current->value << " ";
                current = current->nxt[i];
            }
            std::cout << "\n";
        }
    }
    int getRank(int value) {
        int rank = 0;
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < value) {
                rank += current->nxt[i]->span[i];
                current = current->nxt[i];
            }
        }
        // std::cout << "0 : " << current->nxt[0]->value << ;
        if (current->nxt[0] && current->nxt[0]->value == value) {
            return rank + 1;
        }
        std::cerr << "illegal operation!" << "\n";
        throw std::runtime_error("illegal operation!");
    }
    int getValue(int rank) {
        if (rank > length) {
            std::cerr << "illegal rank!" << "\n";
            throw std::runtime_error("illegal rank!"); 
        }
        SkipListNode* current = head;
        for (int i = level - 1; i > 0; --i) {
            while (current->nxt[i] && rank > current->nxt[i]->span[i]) {
                rank -= current->nxt[i]->span[i];
                current = current->nxt[i];
            }
        }
        return current->nxt[0]->value;
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
    int getPre(int target) {
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < target) {
                current = current->nxt[i];
            }
        }
        return current->value;
        // std::cerr << "no precursor!" << "\n";
        // throw std::runtime_error("no precursor!");
    }
    int getSuf(int target) {
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            if (current->nxt[i] && current->nxt[i]->value < target) {
                current = current->nxt[i];
            }
        }
        if (current->nxt[0] && current->nxt[0]->value == target) {
            if (current->nxt[0]->nxt[0]) {
                return current->nxt[0]->nxt[0]->value;
            } else throw std::runtime_error("no successor!");
        } else if (current->nxt[0] && current->nxt[0]->value > target) {
            return current->nxt[0]->value;
        }
        throw std::runtime_error("no successor!");
        std::cerr << "no successor!" << "\n";
        throw std::runtime_error("no successor!");
    }
    void add(int num) {
        std::vector<SkipListNode*> update(maxLevel, nullptr);
        SkipListNode* current = head;
        int lst_pos[32];
        lst_pos[level] = 0;
        for (int i = level - 1; i >= 0; --i) {
            lst_pos[i] = lst_pos[i + 1];
            while (current->nxt[i] && current->nxt[i]->value < num) {
                lst_pos[i] += current->nxt[i]->span[i];
                current = current->nxt[i];
            }
            update[i] = current;
        }
        int newLevel = randomLevel();
        SkipListNode* curNode = new SkipListNode(num, newLevel);
        if (newLevel > level) {
            for (int i = level; i < newLevel; ++i) {
                update[i] = head;
                update[i]->nxt[i] = curNode;
                lst_pos[i] = 0;
            }
        }
        for (int i = 0; i < newLevel; ++i) {
            curNode->nxt[i] = update[i]->nxt[i];
            int temp;
            if (update[i]->nxt[i]) {
                curNode->nxt[i]->span[i] = update[i]->nxt[i]->span[i] - (lst_pos[0] - lst_pos[i]);
            }
            update[i]->nxt[i] = curNode;
            update[i]->nxt[i]->span[i] = lst_pos[0] - lst_pos[i] + 1;
        }
        for (int i = newLevel; i < level; ++i) {
            if (update[i]->nxt[i]) {
                ++update[i]->nxt[i]->span[i];
            }
        }
        ++length;
    }
    /*
    
    1 577793
1 408221
1 880861
2 880861
    */
    bool erase(int num) {
        // return 1;
        SkipListNode* current = head;
        std::vector<SkipListNode*> update(maxLevel, nullptr);
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < num) {
                current = current->nxt[i];
            }
            update[i] = current;
        }
        current = current->nxt[0];
        for (int i = 0; i < level; ++i) {
            if (update[i]->nxt[i] == current) {
                if (current->nxt[i]) {
                    update[i]->nxt[i]->span[i] += current->nxt[i]->span[i] - 1;
                }
                update[i]->nxt[i] = current->nxt[i];
            } else {
                if (update[i]->nxt[i]) {
                    --update[i]->nxt[i]->span[i];
                }
            }
        }
        while (level > 1 && !head->nxt[level - 1])
            --level;
        delete current;
        --length;
        return true;
        // if (!current || !current->nxt[0] || current->nxt[0]->value != num) {
        //     return false;
        // }
        // if (current->nxt[0] && current->nxt[0]->value == num) {
        //     SkipListNode* toRemove = current->nxt[0];
        //     for (int i = 0; i < level; ++i) {
        //         if (update[i]->nxt[i] != toRemove) { // 不能直接判断 value 因为可能出现多个相同数值的情况
        //             break;
        //         }
        //         update[i]->nxt[i] = toRemove->nxt[i];
        //     }
        //     delete toRemove;
        // }   
        // // 更新 level
        // while (level > 1 && head->nxt[level - 1] == nullptr)
        //     level--;
        // return true;
    }
};


/*

#include <vector>
#include <iostream>

class SkipListNode {
    public:
        int value;
        int span[1005];
        std::vector<SkipListNode*> nxt;
        SkipListNode(int val, int level)
            : value(val)
            , nxt(level, nullptr) {
                for (int i = 0; i < level; ++i) {
                    span[i] = 1;
                }
            }
};

class SkipList {
public:
    int maxLevel = 14;
    int level;
    int length;
    SkipListNode* head;
    SkipList() {
        level = 1;
        head = new SkipListNode(0, maxLevel);
        length = 0;
    }
    int randomLevel() {
        int level = 1;
        while (level < maxLevel && (rand() % 2 == 0)) {
            level++;
        }
        return level;
    }
    void print() {
        for (int i = level - 1; i >= 0; --i) {
            std::cout << head->value << " ";
            SkipListNode* current = head->nxt[i];
            while (current) {
                std::cout << current->value << " ";
                current = current->nxt[i];
            }
            std::cout << "\n";
        }
    }
    int getRank(int value) {
        int rank = 0;
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < value) {
                rank += current->nxt[i]->span[i];
                current = current->nxt[i];
            }
        }
        // std::cout << "0 : " << current->nxt[0]->value << ;
        // if (current->nxt[0] && current->nxt[0]->value == value) {
        //     return rank + 1;
        // }
        return rank + 1;
        std::cerr << "illegal operation!" << "\n";
        throw std::runtime_error("illegal operation!");
    }
    int getValue(int rank) {
        if (rank < 1 || rank > length) {
            std::cerr << "illegal rank!" << "\n";
            throw std::runtime_error("illegal rank!"); 
        }
        
        SkipListNode* current = head;
        int currentRank = 0;

        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && (currentRank + current->nxt[i]->span[i]) <= rank) {
                currentRank += current->nxt[i]->span[i];
                current = current->nxt[i];
            }
        }

        return current->value;
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
    int getPre(int target) {
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < target) {
                current = current->nxt[i];
            }
        }
        return current->value;
        std::cerr << "no precursor!" << "\n";
        throw std::runtime_error("no precursor!");
    }
    int getSuf(int target) {
        SkipListNode* current = head;
        for (int i = level - 1; i >= 0; --i) {
            while (current->nxt[i] && current->nxt[i]->value < target) {
                current = current->nxt[i];
            }
        }
        // if (current->nxt[0] && current->nxt[0]->value == target) {
        //     if (current->nxt[0]->nxt[0]) {
        //         return current->nxt[0]->nxt[0]->value;
        //     } else throw std::runtime_error("no successor!");
        // } else if (current->nxt[0] && current->nxt[0]->value > target) {
        //     return current->nxt[0]->value;
        // }
        if (current->nxt[0]->value > target) return current->nxt[0]->value;
        else return current->nxt[0]->nxt[0]->value;
        // throw std::runtime_error("no successor!");
        std::cerr << "no successor!" << "\n";
        throw std::runtime_error("no successor!");
    }
    void add(int num) {
        std::vector<SkipListNode*> update(maxLevel, nullptr);
        SkipListNode* current = head;
        int lst_pos[32];
        lst_pos[level] = 0;
        for (int i = level - 1; i >= 0; --i) {
            lst_pos[i] = lst_pos[i + 1];
            while (current->nxt[i] && current->nxt[i]->value < num) {
                lst_pos[i] += current->nxt[i]->span[i];
                current = current->nxt[i];
            }
            update[i] = current;
        }
        int newLevel = randomLevel();
        SkipListNode* curNode = new SkipListNode(num, newLevel);
        if (newLevel > level) {
            for (int i = level; i < newLevel; ++i) {
                update[i] = head;
                update[i]->nxt[i] = curNode;
                lst_pos[i] = 0;
            }
        }
        for (int i = 0; i < newLevel; ++i) {
            curNode->nxt[i] = update[i]->nxt[i];
            int temp;
            if (update[i]->nxt[i]) {
                curNode->nxt[i]->span[i] = update[i]->nxt[i]->span[i] - (lst_pos[0] - lst_pos[i]);
            }
            update[i]->nxt[i] = curNode;
            update[i]->nxt[i]->span[i] = lst_pos[0] - lst_pos[i] + 1;
        }
        for (int i = newLevel; i < level; ++i) {
            if (update[i]->nxt[i]) {
                ++update[i]->nxt[i]->span[i];
            }
        }
        ++length;
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
        current = current->nxt[0];
        // if (current->nxt[0] == nullptr) std::cout << "ada";
        for (int i = 0; i < level; ++i) {
            if (update[i]->nxt[i] == current) {
                if (current->nxt[i])
                    update[i]->nxt[i]->span[i] += current->nxt[i]->span[i] - 1;
                update[i]->nxt[i] = current->nxt[i];
            } else {
                --update[i]->nxt[i]->span[i];
            }
        }
        while (level > 1 && !head->nxt[level - 1])
            --level;
        delete current;
        --length;
        return true;
        // if (!current || !current->nxt[0] || current->nxt[0]->value != num) {
        //     return false;
        // }
        // if (current->nxt[0] && current->nxt[0]->value == num) {
        //     SkipListNode* toRemove = current->nxt[0];
        //     for (int i = 0; i < level; ++i) {
        //         if (update[i]->nxt[i] != toRemove) { // 不能直接判断 value 因为可能出现多个相同数值的情况
        //             break;
        //         }
        //         update[i]->nxt[i] = toRemove->nxt[i];
        //     }
        //     delete toRemove;
        // }   
        // // 更新 level
        // while (level > 1 && head->nxt[level - 1] == nullptr)
        //     level--;
        // return true;
    }
};

*/
>>>>>>> refs/remotes/origin/master
