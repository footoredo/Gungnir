#include <bits/stdc++.h>
typedef long double DB;
const DB eps = 1e-8;

__inline int sign(DB x) {
	if (x < -eps) return -1;
	else if (x > eps) return 1;
	else return 0;
}

__inline int sign(long long x) {
	if (x < 0) return -1;
	else if (x > 0) return 1;
	else return 0;
}

__inline DB msqrt(long long x) {
	if (sign(x) > 0) return sqrt(x);
	else return 0;
}

struct Point {
	long long x, y;
	__inline Point(): x(0), y(0) {}
	__inline Point(long long x, long long y): x(x), y(y) {}
	__inline Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	__inline Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	__inline long long len2() const {
		return x * x + y * y;
	}
	__inline DB len() const {
		return msqrt(len2());
	}
	__inline void read() {
		std::cin >> x >> y;
	}
	__inline void print() const {
		std::cout << x << " " << y << std::endl;
	}
};

__inline long long dot(const Point& A, const Point& B) {
	return A.x * B.x + A.y * B.y;
}

__inline long long det(const Point& A, const Point& B) {
	return A.x * B.y - A.y * B.x;
}

struct Line {
	Point A, B;
	__inline Line() {}
	__inline Line(const Point& A, const Point& B): A(A), B(B) {}
	__inline void read() {
		A.read(); B.read();
	}
};

__inline DB disToLine(const Line& l, const Point& p) {
	return fabs(det(p - l.A, l.B - l.A) / (l.B - l.A).len());
}

__inline DB disToSeg(const Line& l, const Point& p) {
//	l.A.print(); l.B.print(); p.print();
//	std::cout << "asdfsdf " << sign(dot(p - l.A, l.B - l.A)) * sign(dot(p - l.B, l.A - l.B)) << std::endl;
	return sign(dot(p - l.A, l.B - l.A)) * sign(dot(p - l.B, l.A - l.B)) == 1 ? disToLine(l, p) : std::min((p - l.A).len(), (p - l.B).len());
}

const int N = 1022, M = N * N * 2;
typedef std::vector<Point> Polygen;
Polygen p[N];
int W, n;

int cc, adj[N], v[M], nxt[M], e;
DB w[M];
__inline void ins(int u0, int v0, DB w0) {
//	std::cout << u0 << " " << v0 << " " << w0 << std::endl;
	v[e] = v0; nxt[e] = adj[u0]; w[e] = w0; adj[u0] = e ++;
}

DB d[N];
int Q[65536];
bool inq[N];
DB SPFA(int S, int T) {
	memset(inq, false, sizeof inq);
	for (int i = 0; i < cc; ++ i) d[i] = 1e9; d[S] = 0;
	unsigned short l = 0, r = 0; Q[r ++] = S; inq[S] = true;
	for (; l != r; ) {
		int u = Q[l ++]; inq[u] = false;
		for (int e = adj[u]; ~e; e = nxt[e]) 
			if (d[v[e]] - d[u] - w[e] > 0) {
				d[v[e]] = d[u] + w[e];
				if (!inq[v[e]]) {
					inq[v[e]] = true;
					Q[r ++] = v[e];
				}
			}
	}

	return d[T];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(15);

	for (; std::cin >> W >> n, W; ) {
		cc = n; int S = cc ++, T = cc ++;
		memset(adj, -1, sizeof adj); e = 0;
		ins(S, T, W);
		for (int i = 0; i < n; ++ i) {
			int m; std::cin >> m;
			p[i].clear();
			//p[i].resize(m);
			long long minx = 1e9, maxx = -1e9;
			for (int j = 0; j < m; ++ j) {
				Point tmp; tmp.read();
				p[i].push_back(tmp);
				minx = std::min(minx, p[i][j].x);
				maxx = std::max(maxx, p[i][j].x);
			}
			ins(S, i, minx); ins(i, T, W - maxx);
			for (int j = 0; j < i; ++ j) {
				int u = i, v = j;
				//if (p[u][0].x > p[v][0].x) std::swap(u, v);
				DB dis = 1e9;
				for (int a = 0; a < (int)p[u].size(); ++ a) {
					Point P = p[u][a];
					for (int b = 0; b < (int)p[v].size(); ++ b) {
						dis = std::min(dis, disToSeg(Line(p[v][b], p[v][(b + 1) % (int)p[v].size()]), p[u][a]));
						dis = std::min(dis, disToSeg(Line(p[u][a], p[u][(a + 1) % (int)p[u].size()]), p[v][b]));
//						std::cout << "xxx " << a << " " << b << " " << dis << std::endl;
					}
				}
				ins(u, v, dis); ins(v, u, dis);
			}
		}
		std::cout << SPFA(S, T) << std::endl;
	}

	return 0;
}
