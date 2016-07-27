#include <bits/stdc++.h>
#define stack STACK123
using namespace std;

const int maxn = 444;
const int maxm = 111111;
int n, m, cnt, T, scc, top, dfs_clock, stack[maxn], f[maxn], low[maxn], dfn[maxn], vis[maxn], head[maxn];

struct ques {
	int x, y, c;
} q[maxm];

struct edge {
	int to, front;
} e[maxm];

inline int getnode(int x, int c) {
	return x + c * n;
}

inline void addedge(int x, int y) {
	e[++cnt].to = y; e[cnt].front = head[x]; head[x] = cnt;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++dfs_clock; vis[u] = 1;
	stack[++top] = u;
	for (int p = head[u]; p; p = e[p].front) {
		int v = e[p].to;
		if (!vis[v]) {
			tarjan(v);
			low[u] = min(low[v], low[u]);
		} else {
			if (vis[v] == 1) low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] != low[u]) return;
	scc++;
	while (stack[top] != u) {
		f[stack[top]] = scc;
		vis[stack[top]] = 2;
		top--;
	}
	f[stack[top]] = scc;
	vis[stack[top]] = 2;
	top--;
}

bool check(int mid) {
	for (int i = 1; i <= n * 2; ++i) head[i] = vis[i] = 0;
	cnt = 0; scc = 0;
	for (int i = 1; i <= mid; ++i) {
		if (q[i].c == 0) {
			addedge(getnode(q[i].x, 0), getnode(q[i].y, 1));
			addedge(getnode(q[i].y, 0), getnode(q[i].x, 1));
		}
		if (q[i].c == 1) {
			addedge(getnode(q[i].x, 0), getnode(q[i].y, 0));
			addedge(getnode(q[i].x, 1), getnode(q[i].y, 1));
			addedge(getnode(q[i].y, 0), getnode(q[i].x, 0));
			addedge(getnode(q[i].y, 1), getnode(q[i].x, 1));
		}
		if (q[i].c == 2) {
			addedge(getnode(q[i].x, 1), getnode(q[i].y, 0));
			addedge(getnode(q[i].y, 1), getnode(q[i].x, 0));
		}
	}	
	
	for (int i = 1; i <= n * 2; ++i) {
		if (vis[i]) continue;
		dfs_clock = top = 0;
		tarjan(i);
	}
	for (int i = 1; i <= n; ++i)
		if (f[i] == f[i + n]) return false;
	return true;
}

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].c);
			q[i].x++; q[i].y++;
		}
		//cout << n << " " << m << endl;
		int left = 0, right = m;
		while (left < right) {
			//cout << left << " " << right << endl;
			int mid = left + right + 1>> 1;
			if (check(mid)) left = mid; else right = mid - 1;
		}
		printf("%d\n", left);
	}
}
