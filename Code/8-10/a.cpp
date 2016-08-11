#include <bits/stdc++.h>

const int N = 555;
bool lt[26][26];
char words[N][22];
int n;
bool boom, vis[26], instk[26];

void dfs(int u) {
	vis[u] = true; instk[u] = true;
	for (int i = 0; i < 26; ++ i)
		if (lt[u][i]) {
			if (vis[i]) if (instk[i]) boom = true; else;
			else dfs(i);
		}
	instk[u] = false;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (; std::cin >> n, n; ) {
		memset(lt, 0, sizeof lt);
		boom = false;
		for (int i = 0; i < n; ++ i) {
			std::cin >> words[i];
			if (i) {
				bool eq = true;
				int len = std::min(strlen(words[i - 1]), strlen(words[i]));
				for (int j = 0; j < len; ++ j) {
					if (words[i - 1][j] != words[i][j]) {
						lt[words[i - 1][j] - 'a'][words[i][j] - 'a'] = true;
						eq = false; break;
					}
				}
				if (eq && strlen(words[i]) < strlen(words[i - 1]))
					boom = true;
			}
		}

		if (!boom) {
			memset(vis, 0, sizeof vis);
			memset(instk, 0, sizeof instk);
			for (int i = 0; i < 26; ++ i)
				if (!vis[i]) dfs(i);
		}

		std::cout << (boom ? "no" : "yes") << std::endl;
	}

	return 0;
}
