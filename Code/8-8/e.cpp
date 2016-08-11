#include <bits/stdc++.h>

const int N = 555;
std::map<std::string, int> var;
std::string eq_s[N][2], target;
int eq[N][2];
int cc;
template <typename T>
__inline void clear(T& container) {
	container.clear();
	T(container).swap(container);
}

int f[N][2222];
bool g[10];
int solve(int s, int i) {
	if (i >= (int)target.size()) return 0;
	if (~f[s][i]) return f[s][i];
	f[s][i] = 0;
	if (~eq[s][0]) {
		int l = solve(eq[s][0], i);
		f[s][i] = solve(eq[s][1], i + l) + l;
	}
	else {
		std::string &S = eq_s[s][0];
		for (int ii = 0; ii < (int)S.size() && f[s][i] + i < target.size(); ++ ii) {
			if (S[ii] == target[f[s][i] + i]) ++ f[s][i];
		}
	}
	//std::cout << s << " " << i << " " << f[s][i] << std::endl;
	return f[s][i];
}

int main() {
	int T; std::cin >> T;
	for (; T --; ) {
		int n; std::cin >> n;
		clear(var);
		for (int i = 0; i < n; ++ i) {
			char v1[10], v2[10], v3[10];
			scanf("%s = %s", v1, v2);
			
			var[std::string(v1)] = i;
			if (isupper(v2[0])) {
				scanf(" + %s", v3);
				eq_s[i][0] = std::string(v2);
				eq_s[i][1] = std::string(v3);
			}
			else {
				eq_s[i][0] = std::string(v2);
				eq_s[i][1] = "NONE";
			}
		}

		std::string start; std::cin >> start;
		std::cin >> target;
		for (int i = 0; i < n; ++ i) {
			memset(f[i], -1, sizeof(*f[i]) * (target.size() + 1));
			if (isupper(eq_s[i][0][0])) {
				eq[i][0] = var[eq_s[i][0]];
				eq[i][1] = var[eq_s[i][1]];
			}
			else {
				eq[i][0] = eq[i][1] = -1;
			}
		}
		std::cout << (solve(var[start], 0) == (int)target.size()
			? "YES" : "NO") << std::endl;
	}

	return 0;
}
