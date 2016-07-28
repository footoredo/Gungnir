#include <bits/stdc++.h>
using namespace std;

const int N = 555;
char seq[N];
int cnt[26], n, k;

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		memset(cnt, 0, sizeof cnt);
		scanf("%d%d%s", &n, &k, seq);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (i > k) --cnt[seq[i-k-1]-'A'];
			if (cnt[seq[i]-'A']) ++ans;
			++cnt[seq[i]-'A'];
		}
		printf("Case %d: %d\n", ca, ans);
	}
	
	return 0;
}
