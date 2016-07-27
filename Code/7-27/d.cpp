#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000;
const double eps = 1e-8;
int T, n, B;
double dx;

priority_queue<double, vector<double>, greater<double> > hp;

struct file {
	int S, p;
} a[maxn];

bool cmp_a(const file &pp, const file &qq) {
	return pp.S < qq.S || pp.S == qq.S && pp.p > qq.p;
}

int main() {
	int testcase = 0;
	while (scanf("%d%d%d", &T, &n, &B) != EOF) {
		if (T == 0) return 0;
		for (int i = 1; i <= T; ++i) {
			scanf("%lf%d", &dx, &a[i].p);
			a[i].S = round(dx * 100 + eps);
		}
		
		sort(a + 1, a + T + 1, cmp_a);
		while (!hp.empty()) hp.pop();
		int j = 1;
		double nowT = 0.0, sum = 0.0, Time = 0.0;
		for (; j <= T && j <= n; ++j) {
			hp.push(1.0 * a[j].S * (100 - a[j].p) / 10000);
			//cout << a[j].S << " " << a[j].p << " " << 1.0 * a[j].S * (100 - a[j].p) / 10000 << endl;
		}
		while (!hp.empty()) {
			double nowv = 1.0 * B / hp.size(), newT = (hp.top() - sum) / nowv;
			sum += nowv * newT;
			//cout << nowT << " " << newT << " " << sum << endl;
			hp.pop();
			if (j <= T) {
				hp.push(1.0 * a[j].S * (100 - a[j].p) / 10000 + sum);
				++j;
			}
			nowT += newT;
		}
		printf("Case %d: %.2f\n\n", ++testcase, nowT);
	}
}
