#include <bits/stdc++.h>
using namespace std;

const int N = 1111, M = N * N * 5, Q = 555555;
int pool[M], cp;
int x[N], ans[Q];
int o[Q], a[Q], b[Q];
vector<pair<int, int> > add, sub;

__inline bool cmp(int x, int y) {
	return a[x] < a[y] || a[x] == a[y] && b[x] < b[y];
}

__inline int fd(int x) {
	return lower_bound(pool, pool + cp, x) - pool + 1;
}

int d[M];
__inline int lowbit(int x) {
	return x & (-x);
}
__inline void d_add(int p, int x) {
	for (; p <= cp; p += lowbit(p)) d[p] += x;
}
__inline int sum(int p) {
	int ret = 0;
	for (; p; p -= lowbit(p)) ret += d[p];
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		int n, m; scanf("%d%d", &n, &m);
		cp = 0; add.clear(); sub.clear();
		for (int i = 0; i < n; i++) scanf("%d", &x[i]);
		for (int i = 0; i <= n; i++) {
			int c[2] = {0, 0}; bool cur = i & 1;
			int cleft[2] = {0, 0}; if (i) cleft[cur ^ 1] += x[i-1]; cur ^= 1;
			for (int j = i-1; j < n; j++, cur ^= 1) {
				if (j >= i) c[cur] += x[j];
				int cc[2] = {cleft[0], cleft[1]}; if (j < n - 1) cc[cur ^ 1] += x[j+1];
				add.push_back(make_pair(c[0], c[1]));
				add.push_back(make_pair(c[0]+cc[0]+1, c[1]+cc[1]+1));
				sub.push_back(make_pair(c[0]+cc[0]+1, c[1]));
				sub.push_back(make_pair(c[0], c[1]+cc[1]+1));
				//printf("%d %d %d %d\n", c[0], c[1], cc[0], cc[1]);
				pool[cp++] = c[1]; pool[cp++] = c[1] + cc[1]+1;
			}
		}
		sort(add.begin(), add.end()); sort(sub.begin(), sub.end());

		for (int i = 0; i < m; i++) {
			o[i] = i;
			scanf("%d%d", a+i, b+i);
			pool[cp++] = b[i];
		}
		sort(pool, pool + cp); cp = unique(pool, pool + cp) - pool;
		sort(o, o + m, cmp);
		
		memset(d+1, 0, sizeof(*d) * cp);
		for (int i = 0, j = 0, k = 0; i < m; i++) {
			for (; j < add.size() && add[j].first <= a[o[i]]; j++) {
				//printf("add %d %d\n", add[j].first, add[j].second);
				d_add(fd(add[j].second), 1);
			}
			for (; k < sub.size() && sub[k].first <= a[o[i]]; k++) {
				//printf("sub %d %d\n", sub[k].first, sub[k].second);
				d_add(fd(sub[k].second), -1);
			}
			//printf("%d %d\n", a[o[i]], b[o[i]]);
			if (sum(fd(b[o[i]]))) ans[o[i]] = 1; else ans[o[i]] = 0;
		}
		
		for (int i = 0; i < m; i++) putchar(ans[i] + '0'); puts("");
	}
	
	return 0;
}
/*
0 0 3 0
3 0 0 4
3 4 0 0
0 0 3 4
0 4 3 0
0 0 0 4
add 0 0
add 0 0
add 0 0
add 0 4
add 0 4
sub 0 0
sub 0 0
sub 0 4
sub 0 4
sub 0 4
1 2
add 3 0
add 3 0
add 3 4
add 3 4
add 3 4
add 3 4
add 3 4
sub 3 0
sub 3 0
sub 3 0
sub 3 4
sub 3 4
sub 3 4
sub 3 4
3 0
3 4
001
*/
