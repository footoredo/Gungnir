#include <bits/stdc++.h>
using namespace std;

const int N = 111111, MODN = 1000000007;

char A[N], B[N];
int fail[N];
void build_fail(char *s, int n) {
	fail[0] = -1;
	for (int i = 1, j = -1; i < n; i++) {
		for (; ~j && s[j+1] != s[i]; ) j = fail[j];
		if (s[j+1] == s[i]) ++j;
		fail[i] = j;
	}
}

int f[N];

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		scanf("%s%s", A + 1, B + 1);
		int n = strlen(A + 1), m = strlen(B + 1);
		build_fail(B + 1, m);
		memset(f, 0, sizeof f); f[0] = 1;
		for (int i = 1, j = -1; i <= n; i++) {
			for (; ~j && B[j+2] != A[i]; ) j = fail[j];
			if (B[j+2] == A[i]) ++j;
			f[i] = f[i - 1];
			if (j == m - 1) {
				f[i] = (f[i] + f[i - m]) % MODN;
				j = fail[j];
			}
		}
		printf("Case #%d: %d\n", ca, f[n]);
	}
	return 0;
}
