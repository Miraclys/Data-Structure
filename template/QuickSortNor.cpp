#include <iostream>
#include <vector>
#include <cstring>
#include "./Stack.hpp"

class Student {
    private:
        int age;
        char* name;
    public:
        int getAge() const {
            return age;
        }
        std::string getName() {
            return name;
        }
        Student(int Age, const char* Name): age(Age) {
            name = new char[20];
            strcpy(name, Name);
        }
        ~Student() {
            delete[] name;
        }
        friend std::ostream& operator<<(std::ostream& os, const Student student) {
            os << student.name << " " << student.age;
            return os;
        }
};

struct CompareStudent {
    bool operator()(const Student& x, const Student& y) const {
        return x.getAge() > y.getAge();
    }
};

template<class T, typename Compare>
int partition(std::vector<T>& v, int l, int r, Compare compare) {
    int pre = l;
    int cur = pre + 1;
    T key = v[l];
    while (cur <= r) {
        if (compare(key, v[cur]) && ++pre != cur)
            std::swap(v[cur], v[pre]);
        ++cur; 
    }
    std::swap(v[l], v[pre]);
    return pre;
}

template<class T, typename Compare>
void quickSort(std::vector<T>& v, int l, int r, Compare compare) {
    if (l >= r) return ;
    Stack<int> s;
    s.push(l);
    s.push(r);
    while (!s.empty()) {
        int right = s.pop();
        int left = s.pop();
        if (left >= right) continue;
        int boundary = partition(v, left, right, compare);
        s.push(left);
        s.push(boundary - 1);
        s.push(boundary + 1);
        s.push(right);
    }
}

int main() {
    CompareStudent compareStudent;
    std::vector<Student> v = {
        Student(19, "lys"),
        Student(20, "zym"),
        Student(21, "zzm"),
        Student(17, "xxx")
    };
    quickSort(v, 0, 3, compareStudent);
    for (Student element : v) {
        std::cout << element.getAge() << std::endl;
    }
    for (Student student : v) {
        std::cout << student << std::endl;
    }
    return 0;
}