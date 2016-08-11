#include <bits/stdc++.h>
#include <queue>
#define stack STACK123
using namespace std;

typedef long long LL;
typedef long double LD;
const int MAXN = 11111;
const int MAXM = 11111;
const LD eps = 1e-10;
const LL INF = 1e18;
int n, m, cnt, S[2], T, sum, top[2], x, y, id[2], adj[MAXN];
LL dist[MAXN][111], X[1111111];
bool vis[MAXN][111];
char ch[1111];

pair<LL, LL> stack[2][MAXN];

struct edge {
	int v, nxt;
	LL w;
} e[MAXM];

inline void addedge(int x, int y, LL w) {
	e[++cnt].v = y; e[cnt].w = w; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

LD getx(pair<LL, LL> p, pair<LL, LL> q) {
	return (LD)1.0 * (q.second - p.second) / (p.first - q.first);
}

LL getdist(pair<LL, LL> l, LL x) {
	return l.first * x + l.second;
}

void getstack(int k) {
	top[k] = 0;
	for (int i = sum; i >= 0; --i) {
		if (dist[S[k]][i] == INF) continue;
		pair<LL, LL> tmp = make_pair(i, dist[S[k]][i]);
		while (top[k] > 1 && getx(stack[k][top[k] - 1], stack[k][top[k]]) > getx(stack[k][top[k]], tmp) - eps) --top[k];
		stack[k][++top[k]] = tmp;
	}
}
queue<pair<int, int> > seq;

int main() {
	while (scanf("%d%d%d%d%d", &n, &m, &S[0], &S[1], &T), n) {
		cnt = sum = 0;
		memset(adj, 0, sizeof(*adj) * (n + 1));
		for (int i = 1; i <= m; ++i) {
			LL w = 0;
			scanf("%d%d%s", &x, &y, ch);
			if (ch[0] == 'x') {
				w = -1, sum++;
				addedge(x, y, w);
				addedge(y, x, w);
			} else {
				int l = strlen(ch);
				for (int j = 0; j < l; ++j) w = w * 10 + ch[j] - '0';
				addedge(x, y, w);
				addedge(y, x, w);
			}
		}
		
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j <= sum; ++j)
				dist[i][j] = INF, vis[i][j] = false;
		while (!seq.empty()) seq.pop();
		dist[T][0] = 0; vis[T][0] = true;
		seq.push(make_pair(T, 0));
		while (!seq.empty()) {
			pair<int, int> u = seq.front();
			seq.pop();
			vis[u.first][u.second] = false;
			for (int p = adj[u.first]; p; p = e[p].nxt) {
				int v = e[p].v;
				//cout << u << " " << v << " " << 
				if (e[p].w < 0) {
					//cout << u.first << " " << u.second << " " << dist[u.first][u.second] << endl;
					if (u.second < sum && dist[u.first][u.second] < dist[v][u.second + 1]) {
						dist[v][u.second + 1] = dist[u.first][u.second];
						pair<int, int> tmp = make_pair(v, u.second + 1);
						if (!vis[tmp.first][tmp.second]) {
							vis[tmp.first][tmp.second] = true;
							seq.push(tmp);
						}
					}
				} else {
					if (dist[u.first][u.second] + e[p].w < dist[v][u.second]) {
						dist[v][u.second] = dist[u.first][u.second] + e[p].w;
						if (!vis[v][u.second]) {
							vis[v][u.second] = true;
							seq.push(make_pair(v, u.second));
						}
					}
				}
			}
		}
		
	/*for (int j = 0; j <= sum; ++j) {
		for (int i = 1; i <= n; ++i)
			cout << dist[i][j] << " ";
		cout << endl;
	}
	cout << "asdf" << endl;*/
		
		for (int k = 0; k < 2; ++k) getstack(k);
	/*for (int k = 0; k < 2; ++k) {
		for (int i = 1; i <= top[k]; ++i) cout << stack[k][i].first << " " << stack[k][i].second << endl;
		cout << "------" << endl;	
	}*/
		int N = 1;
		X[1] = 0;
		for (int k = 0; k < 2; ++k) {
			for (int i = 1; i < top[k]; ++i) {
				LL tx = LL(round(getx(stack[k][i], stack[k][i + 1])));
				for (int j = -2; j <= 2; ++j) 
					if (tx + j > 0) X[++N] = tx + j;
			}
		}
		for (int i = 1; i <= top[0]; ++i)
			for (int j = 1; j <= top[1]; ++j) {
				if (stack[0][i].first == stack[1][j].first) continue;
				LL tx = LL(round(getx(stack[0][i], stack[1][j])));
				
				for (int k = -2; k <= 2; ++k)
					if (tx + k > 0) X[++N] = tx + k;
			}
		sort(X + 1, X + N + 1);
		N = unique(X + 1, X + N + 1) - X - 1;
		id[1] = id[0] = 1;
		LL ans = INF;
		for (int i = 1; i <= N; ++i) {
			if (X[i] > 1e12) break;
			for (int k = 0; k < 2; ++k)
				while (id[k] < top[k] && getdist(stack[k][id[k] + 1], X[i]) <= getdist(stack[k][id[k]], X[i])) id[k]++;
			ans = min(ans, abs(getdist(stack[0][id[0]], X[i]) - getdist(stack[1][id[1]], X[i])));
		}
		cout << ans << endl;
	}
}
