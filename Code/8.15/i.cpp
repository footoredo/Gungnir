#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int R = 6;
const int MOD = 1e9 + 7;
const int MAXN = 100001;
const int MAXQ = 100001;
int hash1[MAXN], hash2[MAXN], c[MAXN], pw[1000], ans[MAXQ], T, n, Q, cnt; 
char str[MAXN], st[111];

struct interval {
	int l, r, hash;
} E[MAXN * 200];

struct question {
	int l, r, hash, id;
} q[MAXQ];

inline bool cmp_E_hash(const interval &p, const interval &q) {
	return p.hash < q.hash;
}

inline bool cmp_q_hash(const question &p, const question &q) {
	return p.hash < q.hash;
}

inline bool cmp_E_r(const interval &p, const interval &q) {
	return p.r < q.r;
}

inline bool cmp_q_r(const question &p, const question &q) {
	return p.r < q.r;
}

inline int gethash1(int l, int r) {
	int ret = ((LL)hash1[r] - (LL)hash1[l - 1] * pw[r - l + 1]) % MOD;
	if (ret < 0) ret += MOD;
	return ret;
}

inline int gethash2(int l, int r) {
	int ret = ((LL)hash2[l] - (LL)hash2[r + 1] * pw[r - l + 1]) % MOD;
	if (ret < 0) ret += MOD;
	return ret;
}

inline int lowbit(int k) {
	return k & (-k);
}

inline void modify(int k, int x) {
	for (; k; k -= lowbit(k)) c[k] += x;
}

inline int query(int k) {
	int ret = 0;
	for (; k <= n; k += lowbit(k)) ret += c[k];
	return ret;
}

int main() {
	pw[0] = 1;
	for (int i = 1; i < 30; ++i) pw[i] = (LL)pw[i - 1] * R % MOD;
	while (scanf("%s", str + 1) != EOF) {
		n = strlen(str + 1);
		hash1[0] = hash2[n + 1] = 0;
		for (int i = 1; i <= n; ++i) hash1[i] = ((LL)hash1[i - 1] * R + str[i] - 'a' + 1) % MOD;
		for (int i = n; i; --i) hash2[i] = ((LL)hash2[i + 1] * R + str[i] - 'a' + 1) % MOD;
		cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n && j - i + 1 <= 20; ++j)
				if (gethash1(i, j) == gethash2(i, j)) {
					int mid = (i + j + 1) / 2;
					for (int k = (i + j + 1) / 2; k <= j; ++k) {
						int hash = gethash1(mid, k);
						E[++cnt].l = i; E[cnt].r = j; E[cnt].hash = hash;
						//if (cnt % 1000000 == 0) printf("%d\n", cnt);
						//cout << i << " " << k << " " << j << " " << hash << endl;
					}
				}
		}
		sort(E + 1, E + cnt + 1, cmp_E_hash);
//for (int i = 1; i <= cnt; ++i) cout << E[i].l << " " << E[i].r << " " << E[i].hash << endl;
		
		scanf("%d", &Q);
		for (int i = 1; i <= Q; ++i) {
			int ll, rr;
			scanf("%d%d%s", &q[i].l, &q[i].r, st);
			int hash = 0, l = strlen(st);
			for (int j = 0; j < l; ++j) hash = hash * R + st[j] - 'a' + 1;
			q[i].hash = hash; q[i].id = i; ans[i] = 0;
		}
		sort(q + 1, q + Q + 1, cmp_q_hash);
//for (int i = 1; i <= Q; ++i) cout << q[i].l << " " << q[i].r << " " << q[i].hash << " " << q[i].id << endl;
		
		int L = 0, R;
		int i = 1, j;
		while (i <= Q) {
			j = i;
			while (j < Q && q[j + 1].hash == q[i].hash) ++j;
			while (L < cnt && E[L + 1].hash < q[i].hash) ++L;
			//cout << cnt << " " <<  i << " " << j << " " << L <<  " " << R << endl;
			if (L == cnt || E[L + 1].hash != q[i].hash) {
				i = j + 1; continue;
			}
			++L; R = L;
			while (R < cnt && E[R + 1].hash == E[R].hash) ++R;
			//cout << i << " " << j << " " << L <<  " " << R << endl;
			sort(E + L, E + R + 1, cmp_E_r);
			sort(q + i, q + j + 1, cmp_q_r);
//for (int k = L; k <= R; ++k) cout << E[k].l << " " << E[k].r << " " << E[k].hash << endl;
//for (int k = i; k <= j; ++k) cout << q[k].l << " " << q[k].r << " " << q[k].hash << " " << q[k].id << endl;
//puts("---------");
			int k = L - 1;
			memset(c, 0, sizeof(c));
			for (int t = i; t <= j; ++t) {
				//cout << E[k + 1].r << " " << q[t].r << endl;
				while (k < R && E[k + 1].r <= q[t].r) {
					++k;
					//cout << E[k].l << endl;
					modify(E[k].l, 1);
				}
				//cout << "query: " << q[t].l << " " << query(q[t].l) << endl;
				ans[q[t].id] = query(q[t].l);
			}
			for (int t = L; t <= k; ++t) modify(E[t].l, -1);
			i = j + 1;
//break;
		}
		for (int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
	}
}
