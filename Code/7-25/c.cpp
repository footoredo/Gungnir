#include <bits/stdc++.h>
using namespace std;

const int N = 111;
int A[N], B[N];

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		int m, n; scanf("%d%d", &m, &n);
		for (int i = 0; i < m; i++) scanf("%d", A+i);
		for (int i = 0; i < n; i++) scanf("%d", B+i);
		sort(A, A + m);
		for (int i = 0; i < n; i++) {
			int db = 100, ans;
			for (int j = 0; j < m; j++) {
				int tmp = __builtin_popcount(A[j] ^ B[i]);
				if (tmp < db) {
					db = tmp; ans = A[j];
				}
			}
			printf("%d\n", ans);
		}
		
	}
	return 0;
}
