#include <bits/stdc++.h>
using namespace std;

const int D = 40;
long long f[111], T, p, q;

int g[20101][30], ans_p[20101];
int found(int x, int lim, int cur) {
	//printf("solving %d %d\n", x, cur);
	//if (x == 7 && cur == 0) printf("jksdhfsdkfhdjk %d %d %d\n", x, cur, lim);
	if (x == 0) return 0;
	if (x < 0) return -1;
	if (lim == 20) return -1;
	if (g[x][cur]) return g[x][cur];
	g[x][cur] = -1;
	int tmp = found(x - (1 << cur), lim + 1, cur + 1);
	if (~tmp) if (!~g[x][cur] || g[x][cur] > tmp + 1) g[x][cur] = tmp + 1;
	tmp = found(x, lim + 1, 0);
	if (~tmp) if (!~g[x][cur] || g[x][cur] > tmp + 1) g[x][cur] = tmp + 1;
	tmp = found(x + 1, lim + 1, 0);
	if (~tmp) if (!~g[x][cur] || g[x][cur] > tmp + 1) g[x][cur] = tmp + 1;
	//if (x == 6 && cur == 1)printf("jksdhfsdkfhdjk %d %d %d\n", x, cur, g[x][cur]);
	return g[x][cur];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	for (int i = 1; i <= D; ++i) f[i] = f[i - 1] + (1LL << (i - 1));
	for (int i = 1; i <= 100; ++ i) {
		//memset(g, 0, sizeof g);
		//ans_p[i] = found(i, 0, 0);
		//printf("%d %d\n", i, found(i, 0, 0));
	}
	//return 0;
	std::cin >> T;
	for (; T; --T) {
		std::cin >> p >> q;
		if (p <= q) {
			std::cout << q - p << std::endl;
			continue;
		}
		long long s = 0, sum = 0, ans = (p - q) * 2 - 1, n = p - q;
		for (int i = D; i; --i) {
			if (f[i] > n) continue;
			n -= f[i]; s++; sum += i;
			//ans = min(ans, s - 1 + sum);
			if (n == 0) {
				ans = min(ans, s - 1 + sum);
				//break;
			}
			//cout << i << " " << f[i] << " " << n << " " << s << " " << sum << " " << ans << endl;
			int tmp;
			if (q + n - (1LL << i) < 0) tmp = 0; else tmp = q + n - (1LL << i);
			ans = min(ans, sum + 1 + max(s - 1, q - tmp));
		}
		std::cout << ans << std::endl;
	}
}
