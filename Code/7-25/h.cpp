#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
const long double eps = 1e-10;
int n, T;
bool vis[maxn][maxn][maxn][3][2];
long double dp[maxn][maxn][maxn][3][2], B1[2], B2[2], B3[2], D1[2], D2[2], D3[2];

inline long double getp(long double p) {
	if (p > 1 - eps) return 1.0;
	return (p > eps) ? p : 0.0;
}

long double dfs(int n, int A, int C, int s, int p) {
	if (A == 1 && C == 0) return 0.0;
	if (vis[n][A][C][s][p]) return dp[n][A][C][s][p];
	vis[n][A][C][s][p] = true; 
	long double &ret = dp[n][A][C][s][p];
	ret = 0.0;
	if (s == 0) {
		if (A > 1) {
			ret = max(ret, getp(B1[p] - D1[p] * (n - 1)) * (1 - dfs(n, A - 1, C, 1, p ^ 1)));
			ret = max(ret, getp(B2[p] - D2[p] * (n - 1)) * (1 - dfs(n, A - 1, C + 1, 1, p ^ 1)));
		}
		if (C) ret = max(ret, getp(B3[p] - D3[p] * (n - 1)) * (1 - dfs(n, A, C - 1, 1, p ^ 1)));
	}
	if (s == 1) {
		if (A > 1) {
			ret = max(ret, getp(B1[p] - D1[p] * n) * (1 - dfs(n, A - 1, C, 2, p ^ 1)));
			ret = max(ret, getp(B2[p] - D2[p] * n) * (1 - dfs(n, A - 1, C + 1, 2, p ^ 1)));
		}
		if (C) {
			//if (n == 5 && A == 1) printf("ADSFDSA %.5f %.5f %.5f\n", B3[p] - D3[p] * n, getp(B3[p] - D3[p] * n), dfs(n, A, C - 1, 2, p ^ 1));
			ret = max(ret, getp(B3[p] - D3[p] * n) * (1 - dfs(n, A, C - 1, 2, p ^ 1)));
		}
	}
	if (s == 2) {
		if (A > 1) {
			ret = max(ret, getp(B1[p] - D1[p] * n) * (1 - dfs(n + 1, A, C, 0, p ^ 1)));
			ret = max(ret, getp(B2[p] - D2[p] * n) * (1 - dfs(n + 1, A, C + 1, 0, p ^ 1)));
		}
		if (C) ret = max(ret, getp(B3[p] - D3[p] * n) * (1 - dfs(n + 1, A + 1, C - 1, 0, p ^ 1)));
	}
	//cout << n << " " << A << " " << C << " " << s << " " << p;
	//printf(" %.5f\n", ret);
	return ret;
}

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		cin >> B1[0] >> D1[0] >> B2[0] >> D2[0] >> B3[0] >> D3[0];
		cin >> B1[1] >> D1[1] >> B2[1] >> D2[1] >> B3[1] >> D3[1];
		for (int A = 0; A <= n * 3 + 1; ++A)
			for (int C = 0; C <= n * 3 + 1; ++C)
				for (int s = 0; s < 3; ++s)
					for (int i = 0; i <= n * 3 + 1; ++i)
						for (int p = 0; p < 2; ++p)
							vis[i][A][C][s][p] = false;
		printf("%.4f\n", (double)(dfs(n + 1, n, 0, 0, 0) + eps));
	}
}
/*
5 1 1 1 0 0.00000
5 2 0 0 1 0.00000
4 1 1 2 0 0.00000
4 2 0 1 1 0.00000
6 1 1 1 1 0.00000
6 2 0 0 0 0.00000
5 1 1 2 1 0.00000
5 1 2 1 0 0.00000
5 2 0 1 0 0.00000
5 2 1 0 1 0.00000
4 1 2 2 0 0.00000
4 2 0 2 0 0.00000
4 2 1 1 1 0.00000
4 3 0 0 0 1.00000
1.0000

*/
