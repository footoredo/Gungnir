#include <bits/stdc++.h>
using namespace std;

const int N = 333;
int f[2][555][55][2];
int p[N], h[N], s[N], V1, V2;

__inline void update(int &f0, int f) {
	if (f > f0) f0 = f;
}

int main() {
	int n, V1, V2;
	for (int T = 1; scanf("%d%d%d", &V1, &V2, &n), n || V1 || V2; T++) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d", &p[i], &h[i], &s[i]);
		memset(f[0], -1, sizeof f[0]); bool cur = 0;
		f[0][V1][V2][0] = 0;
		for (int i = 1; i <= n; i++, cur = !cur) {
			memset(f[!cur], -1, sizeof f[!cur]);
			for (int v1 = 0; v1 <= V1; v1++)
				for (int v2 = 0; v2 <= V2; v2++) {
					if (v1 >= p[i]) {
						if (~f[cur][v1][v2][0]) update(f[!cur][v1-p[i]][v2][0], f[cur][v1][v2][0] + h[i]);
						if (~f[cur][v1][v2][1]) update(f[!cur][v1-p[i]][v2][1], f[cur][v1][v2][1] + h[i]);
					}
					if (v2 >= p[i]) {
						if (~f[cur][v1][v2][0]) update(f[!cur][v1][v2-p[i]][0], f[cur][v1][v2][0] + h[i]);
						if (~f[cur][v1][v2][1]) update(f[!cur][v1][v2-p[i]][1], f[cur][v1][v2][1] + h[i]);
					}
					if (!s[i]) {
						update(f[!cur][v1][v2][0], f[cur][v1][v2][0]);
						update(f[!cur][v1][v2][1], f[cur][v1][v2][1]);
					}
					if (~f[cur][v1][v2][0]) update(f[!cur][v1][v2][1], f[cur][v1][v2][0] + h[i]);
				}
		}
		int ans = -1;
		for (int v1 = 0; v1 <= V1; v1++)
			for (int v2 = 0; v2 <= V2; v2++) {
				update(ans, f[cur][v1][v2][0]);
				update(ans, f[cur][v1][v2][1]);
			}
		printf("Case %d: %d\n\n", T, ans);
	}
	return 0;
}
