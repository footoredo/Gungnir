#include <bits/stdc++.h>
using namespace std;

const int maxn = 111111;
int c[maxn], a[maxn], s[maxn], ans[maxn], T, n;

int lowbit(int k) {
	return k & (-k);
}

int query(int k) {
	int ret = 0;
	for (; k <= n; k += lowbit(k)) ret += c[k];
	return ret;
}

void modify(int k) {
	for (; k > 0; k -= lowbit(k)) c[k]++;
}

int main() {
	scanf("%d", &T);
	for (int Q = 1; Q <= T; ++Q) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) c[i] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = n; i; --i) {
			s[i] = query(a[i]);
			modify(a[i]);
		}
		printf("Case #%d:", Q);
		for (int i = 1; i <= n; ++i) {
			int mx = max(max(a[i], i), n - s[i]), mn = min(i, min(a[i], n - s[i]));
			//cout << i << " " << a[i] << " " << s[i] << endl;
			ans[a[i]] = mx - mn;
			//printf(" %d", mx - mn);
		}
		for (int i = 1; i <= n; ++i) printf(" %d", ans[i]);
		puts("");
	}
}
