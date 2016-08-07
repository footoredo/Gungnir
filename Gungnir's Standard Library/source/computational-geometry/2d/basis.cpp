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
