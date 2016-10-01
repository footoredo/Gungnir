#include <bits/stdc++.h>
using namespace std;

const int MAXT = 20;
const int MAXN = 111111;
const int MAXL = 5e6 + 11;
char str[MAXL], st[MAXL];
int ans, cnt, testcase, N, seq[MAXN], s[MAXT];

struct trie {
	int cc[MAXN][2], c[MAXN][2], sum[MAXN], fail[MAXN], cnt;
	bool end[MAXN];
	inline void init() {
		for (int i = 1; i <= cnt; ++i) {
			cc[i][0] = cc[i][1] = c[i][0] = c[i][1] = sum[i] = fail[i] = end[i] = 0;
		}
		cnt = 1;
	}
	inline void buildfail() {
		for (int i = 1; i <= cnt; ++i) c[i][0] = cc[i][0], c[i][1] = cc[i][1];
		int h = 1, t = 0;
		for (int i = 0; i < 2; ++i)
			if (c[1][i]) fail[c[1][i]] = 1, seq[++t] = c[1][i];
			else c[1][i] = 1;
		for (; h <= t; ++h) {
			int u = seq[h];
			sum[u] = (int)end[u] + sum[fail[u]];
			for (int i = 0; i < 2; ++i)
				if (c[u][i]) {
					fail[c[u][i]] = c[fail[u]][i];
					seq[++t] = c[u][i];
				} else c[u][i] = c[fail[u]][i];
		}
	}
	inline void add(char str[], int l) {
		cnt = 1;
		for (int i = 1; i <= l; ++i) {
			int u = cnt;
			cc[u][str[i] - '0'] = ++cnt;
		}
		end[cnt] = 1;
		buildfail();
	}
} T[MAXT];

inline bool checkin(char str[], int l) {
	for (int i = 1; i <= cnt; ++i) {
		bool flag = true;
		int u = 1;
		for (int j = 1; j <= l; ++j) {
			if (T[i].cc[u][str[j] - '0']) u = T[i].cc[u][str[j] - '0'];
			else {
				flag = false; break;
			}
		}
		if (flag && T[i].end[u]) return true;
	}
	return false;
}

inline void dfs(int a, int b, int u, int v) {
	T[a].end[u] |= T[b].end[v];
	for (int i = 0; i < 2; ++i) {
		if (!T[b].cc[v][i]) continue;
		if (!T[a].cc[u][i]) T[a].cc[u][i] = ++T[a].cnt;
		dfs(a, b, T[a].cc[u][i], T[b].cc[v][i]);
	}
}

inline void merge(int a, int b) {
	dfs(a, b, 1, 1);
	T[a].buildfail();
}

int main() {
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		printf("Case #%d:\n", cs);
		scanf("%d", &N);
		cnt = 0, ans = 0;
		for (; N; --N) {
			scanf("%s", st);
			int l = strlen(st + 1);
			int K = ans % l, tot = 0;
			for (int i = K + 1; i <= l; ++i) str[++tot] = st[i];
			for (int i = 1; i <= K; ++i) str[++tot] = st[i];
			if (st[0] == '+') {
				if (checkin(str, l)) continue;
				T[++cnt].init(); T[cnt].add(str, l); s[cnt] = 1;
				while (cnt > 1 && s[cnt] == s[cnt - 1]) {
					s[cnt - 1] += s[cnt];
					merge(cnt - 1, cnt);
					T[cnt--].init();
				}
			} else {
				int nowans = 0;
				for (int i = 1; i <= cnt; ++i) {
					int u = 1;
					for (int j = 1; j <= l; ++j) {
						u = T[i].c[u][str[j] - '0'];
						nowans += T[i].sum[u];
					}
				}
				printf("%d\n", ans = nowans);
			}
		}
	}
}
/*
1.變量要清空
2.trie建好後的邊發生變化，必須用原來的trie的邊
*/
