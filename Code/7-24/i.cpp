#include <bits/stdc++.h>
using namespace std;

const int limit = 100;
int a[1000], T, n, m, x, y;

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) a[i] = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			a[x] = y;
		}
		
		if (!a[1]) a[1] = 100;
		if (!a[2]) a[2] = min(a[1], 100);
		int minimum = 0;
		for (int i = n; i; --i)
			if (a[i]) minimum = a[i];
			else a[i] = minimum;
		int q = 0;
		for (int i = 1; i <= n; ++i) q += a[i];
		int p = a[1] + a[2];
		int d = __gcd(p, q);
		printf("%d/%d\n", p / d, q / d);
	}
}
