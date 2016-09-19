#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2e4;
const int MAXN = N * 4 + 11;
const int MOD = 1004535809;
const int RT = 3;
int fac[MAXN], inv_fac[MAXN], inv_num[MAXN], f[MAXN], h[MAXN], a[MAXN], b[MAXN], c[MAXN], R[MAXN];

inline int Fpw(int x, int K, int MOD) {
	if (K < 0) K += MOD - 1;
	int ret = 1; 
	for (; K; K >>= 1) {
		if (K & 1) ret = (LL)ret * x % MOD;
		x = (LL)x * x % MOD;
	}
	return ret;
}

inline void prepare() {
	fac[0] = 1; inv_fac[0] = 1; h[1] = 1;
	for (int i = 1; i <= N * 4; ++i) fac[i] = (LL)fac[i - 1] * i % MOD;
	for (int i = 1; i <= N * 4; ++i) inv_num[i] = Fpw(i, MOD - 2, MOD);
	for (int i = 1; i <= N * 4; ++i) inv_fac[i] = (LL)inv_fac[i - 1] * inv_num[i] % MOD;
	for (int i = 2; i <= N * 4; ++i) h[i] = (LL)Fpw(i, i - 2, MOD) * inv_fac[i - 1] % MOD;
}

inline void NTT(int *a, int n, int f) {
	for (int i = 0; i < n; ++i)
		if (R[i] < i) swap(a[i], a[R[i]]);
	for (int i = 1; i < n; i <<= 1) {
		c[0] = 1; c[1] = f ? Fpw(RT, -(MOD - 1) / (i * 2), MOD) : Fpw(RT, (MOD - 1) / (i * 2), MOD);
		for (int j = 2; j < i; ++j) c[j] = (LL)c[j - 1] * c[1] % MOD;
		for (int p = i << 1, j = 0; j < n; j += p)
			for (int k = 0; k < i; ++k) {
				int x = a[k + j] % MOD, y = (LL)a[i + j + k] * c[k] % MOD;
				a[k + j] = x + y;
				a[i + j + k] = x - y;
			}
	}
}

inline int getsequence(int *a, int *b, int n, int m) {
	int L, pn = n, pm = m;
	n += m;
	for (m = 1, L = 0; m <= n; m <<= 1, L++);
	for (int i = pn + 1; i <= m; ++i) a[i] = 0;
	for (int i = pm + 1; i <= m; ++i) b[i] = 0;
	for (int i = 0; i < m; ++i) R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
	NTT(a, m, 0); NTT(b, m, 0);
	for (int i = 0; i < m; ++i) a[i] = (LL)a[i] * b[i] % MOD;
	NTT(a, m, 1);
	for (int i = 0; i < m; ++i) a[i] = (LL)a[i] * inv_num[m] % MOD;
	return m;
}

inline void solve(int l, int r) {
	if (l == r) {
		if (l == 0) f[0] = 1; else f[l] = (LL)f[l] * inv_num[l] % MOD;
		return;
	}
	int mid = l + r >> 1;
	solve(l, mid);
	int n = mid - l, nn = r - l - 1;
	for (int i = 0; i <= n; ++i) b[i] = f[l + i];
	for (int i = 0; i <= nn; ++i) a[i] = h[i + 1];
	int m = getsequence(a, b, nn, n);
	for (int i = mid + 1; i <= r; ++i)
		if (i - mid - 1 + n < m) f[i] = (f[i] + a[i - mid - 1 + n]) % MOD;
	solve(mid + 1, r);
}

int T, n;

int main() {
	prepare();
	solve(0, N);
	for (int i = 1; i <= N; ++i) f[i] = ((LL)f[i] * fac[i] % MOD + MOD) % MOD;
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		cout << (Fpw(2, n * (n - 1) / 2, MOD) - f[n] + MOD) % MOD << endl;
	}
}
