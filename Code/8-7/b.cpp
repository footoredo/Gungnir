#include <bits/stdc++.h>
#define y1 Y1
#define y2 Y2
#define exit EXIT
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

const int N = 55555 * 4;
int W, H, n, m;
int x1[N], x2[N], y1[N], y2[N];

int pos[N], prv[N], cc;
struct CMP {
	__inline bool operator()(int x, int y) const {
		return pos[x] < pos[y]; 
	}
};
typedef std::set<int, CMP> S;
typedef S::iterator SIT;
S block;

__inline void clear(std::vector<int>& v) {
	v.clear();
	std::vector<int>(v).swap(v);
}

__inline void clear(S& s) {
	s.clear();
	S(s).swap(s);
}

std::vector<int> pool, enter[N], exit[N];

__inline int fd(int x) {
	return std::lower_bound(pool.begin(), pool.end(), x) - pool.begin();
}

__inline void eliminate(int sz, long long& cur) {
	if (sz >= m) cur -= sz - m + 1;
}

__inline void revive(int sz, long long& cur) {
	if (sz >= m) cur += sz - m + 1;
}

int label[N];
long long solve() {
	if (m > H) return 0;
	clear(pool);
	for (int i = 0; i < n; ++ i) {
		pool.push_back(x1[i]);
		pool.push_back(x2[i] + 1);
	}
	pool.push_back(W + 1); pool.push_back(1);
	std::sort(pool.begin(), pool.end());
	pool.erase(std::unique(pool.begin(), pool.end()), pool.end());
	for (int i = 0; i < (int)pool.size(); ++ i)
		clear(exit[i]);
	for (int i = 0; i < (int)pool.size(); ++ i)
		clear(enter[i]);

	for (int i = 0; i < n; ++ i) {
		enter[fd(x1[i])].push_back(i);
		exit[fd(x2[i] + 1)].push_back(i);
	}

	cc = 0;
	pos[cc] = H + 1; prv[cc] = H; 
	clear(block); block.insert(cc ++);
	long long ret = 0, cur = H - m + 1;
	for (int i = 0; i < (int)pool.size(); ++ i) {
		if (i) ret += cur * (pool[i] - pool[i - 1]);
//		std::cout << pool[i] << " " << cur << " " << ret << std::endl;
		foreach(it, exit[i]) {
			SIT t = block.lower_bound(label[*it]);
			SIT nxt = t; ++ nxt;
			eliminate(prv[*nxt], cur);
			eliminate(prv[*t], cur);
			revive(prv[*nxt] = prv[*nxt] + prv[*t] + 
					(y2[*it] - y1[*it] + 1), cur);
			block.erase(t);
		}
		foreach(it, enter[i]) {
			pos[cc] = y2[*it];
			SIT nxt = block.upper_bound(cc);
			pos[cc] = y1[*it];
			eliminate(prv[*nxt], cur);
			int s1, s2;
//			std::cout << "fff " << pos[*nxt] << " " << y2[*it] << std::endl; 
			revive(s1 = pos[*nxt] - y2[*it] - 1, cur);
			revive(s2 = prv[*nxt] - (y2[*it] - y1[*it] + 1) - s1, cur);
//			std::cout << "s1 " << s1 << " s2 " << s2 << std::endl;
			prv[*nxt] = s1;
			prv[cc] = s2;
			block.insert(label[*it] = cc ++);
		}
//		std::cout << "entered " << pool[i] << " " << cur << " " << ret << std::endl;
		
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (; std::cin >> W >> H >> n >> m; ) {
		for (int i = 0; i < n; ++ i)
			std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
		long long ans = solve();
		std::swap(W, H);
		for (int i = 0; i < n; ++ i) {
			std::swap(x1[i], y1[i]);
			std::swap(x2[i], y2[i]);
		}
		if (m != 1) ans += solve();
		std::cout << ans << std::endl;
	}

	return 0;
}
