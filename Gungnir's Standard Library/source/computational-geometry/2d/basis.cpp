typedef double DB;
const DB eps = 1e-8;

int sign(DB x) {
	return x < -eps ? -1 : ( x > eps ? 1 : 0 );
}
DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

struct Point {
	DB x, y;
	Point(): x(0), y(0) {}
	Point(DB x, DB y): x(x), y(y) {}
	Point operator+(const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
	Point operator/(DB k) const {
		assert(sign(k));
		return Point(x / k, y / k);
	}
	Point rotate(DB ang) const {  // 逆时针旋转 ang 弧度
		return Point(cos(ang) * x - sin(ang) * y, 
				cos(ang) * y + sin(ang) * x);
	}
	Point turn90() const {  // 逆时针旋转 90 度
		return Point(-y, x);
	}
};
DB dot(const Point& a, const Point& b) {
	return a.x * b.x + a.y * b.y;
}
DB det(const Point& a, const Point& b) {
	return a.x * b.y - a.y * b.x;
}
bool isLL(const Line& l1, const Line& l2, Point& p) {  // 直线与直线交点
	DB s1 = det(l2.b - l2.a, l1.a - l2.a),
	   s2 = -det(l2.b - l2.a, l1.b - l2.a);
	if (!sign(s1 + s2)) return false;
	p = (l1.a * s2 + l1.b * s1) / (s1 + s2);
	return true;
}
bool onSeg(const Line& l, const Point& p) {  // 点在线段上
	return sign(det(p - l.a, l.b - l.a)) == 0 && sign(dot(p - l.a, p - l.b)) <= 0;
}
DB disToLine(const Line& l, const Point& p) {  // 点到直线距离
	return fabs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
DB disToSeg(const Line& l, const Point& p) {  // 点到线段距离
	return sign(dot(p - l.a, l.b - l.a)) * sign(dot(p - l.b, l.a - l.b)) == 1 ? disToLine(l, p) : std::min((p - l.a).len(), (p - l.b).len());
}
// 圆与直线交点
bool isCL(Circle a, Line l, Point& p1, Point& p2) {
	DB x = dot(l.a - a.o, l.b - l.a),
	   y = (l.b - l.a).len2(),
	   d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
	if (sign(d) < 0) return false;
	Point p = l.a - ((l.b - l.a) * (x / y)), delta = (l.b - l.a) * (msqrt(d) / y);
	p1 = p + delta; p2 = p - delta;
	return true;
}
// 求凸包
std::vector<Point> convexHull(std::vector<Point> ps) {
	int n = ps.size(); if (n <= 1) return ps;
	std::sort(ps.begin(), ps.end());
	std::vector<Point> qs;
	for (int i = 0; i < n; qs.push_back(ps[i ++]))
		while (qs.size() > 1 && sign(det(qs[qs.size() - 2], qs.back(), ps[i])) <= 0)
			qs.pop_back();
	for (int i = n - 2, t = qs.size(); i >= 0; qs.push_back(ps[i --]))
		while ((int)qs.size() > t && sign(det(qs[qs.size() - 2], qs.back(), ps[i])) <= 0)
			qs.pop_back();
	return qs;
}
