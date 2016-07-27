#include <bits/stdc++.h>

typedef double DB;
const DB eps = 1e-8, inf = 1e18;
__inline int sign(DB x) {
	return x < -eps ? -1 : (x > eps ? 1 : 0);
}
__inline DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

struct Point {
	DB x, y;
	__inline Point(): x(0), y(0) {}
	__inline Point(DB _x, DB _y): x(_x), y(_y) {}
	__inline void read() {
		std::cin >> x >> y;
	}
	__inline void print() {
		std::cout << x << " " << y;
	}
	__inline DB sqrlen() const {
		return x * x + y * y;
	}
	__inline Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	__inline Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	__inline Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
	__inline Point operator/(DB k) const {
		return Point(x / k, y / k);
	}
	__inline friend DB dot(const Point& a, const Point& b) {
		return a.x * b.x + a.y * b.y;
	}
	__inline friend DB det(const Point& a, const Point& b) {
		return a.x * b.y - a.y * b.x;
	}
	__inline bool operator<(const Point& rhs) const {
		return !sign(x - rhs.x) ? y < rhs.y : x < rhs.x;
	}
	__inline bool operator>(const Point& rhs) const {
		return !sign(x - rhs.x) ? y > rhs.y : x > rhs.x;
	}
	__inline bool operator==(const Point& rhs) const {
		return !sign(x - rhs.x) && !sign(y - rhs.y);
	}
};

Point isLL(Point a, Point b, Point c, Point d) {
	DB s1 = det(d - c, a - c), s2 = -det(d - c, b - c);
	return (a * s2 + b * s1) / (s1 + s2);
}

__inline void clear(std::vector<Point>& v) {
	v.clear();
	std::vector<Point>(v).swap(v);
}

const int N = 111;

struct Convex {
	int n;
	std::vector<Point> a, upper, lower;
	void make_shell(const std::vector<Point>& p,
			std::vector<Point>& shell) {  // p needs to be sorted.
		clear(shell); int n = p.size(); 
		for (int i = 0, j = 0; i < n; i++, j++) {
			for (; j >= 2 && sign(det(shell[j-1] - shell[j-2],
							p[i] - shell[j-2])) <= 0; --j) shell.pop_back();
			//std::cout << i << " xxx " << j << std::endl;
			shell.push_back(p[i]);
		}
	}
	void print() {
		std::cout << "------------" << std::endl;
		for (std::vector<Point>::iterator it = a.begin(); it != a.end(); it++) {
			std::cout << it - a.begin() << ": ";
			it->print();
			std::cout << std::endl;
		}
		std::cout << "------------" << std::endl;
	}
	void make_convex() {
		//print();
		std::sort(a.begin(), a.end());
		make_shell(a, lower);
		std::reverse(a.begin(), a.end());
		make_shell(a, upper);
		a = lower; 
		//print();
		for (std::vector<Point>::iterator it = upper.begin(); it != upper.end(); it++)
			if (!(*it == *a.rbegin()) && !(*it == *a.begin()))
				a.push_back(*it);
		n = a.size();
	}
	void init(const std::vector<Point>& _a) {
		clear(a); a = _a; n = a.size();
		make_convex();
	}
	void read(int _n) {  // Won't make convex.
		clear(a); n = _n; a.resize(n);
		for (int i = 0; i < n; i++) 
			a[i].read();
	}
	std::pair<DB, int> get_tangent(
			const std::vector<Point>& convex, const Point& vec) {
		int l = 0, r = (int)convex.size() - 2;
		assert(r >= 0);
		for (; l + 1 < r; ) {
			int mid = (l + r) / 2;
			if (sign(det(convex[mid + 1] - convex[mid], vec)) > 0)
				r = mid;
			else l = mid;
		}
		return std::max(std::make_pair(det(vec, convex[r]), r),
				std::make_pair(det(vec, convex[0]), 0));
	}
	int binary_search(Point u, Point v, int l, int r) {
		int s1 = sign(det(v - u, a[l % n] - u));
		for (; l + 1 < r; ) {
			int mid = (l + r) / 2;
			int smid = sign(det(v - u, a[mid % n] - u));
			if (smid == s1) l = mid;
			else r = mid;
		}
		return l % n;
	}
	int get_tangent(Point vec) {
		std::pair<DB, int> ret = get_tangent(upper, vec);
		ret.second = (ret.second + (int)lower.size() - 1) % n;
		ret = std::max(ret, get_tangent(lower, vec));
		return ret.second;
	}
	bool get_intersection(Point u, Point v, int &i0, int &i1) {
		int p0 = get_tangent(u - v), p1 = get_tangent(v - u);
//		std::cout << "tangent: " << p0 << " " << p1 << std::endl;
		if (sign(det(v - u, a[p0] - u)) * sign(det(v - u, a[p1] - u)) <= 0) {
			if (p0 > p1) std::swap(p0, p1);
			i0 = binary_search(u, v, p0, p1);
			i1 = binary_search(u, v, p1, p0 + n);
			return true;
		}
		else return false;
	}
} people[N];

__inline void update(DB &ms, int &hit, Point p, Point vec, Point c, int j) {
	if (sign(dot(c - p, vec)) < 0) return;
	if ((c - p).sqrlen() < ms) {
		hit = j; ms = (c - p).sqrlen();
	}
}

__inline void update(DB &ms, int &hit, Point p, Point vec, int j, int i) {
	int n = people[j].n;
	Point p0 = people[j].a[i], p1 = people[j].a[(i+1)%n];
	if (!sign(det(vec, p1 - p0))) {
		update(ms, hit, p, vec, p0, j);
		update(ms, hit, p, vec, p1, j);
	}
	else update(ms, hit, p, vec, isLL(p, p + vec, p0, p1), j);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T--; ) {
		int n; std::cin >> n;
		for (int i = 0; i < n; i++) {
			int k; std::cin >> k;
			people[i].read(k); people[i].make_convex();
//			people[i].print();
		}

		int m; std::cin >> m;
		for (int i = 0; i < m; i++) {
			Point p, vec; p.read(); vec.read();
			DB min_sqrlen = inf;
			int hit = -1;
			for (int j = 0; j < n; j++) {
				int i0, i1;
				if (!people[j].get_intersection(p, p + vec, i0, i1))
					continue;
//				std::cout << "here" << std::endl;
				update(min_sqrlen, hit, p, vec, j, i0);
				update(min_sqrlen, hit, p, vec, j, i1);
				Point s0 = isLL(p, p + vec, people[j].a[i0], people[j].a[(i0+1)%people[j].n]);
				Point s1 = isLL(p, p + vec, people[j].a[i1], people[j].a[(i1+1)%people[j].n]);
				if (sign(dot(vec, s0 - p)) > 0 && (s0 - p).sqrlen() < min_sqrlen) {
					min_sqrlen = (s0 - p).sqrlen();
					hit = j;
				}
				if (sign(dot(vec, s1 - p)) > 0 && (s1 - p).sqrlen() < min_sqrlen) {
					min_sqrlen = (s1 - p).sqrlen();
					hit = j;
				}
			}

			if (~hit) std::cout << "HIT " << hit << std::endl;
			else std::cout << "MISS" << std::endl;
		}

		std::cout << "*****" << std::endl;
	}

	return 0;
}
