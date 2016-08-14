#include <bits/stdc++.h>
#define index INDEX
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

std::list<int> Q;
std::map<int, int> index;

std::list<int>::iterator findi(int u) {
	foreach(it, Q) if (*it == u) return it;
	return Q.end();
}

std::list<int>::iterator findu(int u) {
	if (!index.count(u)) return Q.end();
	return findi(index[u]);
}

void fl(std::list<int>::iterator it) {
	Q.erase(it);
	Q.push_front(*it);
}

const int N = 5555;
int ontop, p[N];
long long w[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T --; ) {
		int n; std::cin >> n;
		Q.clear(); index.clear();
		int cc = 0; ontop = -1;
		for (int op = 1; op <= n; ++ op) {
			std::cout << "Operation #" << op << ": ";
			std::string buf; std::cin >> buf;
			if (buf == "Add") {
				int u; std::cin >> u;
				if (index.count(u)) {
					std::cout << "same priority." << std::endl;
				}
				else {
					std::cout << "success." << std::endl;
					index[u] = cc; w[cc] = 0; p[cc] = u;
					Q.push_back(cc ++);
				}
			}
			else if (buf == "Close") {
				int u; std::cin >> u;
				if (!index.count(u)) {
					std::cout << "invalid priority." << std::endl;
				}
				else {
					int i = index[u];
					std::list<int>::iterator it = findi(i);
					if (it == Q.end()) {
						std::cout << "invalid priority." << std::endl;
					}
					else {
						std::cout << "close " << u << " with " << w[i] << "." << std::endl;
						Q.erase(it);
						if (u == ontop) {
							ontop = -1;
						}
						index.erase(u);
					}
				}
			}
			else if (buf == "Chat") {
				int _w; std::cin >> _w;
				if (!Q.size()) {
					std::cout << "empty." << std::endl;
				}
				else {
					int t = ~ontop ? ontop : *Q.begin();
					w[t] += _w;
					std::cout << "success." << std::endl;
				}
			}
			else if (buf == "Rotate") {
				int x; std::cin >> x;
				if (x < 1 || x > (int)Q.size()) {
					std::cout << "out of range." << std::endl;
				}
				else {
					std::list<int>::iterator it = Q.begin();
					for (int i = 1; i < x; ++ i) ++ it;
					fl(it);
					std::cout << "success." << std::endl;
				}
			}
			else if (buf == "Prior") {
				if (!Q.size()) {
					std::cout << "empty." << std::endl;
				}
				else {
					std::list<int>::iterator mit = Q.begin();
					foreach(it, Q) {
						if (p[*it] > p[*mit]) mit = it;
					}
					fl(mit);
					std::cout << "success." << std::endl;
				}
			}
			else if (buf == "Choose") {
				int u; std::cin >> u;
				if (index.count(u)) {
					int i = index[u];
					std::list<int>::iterator it = findi(i);
					if (it == Q.end()) {
						std::cout << "invalid priority." << std::endl;
					}
					else {
						fl(it);
						std::cout << "success." << std::endl;
					}
				}
				else std::cout << "invalid priority." << std::endl;
			}
			else if (buf == "Top") {
				int u; std::cin >> u;
				std::list<int>::iterator it = findu(u);
				if (it == Q.end()) {
					std::cout << "invalid priority." << std::endl;
				}
				else {
					ontop = index[u];
					std::cout << "success." << std::endl;
				}
			}
			else if (buf == "Untop") {
				if (~ontop) {
					ontop = -1;
					std::cout << "success." << std::endl;
				}
				else std::cout << "no such person." << std::endl;
			}
		}
		if (~ontop) {
			if (w[ontop]) std::cout << "Bye " << p[ontop] << ": " << w[ontop] << std::endl;
		}
		foreach(it, Q) {
			if (w[*it] && *it != ontop) std::cout << "Bye " << p[*it] << ": " << w[*it] << std::endl;
		}
		Q.clear();
	}

	return 0;
}

