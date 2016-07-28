#include <bits/stdc++.h>
using namespace std;

const int N = 55;

struct Vec {
	int x, y;
	Vec(): x(0), y(0) {}
	int read() {
		scanf("%d%d", &x, &y);
	}
	__inline int getS(int h) {
		return (h + h + y) * x;
	}
} vec[N];

int det(const Vec& a, const Vec& b) {
	return a.x * b.y - a.y * b.x;
}

bool operator<(const Vec& a, const Vec& b) {
	return det(a, b) < 0;
}

__inline void update(int &f0, int f) {
	if (f > f0) f0 = f;
}

int f[2][N][N*N], n, K, maxheight[N];

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		scanf("%d%d", &n, &K);
		for (int i = 1; i <= n; i++) vec[i].read();
		sort(vec + 1, vec + 1 + n);
		for (int i = 1; i <= n; i++) maxheight[i] = maxheight[i-1] + vec[i].y;
		bool cur = 0; memset(f[cur], -1, sizeof f[cur]);
		f[cur][0][0] = 0;
		for (int i = 0; i < n; i++, cur = !cur) {
			for (int j = 0; j <= i+1 && j <= K; j++)
				for (int h = 0; h <= maxheight[i+1]; h++)
					f[!cur][j][h] = -1;
			for (int j = 0; j <= i && j <= K; j++)
				for (int h = 0; h <= maxheight[i]; h++)
					if (~f[cur][j][h]) {
						update(f[!cur][j][h], f[cur][j][h]);
						update(f[!cur][j+1][h+vec[i+1].y], f[cur][j][h]+vec[i+1].getS(h));
					}
		}
		int ans = -1;
		for (int j = 0; j <= K; j++)
			for (int h = 0; h <= maxheight[n]; h++)
				if (~f[cur][j][h]) update(ans, f[cur][j][h]);
		printf("Case %d: %d\n", ca, ans);
	}	
	
	return 0;
}
