#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB eps = 1e-8;

__inline int sign(DB x) {
	return x < -eps ? -1 : ( x > eps ? 1 : 0 );
}

__inline DB msqrt(DB x) {
	return sign(x) > 0 ? sqrt(x) : 0;
}

struct P {
	DB x, y;
	__inline P(): x(0), y(0) {}
	__inline P(DB _x, DB _y): x(_x), y(_y) {}
	__inline DB length() {
		return msqrt(x*x + y*y);
	}
	__inline P operator+(const P& rhs) const {
		return P(x + rhs.x, y + rhs.y);
	}
	__inline P operator-(const P& rhs) const {
		return P(x - rhs.x, y - rhs.y);
	}
	__inline P operator*(DB k) const {
		return P(x * k, y * k);
	}
	__inline P rotate(DB a) const {
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	__inline void read() {
		cin >> x >> y;
	}
	__inline void print(char term = '\n') const {
		printf("%.3f %.3f%c", (double)(x), (double)(y), term);
	}
};

__inline DB dot(const P& a, const P& b) {
	return a.x * b.x + a.y * b.y;
}

__inline DB det(const P& a, const P& b) {
	return a.x * b.y - a.y * b.x;
}

__inline DB dist(const P& a, const P& b, const P& c) {
	return abs(det(a - c, b - c) / (a - b).length());
}

__inline bool in_the_seg(const P& a, const P& b, const P& c) {
	if (sign(dist(a, b, c))) return 0;
	return sign(dot(a - c, b - c)) <= 0;
}

__inline bool seg_intersect(const P& a, const P& b, const P& c, const P& d, P& e) {
	DB s1 = det(c - a, d - a);
	DB s2 = det(d - b, c - b);
	if (!sign(s1 + s2)) return 0;
	e = (b - a) * (s1 / (s1 + s2)) + a;
	return in_the_seg(a, b, e) && in_the_seg(c, d, e);
}

P tri[3];
DB u;
const DB pi = acos(-1);

struct Laser {
	P p, v;
	__inline Laser() {}
	__inline Laser(const P& _p, const P& _v): p(_p), v(_v) {}
	__inline Laser reflect(const P& A, const P& B, DB k = 1) {
		//A.print(); B.print();
		P far = p + v * 10000, o; assert(seg_intersect(p, far, A, B, o));
		P normal = (B-A).rotate(-k*pi/2);
		//printf("normal: "); normal.print();
		DB sin0 = det(v, normal) / v.length() / normal.length();
		DB sin1 = sin0 / u;
		DB theta = asin(sin1);
		P vv = normal.rotate(-theta);
		return Laser(o + vv*eps, vv);
	}
	__inline int fd() {
		DB l = 0, r = 10000;
		for (int i = 0; i < 50; i++) {
			DB m = (l + r) / 2.0;
			int tmp = 0; P far = p + v * m, e;
			for (int j = 0; j < 3; j++) {
				tmp += seg_intersect(p, far, tri[j], tri[(j+1)%3], e);
			}
			if (tmp >= 2) r = m; else l = m;
		}
		int ans = -1;
		P far = p + v * l, e;
		for (int j = 0; j < 3; j++)
			if (seg_intersect(p, far, tri[j], tri[(j+1)%3], e)) {
				ans = j; break;
			}
		return ans;
	}
	__inline void print() {
		p.print(' '); printf("-> "); v.print('\n');
	}
} laser;

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		laser.p.read(); P far; far.read(); laser.v = far - laser.p;
		for (int i = 0; i < 3; i++) tri[i].read();
		if (sign(det(tri[1]-tri[0], tri[2]-tri[1])) > 0) swap(tri[2], tri[1]);
		cin >> u;
		//printf("%.3f\n", u);
		DB k = 1;
		/*if (!~laser.fd()) {
			puts("Error"); continue;
		}*/
		for (int nxt; ~(nxt = laser.fd()); k *= -1, u = 1. / u) {
			//laser.print();
			//printf("nxt %d %d\n", nxt, (nxt+1)%3);
			laser = laser.reflect(tri[nxt], tri[(nxt+1)%3], k);
		}
		//laser.print();
		if (sign(laser.v.y) < 0) {
			DB k = laser.p.y / laser.v.y;
			DB ans = laser.p.x - laser.v.x * k;
			printf("%.3f\n", (double)(ans + eps));
		}
		else puts("Error");
	}
	
	return 0;
}
