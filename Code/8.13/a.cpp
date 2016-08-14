#include <bits/stdc++.h>
typedef long double DB;
const DB eps = 1e-9;

const int M = 256;
int S, A, C, n;
int I[M + 5], R[M + 5], O[M + 5];
void gR(int i) {
	if (i == 0) { R[i] = S; }
	else R[i] = (A * R[i - 1] + C) % M;
}
int nx[M + 5];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (; std::cin >> n, n; ) {
		for (int i = 0; i < n; ++ i) std::cin >> I[i];
		DB entropy = 1e9;
		int aS, aA, aC;
		for (S = 0; S < 16; ++ S)
			for (A = 0; A < 16; ++ A)
				for (C = 0; C < 16; ++ C) {
					memset(nx, 0, sizeof nx);
					gR(0);
					for (int i = 0; i < n; ++ i) {
						gR(i + 1);
						O[i] = (I[i] + R[i + 1]) % M;
						++ nx[O[i]];
					}
					DB tmp = 0;
					for (int i = 0; i < M; ++ i)
						if (nx[i]) tmp -= nx[i] * (log(nx[i]) - log(n));
//					if (S == 8 && A == 7 && C == 14 || S == 1 && A == 7 && C == 12)std::cout << S << " " << A << " " << C << " " << tmp << std::endl;
					if (tmp < entropy - eps) {
						entropy = tmp;
						aS = S; aA = A; aC = C;	
					}
				}
		std::cout << aS << " " << aA << " " << aC << std::endl;
	}

	return 0;
}
