#include <bits/stdc++.h>
using namespace std;

char buf[111111], *cur;
int deg[26];

void dfs() {
	char u = *cur++;
	//printf("%c\n", u);
	if (u == 0) return;
	++deg[u-'A'];
	for (; *cur != u; ) {
		dfs(); ++deg[u-'A'];
	}
	cur++;
}

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		scanf("%s", buf);
		memset(deg, 0, sizeof deg);
		cur = buf;
		dfs();
		printf("Case %d\n", ca); --deg[*buf - 'A'];
		for (int i = 0; i < 26; i++) if (deg[i]) {
			printf("%c = %d\n", i + 'A', deg[i]);
		}
	}
	return 0;
}
