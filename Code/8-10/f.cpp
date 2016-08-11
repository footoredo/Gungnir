#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;

const int MAXD = 64;
const LL MAXN = 1e18;
//const int MAXD = 3;
LL b[MAXD], A[MAXD], B[MAXD];
int n;

LL calc(int i, LL x) {
	if (x <= 0) return 0;
	if (i > 62) return 0;
	LL tmp = (LL)1 << i;
	LL tmp2 = (x + 1) % (tmp * (LL)2);
	//cout << tmp << " " << tmp2 << " " << i << endl;
	if (tmp2 > tmp) return (x + 1) / (tmp * (LL)2) * tmp + tmp2 - tmp;
	else return (x + 1) / (tmp * (LL)2) * tmp;
//cout << i << " " << tmp << " " << (x + 1) / (tmp * (LL)2) * tmp << " " << max((LL)0, (x + 1) % (tmp * (LL)2) - tmp) << endl;
	//return (x + 1) / (tmp * (LL)2) * tmp + max((LL)0, (x + 1) % (tmp * (LL)2) - tmp);
}

bool check(LL L, LL R) {
//cout << calc(1, 4) << endl;
//return 0;
	if (L) L--;
	for (int i = 0; i < MAXD; ++i) {
		//cout << i << " " << L << " " << R << " " << calc(i, R) << " " <<  calc(i, L) << " " << b[i] << endl;
		if (calc(i, R) - calc(i, L) != b[i]) return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	while (cin >> n, n) {
		memset(b, 0, sizeof(b));
		for (int i = 0; i < n; ++i) cin >> b[i];
		int cnt = 0;
		//for (LL l = b[0] * 2 - 1; l <= b[0] * 2 + 1; ++l) {
		LL temp = b[0] * 2, LLL, RRR;
		if (temp > 0) LLL = temp - 1; else LLL = temp;
		if (temp < MAXN) RRR = temp + 1; else RRR = temp;
		for (LL l = LLL; l <= RRR; ++l) {
			LL base = 0;
			bool flag = false;
			for (int i = MAXD - 1; i >= 0; --i) {
			//cout << i << " " << b[i] << " " << base << endl;
				if (b[i] == 0) continue;
				if (b[i] >= l) {
					base += (LL)1 << i;
					continue;
				}
				LL tmp = base + ((LL)1 << i) + b[i] - 1;
				//cout << tmp - l + 1 << " " << tmp << endl;
				if (tmp + 1 - l > (LL)0 && tmp <= MAXN && check(tmp + 1 - l, tmp)) {
					++cnt;
					A[cnt] = tmp + 1 - l;
					B[cnt] = tmp;
				}
				flag = true;
				break;
			}
			if (!flag && base && base + l - 1 <= MAXN && check(base, base + l - 1)) {
				++cnt;
				A[cnt] = base;
				B[cnt] = base + l - 1;
			}
		}
		//cout << A[1] << " " << B[1] << " " << endl;
		//cout << A[2] << " " << B[2] << endl;
		if (cnt == 0) cout << "None" << endl;
		else {
			if (cnt > 1) cout << "Many" << endl;
			else cout << A[1] << " " << B[1] << endl;
		}
	}
}
