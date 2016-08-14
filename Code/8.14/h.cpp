#include <bits/stdc++.h>
typedef long double DB;
const DB eps = 1e-8;

const int N = 222;
struct Point {
	int x, y, z;
	__inline Point() {}
	__inline Point(int x, int y, int z): x(x), y(y), z(z) {}
	__inline Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	__inline Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	__inline long long len2() const {
		return 1LL * x * x + 1LL * y * y + 1LL * z * z;
	}
	__inline DB len() const {
		return sqrt(len2());
	}
	__inline void read() {
		std::cin >> x >> y >> z;
	}
	__inline bool operator<(const Point& rhs) const {
		if (x == rhs.x)
			if (y == rhs.y)
				return z < rhs.z;
			else return y < rhs.y;
		else return x < rhs.x;
	}
	__inline void print() const {
		std::cout << x << " " << y << " " << z << std::endl;
	}
} p[N];

std::multiset<Point> hash_p;
std::vector<std::pair<long long, int> > plane;
long long count4 = 0, count6 = 0;

__inline int getint(DB x) {
	if (x > eps) return int(x + eps);
	else if (x < -eps) return int(x - eps);
	else return 0;
}

Point rotate(const Point& s, const Point& axis, DB w) {
	DB x = axis.x, y = axis.y, z = axis.z;
	DB s1 = x * x + y * y + z * z;
	DB a[4][4], c[4] = {s.x, s.y, s.z, 1};
	memset(a, 0, sizeof a);
	a[3][3] = 1;
	a[0][0] = ((y * y + z * z) * cos(w) + x * x) / s1;
	a[0][1] = x * y * (1 - cos(w)) / s1 + z * sin(w) / sqrt(s1);
	a[0][2] = x * z * (1 - cos(w)) / s1 - y * sin(w) / sqrt(s1);
	a[1][0] = x * y * (1 - cos(w)) / s1 - z * sin(w) / sqrt(s1);
	a[1][1] = ((x * x + z * z) * cos(w) + y * y) / s1;
	a[1][2] = y * z * (1 - cos(w)) / s1 + x * sin(w) / sqrt(s1);
	a[2][0] = x * z * (1 - cos(w)) / s1 + y * sin(w) / sqrt(s1);
	a[2][1] = y * z * (1 - cos(w)) / s1 - x * sin(w) / sqrt(s1);
 	a[2][2] = ((x * x + y * y) * cos(w) + z * z) / s1;
	DB ans[4] = {0, 0, 0, 0};
	for (int i = 0; i < 4; ++ i)
		for (int j = 0; j < 4; ++ j)
			ans[i] += a[j][i] * c[j];
	//std::cout << ans[0] << " " << ans[1] << " " << ans[2] << std::endl;
	return Point(getint(ans[0]), getint(ans[1]), getint(ans[2]));
}

void solve(int l, int r, Point mid, Point A, Point B) {
	int tcount4 = (r - l + 1) * (r - l + 1);
	DB a = sqrt(plane[l].first), h = sqrt(3) * a / 2;
	DB sina = a / 2 / h;
	DB alpha = 2 * asin(sina);
	Point axis = A - B;
	long long len = plane[l].first;
	//if ((A-B).len2() != len) return;
	//std::cout << alpha / acos(-1) * 180 << std::endl;
	for (int i = l; i <= r; ++ i) {
		int index = plane[i].second;
		Point vec = p[index] - mid;
		Point vect = rotate(vec, axis, alpha);
		Point nxt = mid + vect;

//		std::cout << "vec "; vec.print(); 
//		std::cout << "vect "; vect.print(); 
//		std::cout << "p "; p[index].print(); 
//		std::cout << "nxt "; p[index].print();
		tcount4 -= hash_p.count(mid - vec);
		tcount4 -= hash_p.count(p[index]);

		if (((A-B).len2() == len) && (nxt - A).len2() == len && 
				(nxt - B).len2() == len &&
				(nxt - p[index]).len2() == len) {
			count6 += hash_p.count(nxt);
		}
	}
	count4 += tcount4 / 2;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		int n; std::cin >> n;
		hash_p.clear();
		for (int i = 0; i < n; ++ i) {
			p[i].read();
			p[i].x *= 2; p[i].y *= 2; p[i].z *= 2;
			hash_p.insert(p[i]);
		}

		count4 = 0; count6 = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < i; ++ j) {
				plane.clear();
				Point mid = p[i] + p[j];
				mid.x /= 2; mid.y /= 2; mid.z /= 2;
				for (int k = 0; k < n; ++ k)
					if (i != k && j != k) {
						if ((p[k] - p[i]).len2() == (p[k] - p[j]).len2()) {
							plane.push_back(std::make_pair((p[k] - p[i]).len2(), k));
						}
					}
				std::sort(plane.begin(), plane.end());
				int m = plane.size(), last = 0;
				for (int k = 0; k <= m; ++ k) {
					if (k == m || k && plane[k].first != plane[k - 1].first) {
						solve(last, k - 1, mid, p[i], p[j]);
						last = k;
					}
				}
			}
		std::cout << "Case #" << curT << ": ";
		//std::cout << "count4: " << count4 << " count6: " << count6 << std::endl;
		std::cout << (count4 - count6) / 2 + count6 / 6 << std::endl;
	}

	return 0;
}

