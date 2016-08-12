#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

typedef long double DB;
const DB eps = 1e-8;
const DB PI = 3.14159265358979323846;

__inline int sign(DB x) {
	return x < -eps ? -1 : ( x > eps ? 1 : 0 );
}
__inline DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

struct Point {
	DB x, y;
	__inline Point(): x(0), y(0) {}
	__inline Point(DB x, DB y): x(x), y(y) {}
	__inline Point operator+(const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	__inline Point operator-(const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	__inline Point rotate(DB ang) const {
		return Point(cos(ang) * x - sin(ang) * y, 
				cos(ang) * y + sin(ang) * x);
	}
	__inline DB len2() const {
		return x * x + y * y;
	}
	__inline DB len() const {
		return msqrt(len2());
	}
	__inline void read() {
		std::cin >> x >> y;
	}
	__inline bool operator<(const Point& rhs) const {
		return sign(x - rhs.x) == 0 ? 
			sign(y - rhs.y) < 0 : sign(x - rhs.x) < 0;
	}
	__inline bool operator==(const Point& rhs) const {
		return sign(x - rhs.x) == 0 && sign(y - rhs.y) == 0;
	}
	__inline Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
} target;

__inline DB dot(const Point& a, const Point& b) {
	return a.x * b.x + a.y * b.y;
}

__inline DB det(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}

template <typename T>
__inline void clear(T& v) {
	v.clear();
	T(v).swap(v);
}

struct Convex {
	int n;
	std::vector<Point> a, upper, lower;
	void make_shell(const std::vector<Point>& p,
			std::vector<Point>& shell) {
		clear(shell); int n = p.size();
		for (int i = 0, j = 0; i < n; ++ i, ++ j) {
			for (; j >= 2 && (!sign(shell[j - 1].len2()) && sign(det(shell[j - 1] - shell[j - 2], p[i] - shell[j - 2])) < 0 || sign(shell[j - 1].len2()) && sign(det(shell[j - 1] - shell[j - 2], p[i] - shell[j - 2])) <= 0); -- j)
				shell.pop_back();
			shell.push_back(p[i]);
		}
	}
	void make_convex() {
		std::sort(a.begin(), a.end());
		make_shell(a, lower);
		std::reverse(a.begin(), a.end());
		make_shell(a, upper);
		a = lower; a.pop_back();
		a.insert(a.end(), upper.begin(), upper.end());
		if ((int)a.size() >= 2) a.pop_back();
		n = a.size();
	}
	void init(const std::vector<Point>& _a) {
		clear(a); a = _a; n = a.size();
		make_convex();
	}
} convex;

typedef std::vector<Point> Polygen;
__inline void rotate(Polygen& polygen, const Point& p, DB ang) {
	foreach(it, polygen) if (sign((*it - p).len2())) {
		*it = (*it - p).rotate(-ang) + p;
	}
}

bool isCL(Point o, DB rr, Point a, Point b, Point& p1, Point& p2) {
	DB x = dot(a - o, b - a),
	   y = (b - a).len2(),
	   d = x * x - y * ((a - o).len2() - rr);
	if (sign(d) < 0) return false;
	Point p = a - ((b - a) * (x / y)), 
		  delta = (b - a) * (msqrt(d) / y);
	p1 = p + delta, p2 = p - delta;
	return true;
}

bool onSeg(Point a, Point b, Point p) {
	return sign(det(p - a, b - a)) == 0 &&
		sign(dot(p - a, p - b)) <= 0;
}

DB get_ang(const Point& A, const Point& B) {
	DB tmp = atan2(A.y, A.x) - atan2(B.y, B.x);
	if (sign(tmp) < 0) tmp += 2 * PI;
	return tmp;
	DB costheta = dot(A, B) / A.len() / B.len();
	DB theta = acos(costheta);
	if (sign(det(A, B)) <= 0) return theta;
	else return 2 * PI - theta;
}

bool get_ang(const Point& O, const Point& A, 
		const Point& B, const Point& x, DB& ang) {
	Point p1, p2;
	if (!isCL(O, x.len2(), A, B, p1, p2)) return false;
	bool ret = false;
	ang = 20;
	if (onSeg(A, B, p1)) {
		ret = true;
		DB tmp = get_ang(p1 - O, x);
		ang = std::min(ang, tmp);
	}
	if (onSeg(A, B, p2)) {
		ret = true;
		DB tmp = get_ang(p2 - O, x);
		ang = std::min(ang, tmp);
	}
	return ret;
}

bool get_ang(const Polygen& polygen, const Point& p, DB& iang) {
//	std::cout << "get_ang " << p.x << " " << p.y << std::endl;
	int n = polygen.size();
	bool ret = false; iang = 20;
	for (int i = 0; i < n; ++ i) {
		if (sign((target - p).len2() - (polygen[i] - p).len2()) == 0) {
			ret = true;
			DB tmp = get_ang(polygen[i] - p, target - p);
			iang = std::min(tmp, iang);
		}
		DB tmp;
		if (get_ang(p, polygen[i], polygen[(i + 1) % n], target - p, tmp)) {
//			std::cout << "found " << polygen[i].x << " " << polygen[i].y << " " << tmp / PI * 180 << std::endl;
			ret = true;
			iang = std::min(iang, tmp);
		}
	}
	return ret;
}

int n;
Polygen polygen;

__inline DB get_ang(const Polygen& c, int p) {
	int nxt = (p + 1) % convex.n;
	Point vec = c[nxt];
	if (sign(vec.len2()) == 0) return 0;
	DB ang = get_ang(vec, Point(1, 0));
	return ang;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(2);
//	std::cout << get_ang(Point(1, sqrt(3)), Point(2, 0)) / PI * 180 << std::endl;

	for (int curT = 1; std::cin >> n, !std::cin.eof(); ++ curT) {
		clear(polygen); polygen.resize(n);
		for (int i = 0; i < n; ++ i)
			polygen[i].read();
		target.read();
		convex.init(polygen);		

//		std::cout << "-----------" << std::endl;
//		foreach(it, convex.a)
//			std::cout << "convex " << it->x << " " << it->y << std::endl;

		Point origin(0, 0);
		int p;
		for (p = 0; sign(convex.a[p].len2()); ++ p);
		int last = p;
		for (; !sign(convex.a[last].len2()); last = (last + convex.n - 1) % convex.n);
		Point vec = convex.a[last] - polygen[0];
//		std::cout << vec.x << " " << vec.y << std::endl;
		DB ang = get_ang(vec, Point(-1, 0));
		if (sign(ang) > 0) ang -= 2 * PI;
//		std::cout << ang / PI * 180 << std::endl;
		rotate(polygen, origin, ang);
//		foreach(it, polygen) std::cout << "Polygen: " << it->x << " " << it->y << std::endl;
		rotate(convex.a, origin, ang);
//		foreach(it, polygen) std::cout << "Polygen: " << it->x << " " << it->y << std::endl;
		DB x0 = 0;
		foreach(it, polygen) x0 = std::max(x0, it->x);
		Polygen shadow(polygen), c(convex.a);
//		std::cout << convex.n << std::endl;
//		std::cout << "p: " << p << std::endl;
		DB dis = 0;
		for (int _ = 0; _ < convex.n; ++ _) {
			DB ang = get_ang(c, p);
//			std::cout << "rotate " << _ << std::endl;
//			std::cout << "ang " << ang / PI * 180 << std::endl;
			rotate(shadow, origin, ang);
			rotate(c, origin, ang);
//			foreach(it, shadow) std::cout << "Polygen: " << it->x << " " << it->y << std::endl;
//			foreach(it, c) std::cout << "Convex: " << it->x << " " << it->y << std::endl;
			(++ p) %= convex.n;
			DB tmp_dis = c[p].x;
			dis += tmp_dis;
			foreach(it, shadow) it->x -= tmp_dis;
			foreach(it, c) it->x -= tmp_dis;
		}
		DB delta_x = dis;
//		std::cout << delta_x << std::endl;
		int rotate0 = int((target.x - x0) / delta_x);
//		std::cout << "rotate0: " << rotate0 << std::endl;
		DB ans = rotate0 * 2 * PI + ang;
		target.x -= rotate0 * delta_x;
//		foreach(it, polygen) it->x += rotate0 * delta_x;
//		foreach(it, convex.a) it->x += rotate0 * delta_x;
//		foreach(it, polygen) std::cout << "Polygen: " << it->x << " " << it->y << std::endl;
//		foreach(it, convex.a) std::cout << "Convex: " << it->x << " " << it->y << std::endl;
//		std::cout << ans / PI * 180 << std::endl;

//		std::cout << p << std::endl;
		bool found = false;
		for (; ; ) {
			DB ang = get_ang(convex.a, p), tmp;
//			std::cout << "rotate " << _ << std::endl;
//			std::cout << "xxxxxxxxxxxxxxx" << std::endl;
//			foreach(it, polygen) std::cout << "Polygen: " << it->x << " " << it->y << std::endl;
//			std::cout << convex.a[p].x << " " << convex.a[p].y << std::endl;
//			std::cout << "ang: " << ang / PI * 180 << std::endl;
//			std::cout << "ans: " << ans / PI * 180 << std::endl;
//			std::cout << "target: " << target.x << " " << target.y << std::endl;
			if (get_ang(polygen, convex.a[p], tmp)) {
//				std::cout << "tmp: " << tmp << std::endl;
//				assert(sign(tmp) >= 0);
				if (sign(tmp - ang) <= 0) {
					found = true;
					ans += tmp;
					break;
				}
			}

			DB back = 1e9;
			foreach(it, polygen) back = std::min(back, it->x);
			if (sign(back - target.x) > 0) break;
			
			rotate(polygen, origin, ang);
			rotate(convex.a, origin, ang);
			(++ p) %= convex.n;
			DB tmp_dis = convex.a[p].x;
			foreach(it, polygen) it->x -= tmp_dis;
			foreach(it, convex.a) it->x -= tmp_dis;
			target.x -= tmp_dis;
			ans += ang;
		}

		std::cout << "Case " << curT << ": ";
		if (found && n > 1) std::cout << ans / PI * 180 << std::endl;
		else std::cout << "Impossible" << std::endl;
	}
//	std::cout << get_ang(Point(0, -1), Point(0, 1)) << std::endl;

	return 0;
}
