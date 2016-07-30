#include <bits/stdc++.h>
using namespace std;

const int N = 20, M = N * N;
int connect[N], x[M], y[M], g[1<<N], n, m;
bool f[1<<N];

__inline int calc(int u, int v) {
	return g[(1<<n)-1 - (1<<u)] + g[(1<<n)-1 - (1<<v)] - 2 * g[(1<<n)-1 - (1<<u) - (1<<v)];
}

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			connect[i] = 0;
		}
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &x[i], &y[i]);
			connect[x[i]] |= 1 << y[i];
			connect[y[i]] |= 1 << x[i];
		}
		
		f[0] = 0;
		for (int i = 1; i < (1<<n); i++) {
			int t = i & (-i), tt = __lg(t);
			if (i == t) {
				f[i] = 1; continue;
			}
			f[i] = 0;
			for (int j = 0; j < n; j++) if (i & (1<<j))
				f[i] |= f[i ^ (1<<j)] && (bool)(connect[j] & (i ^ (1<<j)));
		}
		//printf("%d\n", f[7]);
		for (int i = 0; i < (1<<n); i++)
			if (i & 1) {
				g[i] = f[i] && f[((1<<n)-1) ^ i];
				//if (g[i]) cout << bitset<4>(i) << endl;
			}
			else g[i] = 0;
		//puts("done");
		for (int i = 0; i < n; i++) {
			for (int mask = 0; mask < (1<<n); mask++) {
				if (mask & (1<<i)) g[mask] += g[mask ^ (1<<i)];
			}
		}	
		
		printf("Case #%d: ", ca);
		for (int i = 0; i < m; i++) {
			printf("%d%c", calc(x[i], y[i]), i == m-1 ? '\n' : ' ');
		}
	}
	return 0;
}
