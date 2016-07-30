#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int a[N];

int main() {
	int n;
	for (; ~scanf("%d", &n); ) {
		double ans = 0;
		for (int i = 0; i < n; i++) {
			int x; scanf("%d", &x);
			if (i == 0 || i == n-1) ans += x / 2.0; else ans += x / 3.0;
		}
		if (n == 1) ans *= 2;
		printf("%.10f\n", ans);
	}
	return 0;
}
