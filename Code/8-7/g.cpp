#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int MAXNODE = 1111;
const int MAXS = 1500;
const int MAXL = 111;
int val[111], wei[11111], tail[2], vis[2][MAXNODE][MAXS], n, l, cnt;
char ch[MAXL];

int q[MAXNODE];

struct trie {
	int c[4], f, S;
} tr[MAXNODE];

struct pr {
	int j, mask;
	pr() {};
	pr(int a, int b): j(a), mask(b) {};
} seq[2][MAXN];

inline int getnum(char ch) {
	if (ch == 'A') return 0;
	if (ch == 'T') return 1;
	if (ch == 'C') return 2;
	else return 3;
}

inline int getnode() {
	cnt++;
	tr[cnt].c[0] = tr[cnt].c[1] = tr[cnt].c[2] = tr[cnt].c[3] = tr[cnt].f = tr[cnt].S = 0;
	return cnt;
}

inline void add(int k, char ch[MAXL]) {
	int u = 1, l = strlen(ch);
	for (int i = 0; i < l; ++i) {
		int x = getnum(ch[i]);
		if (!tr[u].c[x]) tr[u].c[x] = getnode();
		u = tr[u].c[x];
	}
	tr[u].S |= 1 << k;
}

inline void buildfail() {
	int h = 1, t = 0;
	for (int i = 0; i < 4; ++i)
		if (tr[1].c[i]) {
			q[++t] = tr[1].c[i];
			tr[q[t]].f = 1;
		} else tr[1].c[i] = 1;
	for (; h <= t; ++h) {
		int u = q[h];
		for (int i = 0; i < 4; ++i)
			if (tr[u].c[i]) {
				int v = tr[u].c[i];
				//cout << u << " " << v << " " << tr[v].f << endl;
				tr[v].f = tr[tr[u].f].c[i];
				tr[v].S |= tr[tr[v].f].S;
				q[++t] = v;
			} else tr[u].c[i] = tr[tr[u].f].c[i];
	}
}

int main() {
	while (scanf("%d%d", &n, &l) != EOF) {
		cnt = 0;
		cnt = getnode();
		for (int i = 0; i < n; ++i) {
			scanf("%s%d", ch, &val[i]);
			//int len = strlen(ch);
			add(i, ch);
		}
		
		buildfail();
//cout << cnt << endl;
//for (int i = 1; i <= cnt; ++i) cout << tr[i].c[0] << " " << tr[i].c[1] << " " << tr[i].c[2] << " " << tr[i].c[3] << " " << tr[i].f << " " << tr[i].S << endl;
		for (int S = 0; S < 1 << n; ++S) {
			wei[S] = 0;
			for (int i = 0; i < n; ++i)
				if (S & (1 << i)) wei[S] += val[i];
		}
		
		int t1 = 1, t2 = 0;
		memset(vis, 0, sizeof(vis));
		tail[0] = 1; vis[0][1][0] = 1;
		seq[0][1] = pr(1, 0);
		for (int i = 1; i <= l; ++i) {
			swap(t1, t2);
			for (int j = 1; j <= tail[t2]; ++j) vis[t2][seq[t2][j].j][seq[t2][j].mask] = 0;
			tail[t2] = 0;
			for (int j = 1; j <= tail[t1]; ++j) {
				pr u = seq[t1][j];
				for (int cc = 0; cc < 4; ++cc) {
					pr v = pr(tr[u.j].c[cc], tr[tr[u.j].c[cc]].S | u.mask);
					if (!vis[t2][v.j][v.mask]) {
						seq[t2][++tail[t2]] = v;
						vis[t2][v.j][v.mask] = 1;
					}
				}
			}
		}
		
		int ans = -1;
		for (int j = 1; j <= cnt; ++j)
			for (int S = 0; S < 1 << n; ++S)
				if (vis[t2][j][S]) ans = max(ans, wei[S]);
		if (ans >= 0) printf("%d\n", ans);
		else printf("No Rabbit after 2012!\n");
	}
}

/*
7
2 5 0 0 0 0
2 3 0 0 1 0
2 5 0 4 5 0
0 0 7 0 6 1
2 5 0 6 1 0
0 0 7 0 0 0
0 0 0 0 0 2

*/
