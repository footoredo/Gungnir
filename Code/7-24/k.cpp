#include <bits/stdc++.h>
using namespace std;

int n, Q, x;

int main() {
	scanf("%d", &Q);
	for (; Q; --Q) {
		scanf("%d", &n);
		int tot = 0;
		long long total = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x);
			if (x % 2) tot++, total += (x - 1) / 2;
			else total += x / 2;
		}
		//cout << tot << " " << total << endl;
		if (!tot) cout << total * 2 << endl;
		else cout << 1 + total / tot * 2 << endl;
	}
}
