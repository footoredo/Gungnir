#include <bits/stdc++.h>
using namespace std;

char buf[1111];

int main() {
	for (; ~scanf("%s", buf); ) {
		if (strlen(buf) > 15) puts("TAT");
		else {
			long long x; sscanf(buf, "%lld", &x);
			int ans = -1;
			for (int i = 0; i <= 5; i++) {
				if (x == 1) { ans = i; break; }
				x = sqrt(x) + 1e-8;
			}
			if (~ans) printf("%d\n", ans);
			else puts("TAT");
		}
	}
	return 0;
}
