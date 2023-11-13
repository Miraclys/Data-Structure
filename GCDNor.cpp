#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b;
	int mod = b;
	int x = 1, y = 0, t;
	int m = 0, n = 1;
	while (b) {
		t = x, x = m;
		m = t - (a / b) * m;
		t = y, y = n;
		n = t - (a / b) * n;
		t = a, a = b;
		b = t % b;
	}
	std::cout << (x % mod + mod) % mod << std::endl;
	return 0;
}