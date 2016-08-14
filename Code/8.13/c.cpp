#include <bits/stdc++.h>
typedef long double DB;
const DB eps = 1e-6;

__inline int sign(DB x) {
	if (x < -eps) return -1;
	else if (x > eps) return 1;
	else return 0;
}

__inline DB msqrt(DB x) {
	if (sign(x) > 0) return sqrt(x);
	else return 0;
}

int n;
struct Point {
	DB x, y;
	__inline Point(): x(0), y(0) {}
	__inline Point(DB x, DB y): x(x), y(y) {}
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
	__inline DB len2() const {
		return x * x + y * y;
	}
	__inline DB len() const {
		return msqrt(len2());
	}
	__inline bool operator<(const Point& rhs) const {
		if (sign(x - rhs.x) == 0) return y < rhs.y;
		else return sign(x - rhs.x) < 0;
	}
	__inline bool operator==(const Point& rhs) const {
		return sign(x - rhs.x) == 0 && sign(y - rhs.y) == 0;
	}
	__inline void read() {
		std::cin >> x >> y;
	}
	__inline void print() const {
		std::cout << x << " " << y << std::endl;
	}
} ans;
bool found, multiple;

__inline DB dot(const Point& A, const Point& B) {
	return A.x * B.x + A.y * B.y;
}

__inline DB det(const Point& A, const Point& B) {
	return A.x * B.y - A.y * B.x;
}

const int N = 111;
struct Line {
	Point A, B;
	__inline Line() {}
	__inline Line(const Point& A, const Point& B): A(A), B(B) {}
	__inline void read() {
		A.read(); B.read();
	}
} line[N];

__inline DB disToLine(const Line& l, const Point& p) {
	return fabs(det(p - l.A, l.B - l.A) / (l.B - l.A).len());
}

__inline bool isLL(const Line& l1, const Line& l2, Point& p) {
	DB s1 = det(l2.B - l2.A, l1.A - l2.A),
	   s2 = -det(l2.B - l2.A, l1.B - l2.A);
	if (sign(s1 + s2) == 0) return false;
	p = Point(l1.A * s2 + l1.B * s1) / (s1 + s2);
	return true;
}

__inline std::pair<Line, Line> get_eq(const Line& l1, const Line& l2) {
	Point p;
	if (isLL(l1, l2, p)) {
		Point vec1 = (l1.B - l1.A);
		assert(sign(vec1.len()));
		Point vec2 = (l2.B - l2.A);
		assert(sign(vec2.len()));
		if (vec1.len2() > vec2.len2()) {
			vec2 = vec2 * vec1.len() / vec2.len();
		}
		else {
			vec1 = vec1 * vec2.len() / vec1.len();
		}
		Point A = p + vec1, B = p + vec2,
			  C = p - vec1, D = p - vec2;
		return std::make_pair(Line((A + B) / 2., (C + D) / 2.),
				Line((A + D) / 2., (B + C) / 2.));
	}
	else {
		Point s = (l1.A + l2.A) / 2.;
		Line l(s, s + l1.B - l1.A);
		return std::make_pair(l, l);
	}
}

__inline void add(const Point& p) {
	if (!found) { found = true; ans = p; }
	else if (!(ans == p)) {
		//std::cout << "xx "; p.print();
		multiple = true;
	}
}

__inline bool check(const Point& p) {
	DB dis = disToLine(line[0], p);
	for (int i = 1; i < n; ++ i)
		if (sign(dis - disToLine(line[i], p))) return false;
	return true;
}

__inline void get_eq(const Line& l1, const Line& l2, const Line& l3) {
	std::pair<Line, Line> x1 = get_eq(l1, l2), x2 = get_eq(l2, l3);
	Point p;
	std::vector<Point> ret;
	if (isLL(x1.first, x2.first, p) && check(p)) add(p);
	if (isLL(x1.first, x2.second, p) && check(p)) add(p);
	if (isLL(x1.second, x2.first, p) && check(p)) add(p);
	if (isLL(x1.second, x2.second, p) && check(p)) add(p);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(6);

	for (; std::cin >> n, n; ) {
		for (int i = 0; i < n; ++ i) line[i].read();
		found = multiple = false;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < i; ++ j)
				for (int k = 0; k < j; ++ k) 
					get_eq(line[i], line[j], line[k]);
		if (multiple || n <= 2) std::cout << "Many" << std::endl;
		else if (found) {
			ans.print();
		}
		else std::cout << "None" << std::endl;
	}
 
	return 0;
}
