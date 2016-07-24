#include <bits/stdc++.h>
using namespace std;

__inline __int128 gcd(__int128 a, __int128 b) {
	for (; b; ) {
		__int128 t = b; b = a % b; a = t;
	}
	return a;
}
/*
struct Frac {
	long long n, m;
	__inline Frac(__int128 n0 = 0, long long m0 = 1) {
		if (n0 < 0) n0 = -n0;
		//if (m0 < 0) m0 = -m0;
		long long g = gcd(m0, n0 % m0);
		n = n0 / g; m = m0 / g;
	}
	__inline Frac operator+(const Frac &rhs) {
		//__int128 g = gcd(m, rhs.m);
		return Frac(__int128(n) * rhs.m + __int128(m) * rhs.n, m * rhs.m);
	}
	__inline Frac operator-(const Frac &rhs) {
		//__int128 g = gcd(m, rhs.m);
		return Frac(__int128(n) * rhs.m - __int128(m) * rhs.n, m * rhs.m);
	}
	__inline Frac operator*(const Frac &rhs) {
		return Frac(__int128(n)  * rhs.n, m * rhs.m);
	}
};
*/
const int N = 111111;
int w[N];

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		int n; scanf("%d", &n);
		long long sum = 0; long long ans = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &w[i]);
			if (w[i] > 0) sum += w[i]; else sum += (w[i] = -w[i]);
		}
		for (int i = 0; i < n; i++) {
			ans = ans + w[i] * w[i];
		}
		long long up = ans * n - sum * sum, down = n;
		long long g = gcd(up, down);
		printf("%I64d/%I64d\n", (long long)(up / g), (long long)(down / g));
		//printf("%lld/%lld\n", (long long)(up / g), (long long)(down / g));
	}
	
	return 0;
}
