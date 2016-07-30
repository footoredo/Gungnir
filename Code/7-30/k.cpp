#include <bits/stdc++.h>
using namespace std;

const int maxn = 111111;
int d[10000000], T, n, m, cnt;

struct point {
	int x, y;
} p[maxn];

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
		if (n > 1000) printf("YES\n");
		else {
			cnt = 0;
			for (int i = 1; i < n; ++i)
				for (int j = i + 1; j <= n; ++j) {
					d[++cnt] = abs(p[i].x - p[j].x) + abs(p[i].y - p[j].y);
				}
			sort(d + 1, d + cnt + 1);
			bool flag = false;
			for (int i = 2; i <= cnt; ++i)
				if (d[i] == d[i - 1]) flag = true;
			if (flag) printf("YES\n"); else printf("NO\n");
		}
	}
}
