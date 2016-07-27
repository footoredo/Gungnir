#include <bits/stdc++.h>
using namespace std;

const int N = 1111, M = 111111;
int deg[N];
int adj[N], v[M], nxt[M], e;
__inline void ins(int u0, int v0) {
	v[e] = v0; nxt[e] = adj[u0]; adj[u0] = e++;
	++deg[v0];
}

__inline void recover(int n) {
	memset(deg+1, 0, sizeof(*deg) * n);
	memset(adj+1, -1, sizeof(*adj) * n); e = 0;
}

int n, r, p[N];
int ans[N][3];
vector<pair<int, int> > limit[3];

int fd(int x) {
	return x == p[x] ? x : (p[x] = fd(p[x]));
}

bool fail;
int rem[N], Q[N];
void solve(int k) {
	recover(n);
	for (int i = 0; i < limit[k].size(); i++) {
//		if (k == 2) printf("%d %d\n", fd(limit[k][i].first), fd(limit[k][i].second));
		ins(fd(limit[k][i].first), fd(limit[k][i].second));
	}
	for (int i = 1; i <= n; i++) rem[i-1] = fd(i);
	sort(rem, rem + n); int nn = unique(rem, rem + n) - rem;
	int l = 0, r = 0;
	for (int i = 0; i < nn; i++) if (!deg[rem[i]]) {
		//printf("%d\n", rem[i]);
		Q[r++] = rem[i];
	}
	for (; l < r; ) {
		int u = Q[l++];
		for (int e = adj[u]; ~e; e = nxt[e]) {
			if (--deg[v[e]] == 0) {
				Q[r++] = v[e];
			}
		}
	}
//	if (k == 2) printf("%d %d\n", r, nn);
	if (r < nn) fail = 1;
	else {
		for (int i = 0, cur = 0; i < r; i++, cur += 2)
			ans[Q[i]][k] = cur;
	}
}

int main() {
	for (int T = 1; scanf("%d%d", &n, &r), n || r; T++) {
		for (int i = 1; i <= n; i++) {
			p[i] = i;
		}
		limit[0].clear(); limit[1].clear(); limit[2].clear();
		for (int i = 0; i < r; i++) {
			char buf[4]; int x, y; scanf("%s%d%d", buf, &x, &y);
			if (buf[0] == 'I') {
				p[fd(x)] = p[fd(y)];
			}
			else if (buf[0] == 'X') {
				limit[0].push_back(make_pair(x, y));
			}
			else if (buf[0] == 'Y') {
				limit[1].push_back(make_pair(x, y));
			}
			else if (buf[0] == 'Z') {
				limit[2].push_back(make_pair(x, y));
			}
		}

		fail = 0;
		solve(0); solve(1); solve(2);
		printf("Case %d: ", T);
		if (fail) {
			puts("IMPOSSIBLE");
		}
		else {
			puts("POSSIBLE");
			for (int i = 1; i <= n; i++) {
				int p = fd(i);
				printf("%d %d %d %d %d %d\n", 
						ans[p][0], ans[p][1], ans[p][2],
						ans[p][0]+1, ans[p][1]+1, ans[p][2]+1);
			}
		}
		puts("");
	}
	
	return 0;
}
