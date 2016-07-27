#include <bits/stdc++.h>
#define prev PREV
using namespace std;

const int N = 7;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
const int order[4] = {1, 0, 2, 3};
const char dn[5] = "LDRU";
int G[2][N][N];

struct P {
	int x, y; bool b;
	P(): x(0), y(0), b(0) {}
	P(int _x, int _y, bool _b) {
		x = _x; y = _y; b = _b;
	}
	__inline bool have_barrier(int d) {
		return G[b][x][y] & (1 << d);
	}
	__inline bool is_square() {
		return G[b][x][y] & (1 << 4);
	}
	__inline bool is_start() {
		return G[b][x][y] & (1 << 5);
	}
	__inline bool is_end() {
		return G[b][x][y] & (1 << 6);
	}
	__inline bool is_valid() {
		return x >= 0 && y >= 0 && x < 6 && y < 6 && is_square();
	}
	__inline P move(int d) {
		if (have_barrier(d)) return *this;
		else return P(x + dx[d], y + dy[d], b);
	}
};

pair<P, P> Q[N*N*N*N];
int dis[N][N][N][N];
int prevd[N][N][N][N];
pair<P, P> prev[N][N][N][N];
pair<P, P> BFS(pair<P, P> S) {
	int l = 0, r = 0; Q[r++] = S;
	memset(dis, -1, sizeof dis); dis[S.first.x][S.first.y][S.second.x][S.second.y] = 0;
	if (S.first.is_end() && S.second.is_end()) return S;
	for (; l < r; ) {
		//printf("%d %d\n", l, r);
		pair<P, P> u = Q[l++]; int curd = dis[u.first.x][u.first.y][u.second.x][u.second.y];
		//printf("%d %d %d %d\n", u.first.x, u.first.y, u.second.x, u.second.y);
		for (int i = 0; i < 4; i++) {
			int d = order[i];
			pair<P, P> v = make_pair(u.first.move(d), u.second.move(d));
			
			if (!v.first.is_valid() || !v.second.is_valid()) continue;
			//printf("move %c to %d %d %d %d\n", dn[d], v.first.x, v.first.y, v.second.x, v.second.y);
			if (!~dis[v.first.x][v.first.y][v.second.x][v.second.y]) {
				dis[v.first.x][v.first.y][v.second.x][v.second.y] = curd + 1;
				prevd[v.first.x][v.first.y][v.second.x][v.second.y] = d;
				prev[v.first.x][v.first.y][v.second.x][v.second.y] = u;
				if (v.first.is_end() && v.second.is_end()) return v;
				Q[r++] = v;
			}
		}
	}
	return make_pair(P(-1, -1, 0), P(-1, -1, 1));
}

char ans_trace[N*N*N*N];

int main() {
	int T; scanf("%d", &T);
	P rs[2];
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			scanf("%d", &G[0][i][j]);
			if (P(i, j, 0).is_start()) rs[0] = P(i, j, 0);
		}
	for (bool cur = 1; --T; cur = !cur) {
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++) {
				scanf("%d", &G[cur][i][j]);
				if (P(i, j, cur).is_start()) rs[cur] = P(i, j, cur);
			}
		
		pair<P, P> T = BFS(make_pair(rs[0], rs[1]));
		//printf("%d %d\n", T.first.x, T.first.y);
		if (!T.first.is_valid()) puts("-1");
		else {
			int cc = 0;
			for (; !T.first.is_start() || !T.second.is_start(); ) {
				int d = prevd[T.first.x][T.first.y][T.second.x][T.second.y];
				ans_trace[cc++] = dn[d];
				//putchar(dn[d]);
				T = prev[T.first.x][T.first.y][T.second.x][T.second.y];
			}
			ans_trace[cc] = 0;
			reverse(ans_trace, ans_trace + cc);
			printf("%s\n", ans_trace);
		}
	}
	
	return 0;
}
