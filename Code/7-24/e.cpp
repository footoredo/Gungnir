#include <bits/stdc++.h>
#define hash HASH

const int MODN = 1e9 + 7 + 1e-9;
const int N = 1111;

struct P {
	int x, y;
	__inline P(int x = 0, int y = 0): x(x), y(y) {}
	__inline P operator+(const P& rhs) {
		return P(x + rhs.x, y + rhs.y);
	}
	__inline P operator-(const P& rhs) {
		return P(x - rhs.x, y - rhs.y);
	}
	__inline void read() {
		std::cin >> x >> y;
	}
	__inline bool operator<(const P& rhs)  const{
		return x < rhs.x || x == rhs.x && y < rhs.y;
	}
	__inline bool operator==(const P& rhs)  const{
		return x == rhs.x && y == rhs.y;
	}
} p[N];

__inline long long dot(const P& a, const P& b) {
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}

__inline long long det(const P& a, const P& b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

int n, pw[N], count[N];

struct Dir {
	int i, j;
	P d;
	__inline Dir() {}
	__inline Dir(int i, int j, P _d): i(i), j(j), d(_d) {
		int g = std::__gcd(d.x, d.y);
		//std::cout << "DDD " << i << " " << j << " " << d.x << " " << d.y << " " << g << std::endl; 
		d.x /= g; d.y /= g;
	}
	__inline bool operator<(const Dir& rhs) const ;
	__inline bool operator==(const Dir& rhs) const {
		return d == rhs.d;
	}
} dir[N*N];
int cd = 0;
std::map<P, int> hash;

__inline bool cmp(const Dir& a, const Dir& b) {
	return det(p[a.i], a.d) < det(p[b.i], b.d);
}

__inline bool Dir::operator<(const Dir& rhs) const {
	return d < rhs.d || d == rhs.d && cmp(*this, rhs);
}

int buf[N], cbuf;
bool appear[N];
int ans;
void solve(int l, int r) {
	//std::cout << "solving " << l << " " << r << std::endl;
	cbuf = 0;
	if (l == r) return;
	int j;
	for (j = l; j < r && !cmp(dir[l], dir[j]); j++) {
		if (!appear[dir[j].i]) {
			appear[dir[j].i] = 1;
			buf[cbuf++] = dir[j].i;
		}
		if (!appear[dir[j].j]) {
			appear[dir[j].j] = 1;
			buf[cbuf++] = dir[j].j;
		}
	}

	int sum = 0;
	for (int i = 0; i < cbuf; i++) {
		//std::cout << buf[i] << " ";
		sum += count[buf[i]];
		ans = (ans - pw[count[buf[i]]] + 1) % MODN;
		appear[buf[i]] = 0;
	}
	//std::cout << std::endl;
	//std::cout << sum << std::endl;
	ans = (ans + pw[sum] - 1) % MODN;
	solve(j, r);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	pw[0] = 1; for (int i = 1; i <= 1000; i++) pw[i] = 2 * pw[i-1] % MODN; 

	int T; std::cin >> T;
	for (; T--; ) {
		hash.clear();
		int n, cc = 0; std::cin >> n;
		for (int i = 1; i <= n; i++) {
			P tmp; tmp.read();
			if (hash[tmp]) ++count[hash[tmp]];
			else {
				hash[tmp] = ++cc;
				p[cc] = tmp; count[cc] = 1;
			}
		}

		cd = 0;
		for (int i = 1; i <= cc; i++)
			for (int j = 1; j <= cc; j++) {
				P delta = p[j] - p[i];
				if (delta.x > 0 || delta.x == 0 && delta.y > 0) {
					dir[cd++] = Dir(i, j, delta);
				}
			}

		std::sort(dir, dir + cd);
		ans = 0;
		for (int i = 0; i < cd; ) {
			int j; 
			for (j = i; j < cd && dir[i] == dir[j]; j++) {
				//std::cout << "dir " << dir[j].d.x << " " << dir[j].d.y << " " << dir[j].i << " " << dir[j].j << std::endl;
			}
			solve(i, j);

			i = j;
		}

		//std::cout << "cc " << cc << std::endl;
		//std::cout << count[1] << std::endl;
		for (int i = 1; i <= cc; i++) ans = (ans + pw[count[i]] - count[i] - 1) % MODN;
		std::cout << (ans + MODN) % MODN << std::endl;
	}


	return 0;
}
