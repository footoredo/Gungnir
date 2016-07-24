#include <bits/stdc++.h>
using namespace std;

const int N = 66;
int n, m;
int a[N][N], ca[N];

__inline int mabs(int x) {
	return x > 0 ? x : -x;
}

long long calc(int p) {
	long long ret = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n; j++)
			ret += mabs(a[i][j] - (p + j));
	}
	return ret;
}

int main() {
	for (; scanf("%d%d", &n, &m), n || m; ) {
		memset(ca+1, 0, sizeof(*ca)*n);
		for (int i = 0; i < n * n; i++) {
			int X, Y; scanf("%d%d", &X, &Y);
			a[X][ca[X]++] = Y;
		}
		for (int i = 1; i <= n; i++) {
			assert(ca[i] == n);
			sort(a[i], a[i] + ca[i]);
		}
		long long ans = 1e15;
		for (int i = 1; i <= m - n + 1; i++) {
			long long tmp = calc(i);
			if (tmp < ans) ans = tmp;
		}
		cout << ans << endl;
	}
	
	return 0;
}