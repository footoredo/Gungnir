typedef double DB;
const DB eps = 1e-8;

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
	__inline Point operator*(DB k) const {
		return Point(x * k, y * k);
	}
	__inline Point operator/(DB k) const {
		assert(sign(k));
		return Point(x / k, y / k);
	}
};

__inline DB dot(const P& a, const P& b) {
	return a.x * b.x + a.y * b.y;
}

__inline DB det(const P& a, const P& b) {
	return a.x * b.y - a.y * b.x;
}
