#include <bits/stdc++.h>
using namespace std;

const int G[9][3] = {
	{0, 0, 0},
	{2, 3, 4},
	{1, 7, 5},
	{1, 5, 6},
	{1, 6, 7},
	{2, 8, 3},
	{3, 8, 4},
	{4, 8, 2},
	{5, 7, 6}
};

int pw[11], inter[11][11][11], a[11], cnt, used[11], id[11], temp[11111], x[111];
char str[111];
map<string, int> mp;
set<int> S;

int main() {
	pw[0] = 1;
	for (int i = 1; i <= 8; ++i) pw[i] = pw[i - 1] * 10;
	for (int i = 1; i <= 8; ++i)
		for (int j = 1; j <= 8; ++j) {
			if (i == j) continue;
			cnt = inter[i][j][0] = inter[i][j][1] = 0;
			memset(used, 0, sizeof(used));
			for (int k = 0; k < 3; ++k) used[G[i][k]]++;
			for (int k = 0; k < 3; ++k) used[G[j][k]]++;
			for (int k = 1; k <= 8; ++k)
				if (used[k] == 2) inter[i][j][cnt++] = k;
			//cout << i << " " << j << " " << inter[i][j][0] << " " << inter[i][j][1] << endl;
		}
	while (scanf("%s", str) != EOF) {
		mp.clear(); S.clear();
		int cnt = 0, ans = 0;
		for (int i = 1; i <= 8; ++i) {
			string s = string(str);
			if (mp.count(s)) a[i] = mp[s];
			else a[i] = mp[s] = ++cnt;
			if (i < 8) scanf("%s", str);
		}
		for (int i = 1; i <= 8; ++i) x[i] = i;
		do {
			cnt = 0;
			for (int i = 1; i <= 8; ++i) {
				id[1] = i;
				for (int j = 0; j < 3; ++j) {
					id[2] = G[i][j]; id[3] = G[i][(j + 1) % 3]; id[4] = G[i][(j + 2) % 3];
					memset(used, 0, sizeof(used));
					for (int k = 1; k <= 4; ++k) used[id[k]] = 1;
					used[0] = 1;
					for (int k = 2; k <= 4; ++k) {
						int l = (k == 4) ? 2 : k + 1;
						if (used[inter[id[k]][id[l]][0]] == 0) {
							used[inter[id[k]][id[l]][0]] = 1;
							id[k + 3] = inter[id[k]][id[l]][0];
						} else 
						if (used[inter[id[k]][id[l]][1]] == 0) {
							used[inter[id[k]][id[l]][1]] = 1;
							id[k + 3] = inter[id[k]][id[l]][1];
						}
					}
					for (int k = 1; k < 9; ++k)
						if (!used[k]) id[8] = k;
					int mask = 0;
					for (int k = 1; k <= 8; ++k) mask += pw[k - 1] * a[x[id[k]]];
					temp[++cnt] = mask;
				}
			}
			bool flag = true;
			for (int i = 1; i <= cnt; ++i)
				if (S.find(temp[i]) != S.end()) {
					flag = false;
					break;
				}
			if (flag) {
				ans++;
				//for (int i = 1; i <= 8; ++i) cout << a[x[i]] << " "; cout << endl;
				//for (int i = 1; i <= 8; ++i) cout << id[i] << " "; cout << endl;
				//for (int i = 1; i <= cnt; ++i) cout << temp[i] << " "; cout << endl;
				S.insert(temp[1]);
			}
		} while (next_permutation(x + 1, x + 9));
		printf("%d\n", ans);
	}
}
