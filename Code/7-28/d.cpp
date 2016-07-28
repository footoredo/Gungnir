#include <bits/stdc++.h>
using namespace std;
typedef double DB;

const int N = 111;
int n, q, chps;
int C[N], T[N], R[N];
DB p[N];

bool check(int m, DB t) {
	DB outputs = 0, rest = 0, inputs = m * chps;
	for (int i = 0; i < n; i++) {
		if (R[i] / p[i] < t) {
			rest += R[i];
			outputs += p[i];
		}
	}
	//if (abs(t-10) < 1e-2) printf("%.3f %.3f %.3f\n", outputs, inputs, rest);
	return outputs * t <= inputs * t + rest;
}

int main() {
	for (int ca = 1; scanf("%d%d", &n, &q), n || q; ca++) {
		scanf("%d", &chps);
		DB outputs = 0, rest = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &C[i], &T[i], &R[i]);
			outputs += p[i] = DB(C[i]) / T[i];
			rest += R[i];
		}
		printf("Case %d:\n", ca);
		printf("%d\n", int(ceil(outputs / chps) + 1e-9));
		for (int i = 0; i < q; i++) {
			int m; scanf("%d", &m);
			DB l = 0, r = 100000 + 1;
			for (int j = 0; j < 50; j++) {
				DB mid = (l + r) / 2.0;
				if (check(m, mid)) l = mid; else r = mid;
			}
			if (l > 100000) puts("-1.000");
			else printf("%.3f\n", l);
		}
	}
	return 0;
}
