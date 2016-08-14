#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
int T, f[1111];
char str[MAXN];

int main() {
	scanf("%d", &T);
	for (int cs = 1; cs <= T; ++cs) {
		memset(f, 0, sizeof(f));
		scanf("%s", str);
		int l = strlen(str);
		for (int i = 0; i < l; ++i) f[str[i] - 'a']++;
		int s = 0;
		for (int i = 0; i < 26; ++i)
			if (f[i]) s++;
		printf("Case #%d: %d\n", cs, s);
	}
}
