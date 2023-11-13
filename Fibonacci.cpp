#include <iostream>
#include <vector>
#define ll long long

class Matrix {
    private:
        int rows;
        int cols;
        std::vector<std::vector<long long>> data;
    public:
        Matrix(int row, int col): rows(row), cols(col) {
            data.assign(rows, std::vector<long long>(cols, 0)); 
        }
        Matrix() {
            rows = 0;   
            cols = 0;
            data.assign(rows, std::vector<long long>(cols, 0));
        }
        ll& geData(int row, int col) {
            return data[row][col];
        }
        static Matrix IdentityMatrix(int n) {
            Matrix result(n, n);
            for (int i = 0; i < n; ++i)
                result.geData(i, i) = 1;
            return result;
        }
        Matrix pow(int n) const {
            if (n == 0) return IdentityMatrix(rows);
            if (n == 1) return *this;
            Matrix base = *this;
            Matrix result = IdentityMatrix(rows);
            while (n) {
                if (n & 1) result = result * base;
                base = base * base;
                n >>= 1;
            }
            return result;
        }
        Matrix operator*(const Matrix& x) const {
            Matrix result(rows, x.cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < x.cols; ++j) {
                    for (int k = 0; k < cols; ++k) {
                        result.data[i][j] += data[i][k] * x.data[k][j];
                    }
                }
            }
            return result;
        }
};

ll Fibnacci(int n) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    Matrix Fib(2, 1);
    Fib.geData(0, 0) = 1;
    Fib.geData(1, 0) = 1;
    Matrix base(2, 2);
    base.geData(0, 0) = 1;
    base.geData(0, 1) = 1;
    base.geData(1, 0) = 1;
    base.geData(1, 1) = 0;
    Matrix result = base.pow(n - 2);
    return (result * Fib).geData(0, 0);
}

int main() {
    int n;
    std::cin >> n;
    std::cout << Fibnacci(n) << "\n";
    return 0;
}