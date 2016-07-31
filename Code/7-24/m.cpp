#include <bits/stdc++.h>
#define foreach(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++ it)

const int N = 2222;
int n, m, k;
typedef std::pair<int, int> Point;
Point point[N];
int container[N];
std::list<Point> table;
typedef std::list<Point>::iterator lit;
lit where[N];

template <typename T>
__inline void clear(T &a) {
	a.clear(); T(a).swap(a);
}

__inline bool cmpY(int a, int b) {
	return point[a].second < point[b].second;
}

__inline bool cmpY_point(const Point& a, const Point& b) {
	return a.second < b.second;
}

int p[4], up, middle, down;

int calc(int i, int j) {
	Point tmp[4]; tmp[0] = point[i]; tmp[1] = point[j];
	int cc = 2;

	if (point[j].second > point[i].second) {
		lit it = where[j];
		if (++it != table.end() && it->second == point[j].second) return 0;
		it = where[i];
		if (--it != table.end() && it->second == point[i].second) return 0;
		int c = 0;
		for (it = where[i]; ++ it != where[j] && c < middle; ++ c) {
			tmp[cc ++] = *it;
		}
//		std::cout << c << " " << middle << std::endl;
		if (c == middle && it == where[j]) {
			c = 0;
			for (it = where[j]; ++ it != table.end() && c < down; ++ c) {
				tmp[cc ++] = *it;
			}
			if (c == down && (it == table.end() || 
						!(down && it != table.end() && 
						it->second == tmp[cc - 1].second)) ) {
//				std::cout << "up" << std::endl;
				c = 0;
				for (it = where[i]; -- it != table.end() && c < up; ++ c) {
					tmp[cc ++] = *it;
				}
				if (c == up && (it == table.end() || 
							!(up && it != table.end() && 
							it->second == tmp[cc - 1].second)) ) { 
					assert(cc == 4);
					if (tmp[2].first > tmp[3].first) std::swap(tmp[2], tmp[3]);
					if (tmp[2].second >= tmp[3].second && p[1] < p[2] ||
							tmp[2].second <= tmp[3].second && p[1] > p[2])
						return 0;
					sort(tmp, tmp + cc, cmpY_point);
//					std::cout << "xxx" << std::endl;
					bool valid = 1;
					for (int _ = 1; _ < 4 && valid; ++ _)
						if (tmp[_].second == tmp[_ - 1].second) valid = 0;
					if (valid) sort(tmp, tmp + cc);
					for (int _ = 1; _ < 4 && valid; ++ _)
						if (tmp[_].first == tmp[_ - 1].first) valid = 0;
					return valid;
				}
			}
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T--; ) {
		std::cin >> n >> m >> k;
		std::cin >> p[0] >> p[1] >> p[2] >> p[3];
		up = std::min(p[0], p[3]) - 1;
		middle = std::max(p[0], p[3]) - std::min(p[0], p[3]) - 1;
		down = 4 - std::max(p[0], p[3]);
		for (int i = 0; i < k; ++ i)
			std::cin >> point[i].first >> point[i].second;

		sort(point, point + k);
		long long ans = 0;
		for (int i = 0 ; i < k; ++ i) {
			clear(table);
			int cc = 0;
			for (int j = k - 1; j >= 0 && point[j].first >= point[i].first; -- j)
				container[cc++] = j;
			std::sort(container, container + cc, cmpY);
			for (int *it = container; it < container + cc; ++ it)
				where[*it] = table.insert(table.end(), point[*it]);

			for (int j = k - 1; point[j].first > point[i].first; -- j) {
				if (p[0] < p[3]) ans += calc(i, j);
				else ans += calc(j, i);
				if (j > i && point[j].first > point[j - 1].first)
					for (int _ = j; _ < k && point[_].first == point[j].first; ++ _)
						table.erase(where[_]);
			}
		}

		std::cout << ans << std::endl;
	}

	return 0;
}
