#include <iostream>
#include <ctime>

int n, arr[1005];

template<class T>
int find_kth_element(T arr[], int len, int rk) {
    // j 是第一个与 pivot 相等的下标
    // k 是第一个大于 pivot 的下标
    T pivot = arr[rand() % len];
    int i = 0, j = 0, k = len;
    while (i < k) {
        if (arr[i] < pivot) {
            std::swap(arr[i++], arr[j++]);
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[--k]);
        } else {
            ++i;
        }
    }
    if (rk < j) return find_kth_element(arr, j, rk);
    else if (rk >= k) return find_kth_element(arr + k, len - k, rk - k);
    else return pivot;
}

int main() {
    srand(time(0));
    std::cin >> n;
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
    std::cout << find_kth_element<int>(arr, n, 4);
    return 0;
}