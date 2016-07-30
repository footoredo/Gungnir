#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
int low[N], s[N], n, f[N], zero[N], zero_back[N];

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		scanf("%d", &n);
		low[0] = -1000000 - 1; zero[0] = 0;
		for (int i = 1; i <= n; i++) {
			low[i] = 1000000 + 1;
			scanf("%d", &s[i]);
			zero[i] = zero[i-1];
			if (s[i] == 0) ++zero[i];
		} low[n+1] = 1000000 + 1;
		zero_back[n + 1] = 0;
		for (int i = n; i >= 1; i--) {
			zero_back[i] = zero_back[i+1];
			zero_back[i] += s[i] == 0;
		}
		
		int ans = zero_back[1];
		//printf("%d\n", zero_back[1]);
		for (int i = 1; i <= n; i++) {
			if (s[i] == 0) continue;
			int s0 = s[i] - zero[i];
			f[i] = lower_bound(low, low + i, s0) - low;
			//printf("%d %d %d\n", i, s0, f[i]);
			if (f[i] + zero[i] + zero_back[i + 1] > ans)
				ans = f[i] + zero[i] + zero_back[i + 1];
			if (s0 < low[f[i]]) low[f[i]] = s0;
		}
		printf("Case #%d: %d\n", ca, ans);
	}
	return 0;
}
