#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int MAXH = 20;
int f[MAXN], val[MAXN], a[MAXN][MAXH], n, T, Q;

inline int getmin(int l, int r) {
	int t = f[r - l + 1];
	return min(a[l][t], a[r - (1 << t) + 1][t]);
}

inline int getnext(int first, int num) {
	int l = first, r = n + 1;
	while (l < r) {
		int mid = l + r>> 1;
		if (getmin(first, mid) <= num) r = mid;
		else l = mid + 1;		
	}
	return l;
}

int main() {
	for (int i = 1; i < MAXN; ++i)
		for (int j = 0; j < MAXH; ++j)
			if ((1 << j) <= i) f[i] = j;
			
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
		for (int i = 1; i <= n; ++i) a[i][0] = val[i];
		a[n + 1][0] = 0;
		for (int h = 1; h < MAXH; ++h)
			for (int i = 1; i <= n + 1; ++i) {
				int j = i + (1 << h - 1);
				if (j > n + 1) a[i][h] = a[i][h - 1];
				else a[i][h] = min(a[i][h - 1], a[j][h - 1]);
			}
		
		scanf("%d", &Q);
		for (; Q; --Q) {
			int x, y;
			scanf("%d%d", &x, &y);
			int nownum = val[x], i = x + 1;
			while (nownum && i <= y) {
				int nxt = getnext(i, nownum);
				if (nxt > y) break;
				nownum %= val[nxt];
				i = nxt + 1;
			}
			printf("%d\n", nownum);
		}
	}
}
