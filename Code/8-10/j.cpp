#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

const int N = 111111;
int l, d;
char str[3][N];
char all[52];
int cnt1[N], cnt2[3][N];

__inline bool check(int _d[3], int p) {
	int d[3];
	if (p == l) return _d[0] >= 0 && _d[1] >= 0 && _d[2] >= 0;
	else {
		for (int j = 0; j < 3; ++ j) {
			for (int k = 0; k < 3; ++ k)
				d[k] = _d[k] - cnt1[p];
			int a, b;
			if (j == 0) { a = 1; b = 2; }
			if (j == 1) { a = 0; b = 2; }
			if (j == 2) { a = 0; b = 1; }
			d[a] -= cnt2[a][p];
			d[b] -= cnt2[b][p];
			int t = std::min(cnt2[j][p], std::max(0, std::min(d[a], d[b])));
			d[a] -= t; d[b] -= t;
			d[j] -= cnt2[j][p] - t;
			int sum = 0;
			for (int k = 0; k < 3; ++ k)
				if (d[k] < 0) sum += -d[k];
			if (sum <= cnt1[p]) return true;
		}
	}
	return false;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (int i = 0; i < 26; ++ i) all[i] = i + 'A';
	for (int i = 0; i < 26; ++ i) all[i + 26] = i + 'a';

	for (; std::cin >> l >> d, l || d; ) {
		std::cin >> str[0] >> str[1] >> str[2];
		cnt1[l] = cnt2[0][l] = cnt2[1][l] = cnt2[2][l] = 0;
		for (int i = l - 1; i >= 0; -- i) {
			cnt1[i] = cnt1[i + 1];
			cnt2[0][i] = cnt2[0][i + 1];
			cnt2[1][i] = cnt2[1][i + 1];
			cnt2[2][i] = cnt2[2][i + 1];
			std::vector<char> tmp;
			for (int j = 0; j < 3; ++ j)
				tmp.push_back(str[j][i]);
			std::sort(tmp.begin(), tmp.end());
			tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
			if ((int)tmp.size() == 3) ++ cnt1[i];
			else if ((int)tmp.size() == 2) {
				if (str[0][i] == str[1][i]) ++ cnt2[2][i];
				if (str[0][i] == str[2][i]) ++ cnt2[1][i];
				if (str[2][i] == str[1][i]) ++ cnt2[0][i];
			}
		}

		int dr[3] = {d, d, d};
		bool fail = false;
		for (int i = 0; i < l; ++ i) {
			std::set<char> decision;
			for (int j = 0; j < 3; ++ j)
				if (!decision.count(str[j][i]))
					decision.insert(str[j][i]);
			for (int j = 0; j < 52; ++ j)
				if (!decision.count(all[j])) {
					decision.insert(all[j]);
					break;
				}
			bool succ = false;
			foreach(it, decision) {
				for (int j = 0; j < 3; ++ j)
					if (*it != str[j][i]) -- dr[j];
				if (check(dr, i + 1)) {
					succ = true;
					std::cout << *it;
					break;
				}
				for (int j = 0; j < 3; ++ j)
					if (*it != str[j][i]) ++ dr[j];
			}
			if (!succ) {
				fail = true;
				break;
			}
		}

		if (fail) std::cout << -1 << std::endl;
		else std::cout << std::endl;
	}

	return 0;
}
