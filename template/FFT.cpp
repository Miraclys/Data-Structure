#include <iostream>
#include <complex>
#include <cstring>
#include <algorithm>
#define ll long long

const double PI = acos(-1);
const int N = 1e6 + 5;
int n, m;
std::complex<double> F[N << 2], G[N << 2];

void FFT(std::complex<double> *A, int N) {
    if (N == 1) return ;
    int M = N >> 1;
    std::complex<double> A1[M], A0[M];
    for (int i = 0; i < M; ++i) {
        A0[i] = A[i << 1];
        A1[i] = A[i << 1 | 1];
    }
    FFT(A0, M);
    FFT(A1, M);
    std::complex<double> W = std::complex<double>(cos(PI * 1.0 / M), sin(1.0 * PI / M)), w = std::complex<double>(1.0, 0);
    for (int i = 0; i < M; ++i) {
        A[i] = A0[i] + A1[i] * w;
        A[i + M] = A0[i] - w * A1[i];
        w = w * W;
        std::cout << A[i] << " " << A[i + M] << "\n";
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i <= n; ++i) std::cin >> F[i];
    for (int i = 0; i <= m; ++i) std::cin >> G[i];
    int sum = n + m;
    int k = 1;
    while (k <= sum) k <<= 1;
    FFT(F, k);
    FFT(G, k);
    for (int i = 0; i < k; ++i)
        F[i] = F[i] * G[i];
    std::reverse(F + 1, F + k);
    FFT(F, k);
    for (int i = 0; i <= sum; ++i)
        std::cout << (int)(F[i].real() / k + 0.5) << " ";
    // for (auto element : F) {
    //     std::cout << element << "\n";
    // }
    return 0;
}