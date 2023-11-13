#include "Complex.hpp"
#include <math.h>
#include <vector>
#include <algorithm>

const int N = 1e6 + 5;
const double PI = acos(-1);

void FFT(std::vector<Complex<double>>& A, int N) {
    if (N == 1) return ;
    int M = N >> 1;
    std::vector<Complex<double>> A0, A1;
    A0.assign(M, Complex<double>(0.0, 0.0));
    A1.assign(M, Complex<double>(0.0, 0.0));
    for (int i = 0; i < M; ++i) {
        A0[i] = A[i << 1];
        A1[i] = A[i << 1 | 1];
        // A0.push_back(A[i << 1]);
        // A1.push_back(A[i << 1 | 1]);
    }
    FFT(A0, M);
    FFT(A1, M);
    Complex<double> W = Complex<double>(cos(PI * 1.0 / M), sin(1.0 * PI / M)), w = Complex<double>(1.0, 0.0);
    for (int i = 0; i < M; ++i) {
        A[i] = A0[i] + w * A1[i];
        A[i + M] = A0[i] - w * A1[i];
        // std::cout << A0[i] << " " << A1[i] << "\n";
        w = w * W;
        // std::cout << A[i] << " " << A[i + M] << "\n";
        // std::cout << "w " << w << "\n"; 
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int sum = n + m;
    int k = 1;
    while (k <= sum) k <<= 1;
    std::vector<Complex<double>> F, G;
    F.assign(N << 2, Complex<double>(0.0, 0.0));
    G.assign(N << 2, Complex<double>(0.0, 0.0));
    // for (auto e : F) {
    //     std::cout << e << "\n";
    // }
    double x;
    for (int i = 0; i <= n; ++i) {
        std::cin >> x;
        F[i] = Complex<double>(x, 0.0);
    }
    // for (int i = 0; i <= n; ++i)
    //     std::cout << F[i] << "\n";
    for (int i = 0; i <= m; ++i) {
        std::cin >> x;
        G[i] = Complex<double>(x, 0.0);
    }
    FFT(F, k);
    FFT(G, k);
    for (int i = 0; i < k; ++i)
        F[i] = F[i] * G[i];
    std::reverse(F.begin() + 1, F.begin() + k); 
    FFT(F, k); 
    for (int i = 0; i <= sum; ++i)
        std::cout << (int)(F[i].getReal() / k + 0.5) << " ";
    return 0;
}