#include <iostream>
#include <vector>

class Student {
public:
    int getAge() const {
        return age;
    }
    std::string getName() const {
        return name;
    }
    Student(int age, std::string name) : age(age), name(name) {}
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << student.name << " " << student.age;
        return os;
    }
private:
    int age;
    std::string name;
};

template <typename T, typename Compare>
void quick_sort(std::vector<T>& arr, Compare compare) {
    if (arr.size() <= 1) return;
    T p = arr[arr.size() / 2];
    std::vector<T> l, r, e;
    for (T element : arr) {
        if (compare(element, p)) {
            l.push_back(element);
        } else if (compare(p, element)) {
            r.push_back(element);
        } else {
            e.push_back(element);
        }
    }
    quick_sort(l, compare);
    quick_sort(r, compare);
    arr.clear();
    arr.insert(arr.end(), l.begin(), l.end());
    arr.insert(arr.end(), e.begin(), e.end());
    arr.insert(arr.end(), r.begin(), r.end());
}

struct CompareStudent {
    bool operator()(const Student& a, const Student& b) const {
        return a.getAge() < b.getAge();
    }
};

int main() {
    std::vector<Student> students = {
        Student(19, "Lys"),
        Student(18, "Alice"),
        Student(17, "Bob")
    };
    CompareStudent compareStudent;
    quick_sort(students, compareStudent);
    for (const Student& student : students) {
        std::cout << student.getName() << " ";
    }
    for (Student student : students) {
        std::cout << student << std::endl;
    }
    return 0;
}
