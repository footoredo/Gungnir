#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 55555;
int table[MAXN], a[MAXN], c1[MAXN], c2[MAXN], less1[MAXN], less2[MAXN], more1[MAXN], more2[MAXN], n, cnt;

inline int lowbit(int k) {
	return k & (-k);
}

inline void modify1(int k) {
	for (; k <= cnt; k += lowbit(k)) c1[k]++;
}

inline void modify2(int k) {
	for (; k; k -= lowbit(k)) c2[k]++;
}

inline int query1(int k) {
	int ret = 0;
	for (; k; k -= lowbit(k)) ret += c1[k];
	return ret;
}

inline int query2(int k) {
	int ret = 0;
	for (; k <= cnt; k += lowbit(k)) ret += c2[k];
	return ret;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			table[i] = a[i];
		}
		sort(table + 1, table + n + 1);
		cnt = unique(table + 1, table + n + 1) - table - 1;
		//cout << cnt << endl;
		for (int i = 1; i <= n; ++i)
			a[i] = lower_bound(table + 1, table + cnt + 1, a[i]) - table;
		
		memset(c1, 0, sizeof(c1));
		memset(c2, 0, sizeof(c2));
		for (int i = 1; i <= n; ++i) {
			less1[i] = query1(a[i] - 1);
			more1[i] = query2(a[i] + 1);
			modify1(a[i]);
			modify2(a[i]);
		}
		memset(c1, 0, sizeof(c1));
		memset(c2, 0, sizeof(c2));
		for (int i = n; i; --i) {
			less2[i] = query1(a[i] - 1);
			more2[i] = query2(a[i] + 1);
			modify1(a[i]);
			modify2(a[i]);
		}
		
		LL ans = 0, less = 0, more = 0;
		for (int i = 1; i <= n; ++i) less += less1[i], more += more1[i];
		ans = (LL)less * more;
		for (int i = 1; i <= n; ++i) ans -= (LL)less2[i] * more2[i];
		for (int i = 1; i <= n; ++i) ans -= (LL)less1[i] * less2[i];
		for (int i = 1; i <= n; ++i) ans -= (LL)more1[i] * more2[i];
		for (int i = 1; i <= n; ++i) ans -= (LL)less1[i] * more1[i];
		cout << ans << endl;
	}
}
