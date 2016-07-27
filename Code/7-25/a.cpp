#include <bits/stdc++.h>
using namespace std;

int num[22], l;
char buf[22];
long long f[20][1700][188];

long long calc(int p, int sumi, int sum, bool e) {
	long long &ff = f[p][sumi][sum];
	if (!e && ~ff) return ff;
	long long fff = 0;
	if (p == l) return fff = (sum == 0) ? sumi == 0 : (sumi % sum == 0);
	int limit = 10;
	if (e) limit = num[p];
	for (int i = 0; i < limit; i++) 
		fff += calc(p+1, sumi + p * i, sum + i, 0);
	if (e) fff += calc(p+1, sumi + limit * p, sum + limit, 1);
	if (!e) ff = fff;
	return fff;
}

long long solve(long long x) {
	if (x < 0) return 0;
	if (x == 0) return 1;
	l = 0;
	for (; x; x /= 10) num[l++] = x % 10;
	reverse(num, num + l);
	memset(f, -1, sizeof f);
	//cout << sizeof f << endl;
	return calc(0, 0, 0, 1);
}

int main() {
	int T; cin >> T;
	for (; T--; ) {
		long long x, y; cin >> x >> y; --x;
		cout << solve(y) - solve(x) << endl;
	}
	return 0;
}
