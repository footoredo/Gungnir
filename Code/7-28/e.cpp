#include <bits/stdc++.h>
using namespace std;
typedef long double DB;

const int N = 333;
bool appear[N];
vector<int> seq;

int main() {
	int T; scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++) {
		int a, b, sum; scanf("%d%d", &a, &b); sum = a + b;
		DB len = 0, ans = 0, cur = 1;
		for (int i = 0; i < 1000; i++, cur /= 2.0) {
			len = len / 2 + 1;
			if (a >= b) ans += cur / 2.0;
			if (a == b) break;
			int t = min(a, b);
			if (a > b) {
				b += t; a -= t;
			}
			else {
				a += t; b -= t;
			}
		}
		
		printf("Case %d: %.6f %.6f\n", ca, (double)len, (double)ans);
	}
	
	return 0;
}
