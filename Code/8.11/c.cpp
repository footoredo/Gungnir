#include <bits/stdc++.h>
#define index INDEX
#define foreach(it, v) for (__typeof((v).begin())it = (v).begin(); it != (v).end(); ++ it)

const int N = 111111, maxn = 100000;
int pool[N], cp, cnt[N], u[N];
long long cnt_mult[N], cnt_s[N];
int A[N];

int p[N], pp, is_prime[N], cnt_pf[N], mp[N];
std::vector<int> fac[N];
void eratos(int maxn) {
	memset(is_prime, true, sizeof is_prime);
	is_prime[1] = false; u[1] = 1;
	fac[1].push_back(1);
	for (int i = 2; i <= maxn; ++ i) {
		if (is_prime[i]) {
			p[pp ++] = i;
			cnt_pf[i] = 1;
			u[i] = -1;
		}
		else {
			cnt_pf[i] = cnt_pf[fac[i][0]] + cnt_pf[i / fac[i][0]];
			if (i / mp[i] % mp[i] == 0) u[i] = 0;
			else u[i] = -u[i / mp[i]];
		}
//		if (i <= 10) std::cout << "u " << i << " " << u[i] << std::endl;
//		fac[i].push_back(i);
//		fac[i].push_back(1);
		for (int j = i + i; j <= maxn; j += i) {
			if (is_prime[i]) mp[j] = i;
			is_prime[j] = false;
			if (!fac[j].size()) fac[j].push_back(i);
		}
	}
}

int index[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	eratos(100000);
	int T; std::cin >> T;
	for (; T --; ) {
		int n; std::cin >> n;
		cp = 0;
		memset(cnt, 0, sizeof cnt);
		memset(cnt_mult, 0, sizeof cnt_mult);
		memset(cnt_s, 0, sizeof cnt_s);
		memset(index, -1, sizeof index);
		for (int i = 0; i < n; ++ i) {
			std::cin >> A[i];
			++ cnt[A[i]];
		}

		for (int i = 1; i <= maxn; ++ i) {
			for (int j = i; j <= maxn; j += i)
				cnt_mult[i] += cnt[j];
		}

		for (int i = 2; i <= maxn; ++ i) if (cnt_mult[i]) {
//			if (i <= 10) std::cout << i << " " << cnt_mult[i] << std::endl;
			for (int j = i; j <= maxn; j += i)
				cnt_s[j] += -u[i] * cnt_mult[i];
		}
		cnt_s[1] = cnt[1];

		long long ans = 1LL * n * (n - 1) * (n - 2) / 3 / 2;
		long long tmp = 0;

		for (int i = 0; i < n; ++ i) {
			tmp += (cnt_s[A[i]] - 1) * (n - cnt_s[A[i]]);
//			std::cout << A[i] << " " << (cnt_s[A[i]] - 1) * (n - cnt_s[A[i]]) << std::endl;
		}

//		std::cout << ans << " " << tmp << std::endl;
		std::cout << ans - tmp / 2 << std::endl;
	}

	return 0;
}
