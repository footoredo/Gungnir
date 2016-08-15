#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300;
int sg[MAXN], used[MAXN], n;
int T, x;

int main() {
	/*scanf("%d", &n);
	sg[0] = 0;
	for (int i = 1; i <= n; ++i) {
		memset(used, 0, sizeof(used));
		for (int j = 0; j < i; ++j) used[sg[j]] = 1;
		for (int x = 1; x < i; ++x)
			for (int y = 1; x + y < i; ++y)
				used[sg[x] ^ sg[y] ^ sg[i - x - y]] = 1;
		for (int j = 1; j < MAXN; ++j)
			if (!used[j]) {
				sg[i] = j;
				break;
			}
		if (i != sg[i]) printf("%d %d\n", i, sg[i]);
	}*/
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d", &n);
		int ans = 0;
		for (; n; --n) {
			scanf("%d", &x);
			if (x % 8 == 0) ans ^= (x - 1);
			else 
				if (x % 8 == 7) ans ^= (x + 1);
				else ans ^= x;
		}
		if (ans) puts("First player wins.");
		else puts("Second player wins.");
	}
}
