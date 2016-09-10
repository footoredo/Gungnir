#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

const int N = 200005, M = 2e5 + 5;
int adj[N], v[M + N], nxt[M + N], e;
std::set<std::pair<int, int> > xxx;
__inline void add(int u0, int v0) {
	if (xxx.count(std::make_pair(u0, v0))) return;
	v[e] = v0; nxt[e] = adj[u0]; adj[u0] = e ++;
	xxx.insert(std::make_pair(u0, v0));
}

int rem_p[2][N], cr[2];
int layer[2][N], cl[2];
std::vector<int> del;
__inline void clear(std::vector<int>& v) {
	v.clear();
	std::vector<int>(v).swap(v);
}
__inline void clear(std::set<int>& v) {
	v.clear();
	std::set<int>(v).swap(v);
}
__inline void clear(std::set<std::pair<int, int> >& v) {
	v.clear();
	std::set<std::pair<int, int> >(v).swap(v);
}
int dis[N];

int main() {
	/*std::ios::sync_with_stdio(false);
	std::cin.tie(0);*/
	//std::cout.tie(0);

	int T; scanf("%d", &T);
	for (; T --; ) {
		int n, m; scanf("%d%d", &n, &m);
		e = 0; memset(adj + 1, -1, sizeof(*adj) * n);
		clear(xxx);
		for (int i = 0; i < m; ++ i) {
			int u, v; scanf("%d%d", &u, &v);
			add(u, v); add(v, u);
		}

		int S; scanf("%d", &S);
		cl[0] = cl[1] = 0; layer[0][cl[0] ++] = S;
		cr[0] = cr[1] = 0; dis[S] = 0;
		for (int i = 1; i <= n; ++ i) {
			if (i != S) {
				rem_p[0][cr[0] ++] = i;
				dis[i] = -1;
			}
		}
		int cur_dis = 1;
		for (bool cur = 1; cl[!cur]; cur = !cur, ++ cur_dis) {
			cl[cur] = cr[cur] = 0;
			for (int i = 0; i < cr[!cur]; ++ i) {
				int u = rem_p[!cur][i], tmp = 0;
				for (int e = adj[u]; ~e; e = nxt[e])
					if (dis[v[e]] == cur_dis - 1) {
						++ tmp;
					}
				if (tmp != cl[!cur]) {
					layer[cur][cl[cur] ++] = u;
					dis[u] = cur_dis;
				}
				else rem_p[cur][cr[cur] ++] = u;
			}
		}
		int last = S == n ? n - 1 : n;
		for (int i = 1; i <= n; ++ i)
			if (i != S) printf("%d%c", dis[i], (i == last ? '\n' : ' '));
//			if (i != S) std::cout << dis[i] << (i == last ? '\n' : ' ');
//		std::cerr << cur_dis << std::endl;
	}

	return 0;
}
