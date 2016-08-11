#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;
const int MAXN = 222222;
int table[MAXN], c[MAXN], T, n, m, cnt;

set<int> S[MAXN];

struct point {
	int x, y, c;
} p[MAXN];

bool cmp(const point &p, const point &q) {
	return p.y < q.y;
}

inline int lowbit(int k) {
	return k & (-k);
}

inline void add(int k) {
	for (; k <= cnt; k += lowbit(k)) c[k]++;
}

inline int query(int k) {
	if (k <= 0) return 0;
	if (k > cnt) k = cnt;
	int ret = 0;
	for (; k; k -= lowbit(k)) ret += c[k];
	return ret;
}

namespace Reader {
	const int L = (1 << 15) + 5;
	char buffer[L], *S, *T;
	__inline void get_char(char &ch) {
		if (S == T) {
			T = (S = buffer) + fread(buffer, 1, L, stdin);
			if (S == T) {
				ch = EOF;
				return;
			}
		}
		ch = *S++;
	}
	__inline void get_int(int &x) {
		char ch; //bool neg = 0;
		for (; get_char(ch), ch < '0' || ch > '9'; );
		x = ch - '0';
		for (; get_char(ch), ch >= '0' && ch <= '9'; )
			x  = x * 10 + ch - '0';
		//if (neg) x = -x;
	}
}

int main() {
	Reader::get_int(T);
	for (; T; --T) {
		Reader::get_int(n);
		Reader::get_int(m);
		//scanf("%d%d", &n, &m);
		cnt = 0;
		for (int i = 1; i <= n; ++i) {
			Reader::get_int(p[i].x);
			Reader::get_int(p[i].y);
			Reader::get_int(p[i].c);
			//scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].c);
			table[++cnt] = p[i].x;
		}
		
		sort(table + 1, table + cnt + 1);
		cnt = unique(table + 1, table + cnt + 1) - table;
		table[cnt] = INF;
		sort(p + 1, p + n + 1, cmp);
		for (int i = 1; i <= m; ++i) {
			S[i].clear();
			S[i].insert(0);
			S[i].insert(cnt);
		}
		int ans = 0;
		for (int i = 1; i <= cnt; ++i) c[i] = 0;
		int l = 1;
		while (l <= n) {
			int r = l;
			while (r < n && p[r + 1].y == p[r].y) ++r;
			for (int i = l; i <= r; ++i) {
				int x = lower_bound(table + 1, table + cnt + 1, p[i].x) - table;
				set<int>::iterator it = S[p[i].c].lower_bound(x);
				if (*it == x) continue;
//cout << p[i].x << " " << p[i].y << " " << p[i].c << " " << *it << endl;
				int sum1, sum2;
				sum2 = query(*it - 1);
				--it;
				sum1 = query(*it);
				ans = max(ans, sum2 - sum1);
			}
			for (int i = l; i <= r; ++i) {
				int x = lower_bound(table + 1, table + cnt + 1, p[i].x) - table;
				S[p[i].c].insert(x);
				add(x);				
			}
			l = r + 1;
		}
		for (int i = 1; i <= m; ++i) {
			for (set<int>::iterator it = S[i].begin(); it != S[i].end(); ++it) {
				set<int>::iterator tmp = it;
				++tmp;
				if (tmp == S[i].end()) continue;
				ans = max(ans, query(*tmp - 1) - query(*it));
			}
		}
		printf("%d\n", ans);
	}
}
