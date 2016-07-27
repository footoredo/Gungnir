#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int maxn = 111111;
int T, n, K, a[maxn], c[maxn];

int check(LL mid) {
	int d = int(sqrt(mid)), ret = 0;
	LL size = 0, S = 0, T = 0;
	for (int i = n; i; --i) {
		if (i + d + 1 <= n) {
			size -= c[i + d + 1];
			S -= (LL)c[i + d + 1] * (i + d + 1);
			T -= (LL)c[i + d + 1] * (i + d + 1) * (i + d + 1);
		}
		//cout << i << " " << size << " " << S << " " << T << endl;
		LL tmp = (LL)a[i] - size * mid + T + size * i * i - LL(2) * i * S;
		if (tmp <= 0) {
			c[i] = 0;
			continue;
		}
		c[i] = (tmp - 1) / mid + 1;
		size += c[i]; 
		S += (LL)c[i] * i;
		T += (LL)c[i] * i * i;
		ret += c[i];
		//cout << i << " " << ret << " " << c[i] << " " << S << " " << T << " " << size << " " << tmp << endl;
		if (ret > K) return K + 1;
	}
	return ret;
}

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%d", &n, &K);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[i]++;
		}
		
		//cout << check(6) << endl;
		LL left = 1, right = 1e10;
		while (left < right) {
			LL mid = left + right >> 1;
			if (check(mid) > K) left = mid + 1; else right = mid;
		}
		cout << left << endl;
	}
}
