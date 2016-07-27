#include <bits/stdc++.h>
using namespace std;

const int N = 102;
int n, k, h[N], pool[N], cp;
char f[2][N][1<<8][8];

inline void update(char &f, char ff) {
	if (!~f || ff < f) f = ff;
}

int main() {
	for (int T = 1; scanf("%d%d", &n, &k), n || k; T++) {
		cp = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &h[i]);
			pool[cp++] = h[i];
		}
		sort(pool, pool + cp); cp = unique(pool, pool + cp) - pool;
		for (int i = 1; i <= n; i++) {
			h[i] = lower_bound(pool, pool + cp, h[i]) - pool;
			//printf("%d\n", h[i]);
		}
		memset(f, -1, sizeof f);
		f[0][0][0][0] = 0; bool cur = 0;
		for (int i = 0; i < n; i++, cur = !cur) {
			memset(f[!cur], -1, sizeof f[!cur]);
			for (int j = 0; j <= k; j++)
				for (int mask = 0; mask < (1<<cp); mask++) {
					for (int last = 0; last < cp; last++)
						if (~f[cur][j][mask][last]) {
							update(f[!cur][j][mask|(1<<h[i+1])][h[i+1]], f[cur][j][mask][last] + (int)(!mask||h[i+1]!=last));
							update(f[!cur][j+1][mask][last], f[cur][j][mask][last]);
						}
				}
		}
		
		//printf("%d\n", f[5][1][3][0]);
		char ans = -1;
		//printf("%d\n", (int)ans);
			for (int j = 0; j <= k; j++)
				for (int mask = 0; mask < (1<<cp); mask++)
					for (int last = 0; last < cp; last++)
						if (~f[cur][j][mask][last]) {
							/*if (j == 1 && mask == 3 && last == 0) {
								puts("xx");
								printf("%d %d\n", f[n][j][mask][last], ((1<<cp)-1)^mask);
							}*/
							update(ans, f[cur][j][mask][last] + __builtin_popcount(((1<<cp)-1)^mask));
						}
		
		printf("Case %d: %d\n\n", T, (int)ans);
	}
	
	return 0;
}
