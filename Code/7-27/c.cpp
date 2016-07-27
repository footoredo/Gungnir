#include <bits/stdc++.h>
using namespace std;

int n, D, p, L, v;

int main () {
	int T = 0;
	while (1) {
		scanf("%d%d", &n, &D);
		if (D == 0) return 0;
		double ans = D;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", &p, &L, &v);
			ans = ans - 1.0 * L + 2.0 * L / v;
		}
		printf("Case %d: %.3f\n\n", ++T, ans);
	}
}
