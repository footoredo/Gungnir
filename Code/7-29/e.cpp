#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL mult(LL a, LL b, LL P) {
	LL t = (a * b - LL((long double)a / P * b + 1e-3) * P) % P;
	return t < 0 ? t + P : t;
}

LL x, y;
void exGcd(LL a, LL b) {
	if (b == 0) {
		x = 1; 
		y = 0;
		return;
	}
	exGcd(b, a % b);
	LL k = y;
	y = x - a / b * y;
	x = k;
}

LL inversion(LL a, LL b) {
	exGcd(a, b);
	return (x % b + b) % b;
}

pair<LL, LL> CRT(vector<LL> m, vector<LL> a) {
	int N = m.size();
	LL M = 1, ret = 0;
	for (int i = 0; i < N; i++)
		M *= m[i];
	for (int i = 1; i < N; i++) {
		ret = (ret + mult(mult(M / m[i], a[i], M), inversion(M / m[i], m[i]), M)) % M;
	}
	return make_pair(M, ret);
}

__inline int lowbit(int x) {
	return x & (-x);
}

const int N = 55;
int p[N], a[N], n;

__inline void clear(vector<LL>& v) {
	v.clear(); vector<LL>(v).swap(v);
}

vector<LL> mm, aa;
pair<LL, LL> solve(int mask) {
	clear(mm); clear(aa);
	mm.push_back(7); aa.push_back(0);
	for (int i; mask; mask ^= i) {
		i = lowbit(mask); int ii = __lg(i); 
		mm.push_back(p[ii]); aa.push_back(a[ii]);
	}
	return CRT(mm, aa);
}

LL calc(LL x, pair<LL, LL> ans) {
	return x < ans.second ? 0 : (x - ans.second) / ans.first + 1;
}

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		LL x, y; cin >> n >> x >> y;
		for (int i = 0; i < n; i++) scanf("%d %d", &p[i], &a[i]);
		LL ans = 0;
		for (int i = 0; i < (1<<n); i++) {
			pair<LL, LL> tmp = solve(i);
			if (__builtin_popcount(i) & 1)
				ans -= calc(y, tmp) - calc(x-1, tmp);
			else ans += calc(y, tmp) - calc(x-1, tmp);
		}
		cout << "Case #" << ca << ": " << ans << endl;
	}
	return 0;
}
