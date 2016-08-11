#include <bits/stdc++.h>

template <typename T>
__inline void clear(T& container) {
	container.clear();
	T(container).swap(container);
}

__inline bool check(const std::vector<bool>& seq) {
	int n = seq.size();
	bool all_zero = 1;
	for (int i = 0; i < n; ++ i)
		all_zero &= seq[i] == 0;
	if (all_zero) return true;
	if (n == 3 || n == 1) return true;
	if (n % 2 == 0) return false;
	
	std::vector<bool> sub_seq[2];
	for (int i = 0; i < n; ++ i)
		sub_seq[i & 1].push_back(seq[i]);
	if (sub_seq[0].size() > sub_seq[1].size()) 
		std::swap(sub_seq[0], sub_seq[1]);
	for (int i = 0; i < sub_seq[0].size(); ++ i)
		sub_seq[1][i] = sub_seq[1][i] ^ sub_seq[1][i + 1];
	sub_seq[1].pop_back();
	bool ret = check(sub_seq[0]) && check(sub_seq[1]);
	clear(sub_seq[0]); clear(sub_seq[1]);
	return ret;
}

std::string buf;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T --; ) {
		std::cin >> buf;
		std::vector<bool> seq;
		for (int i = 0; i < (int)buf.size(); ++ i)
			seq.push_back(buf[i] == '1');
		std::cout << (check(seq) ? "DIES" : "LIVES") << std::endl;
		clear(seq);
	}

	return 0;
}
