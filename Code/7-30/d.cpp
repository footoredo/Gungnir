#include <bits/stdc++.h>
using namespace std;

const int inv[3] = {0, 1, 2};
const int dx[4] = {0, 0, 0, -1};
const int dy[4] = {0, 1, -1, 0};

__inline void clear(vector<int> &v) {
	v.clear();
	vector<int>(v).swap(v);
}

__inline void clear(vector<pair<int, int> > &v) {
	v.clear();
	vector<pair<int, int> >(v).swap(v);
}

struct X {
	vector<int> x;
	void init(int n) {
		clear(x);
		x.resize(n);
	}
	X operator+(const X& rhs) {
		X ret; ret.init(x.size());
		for (int i = 0; i < x.size(); i++)
			ret.x[i] = (x[i] + rhs.x[i]) % 3;
		return ret;
	}
	X operator-(const X& rhs) {
		X ret; ret.init(x.size());
		for (int i = 0; i < x.size(); i++)
			ret.x[i] = (x[i] - rhs.x[i] + 3) % 3;
		return ret;
	}
	X operator*(int k) {
		X ret; ret.init(x.size());
		for (int i = 0; i < x.size(); i++)
			ret.x[i] = x[i] * k % 3;
		return ret;
	}
	/*X &operator=(const X& rhs) {
		clear(x); x = rhs.x;
		return *this;
	}*/
};

const int N = 33;
X s[N][N], effect[N][N], a[N][N];
int n, m;

__inline bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < n && j < m;
}

vector<pair<int, int> > ans;

X eq[N];
vector<int> gauss() {
	for (int i = 0; i < m; i++) {
		eq[i] = a[n-1][i] - effect[n-1][i]; eq[i].x[m] = 3-eq[i].x[m];
	}
	for (int i = 0; i < m; i++) {
		int k = -1;
		for (int j = i; j < m; j++)
			if (eq[j].x[i]) {
				k = j; break;
			}
		//assert(k >= i);
		if (~k) {
			swap(eq[i], eq[k]);
			for (int j = i + 1; j < m; j++) {
				if (eq[j].x[i]) {
					int k = eq[j].x[i] * inv[eq[i].x[i]] % 3;
					eq[j] = eq[j] - eq[i] * k;
				}
			}
		}
	}
	
	vector<int> ret; ret.resize(m);
	for (int i = m - 1; i >= 0; i--) {
		for (int j = i + 1; j < m; j++)
			eq[i].x[m] = (eq[i].x[m] + 3 - ret[j] * eq[i].x[j]%3)%3;
		ret[i] = eq[i].x[m] * inv[eq[i].x[i]] % 3;
	}
	
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	for (; T--; ) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i == 0) {
					s[i][j].init(m + 1);
					s[i][j].x[j] = 1;
				}
				else s[i][j] = a[i-1][j] - effect[i-1][j];
				
				//puts("done");
				
				a[i][j].init(m + 1);
				//printf("%d %d\n", i, j);
				scanf("%d", &a[i][j].x[m]); a[i][j].x[m] = 3-a[i][j].x[m];
				
			}
			for (int j = 0; j < m; j++) {
				effect[i][j].init(m + 1);
				for (int k = 0; k < 4; k++)
					if (valid(i + dx[k], j + dy[k]))
						effect[i][j] = effect[i][j] + s[i + dx[k]][j + dy[k]] * (k == 0 ? 2 : 1);
			}
		}
		
		//puts("done");
		vector<int> x = gauss();
		clear(ans);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				int tmp = 0;
				for (int k = 0; k < m; k++)
					tmp = (tmp + s[i][j].x[k] * x[k]) % 3;
				tmp = (tmp + s[i][j].x[m]) % 3;
				for (int k = 0; k < tmp; k++) ans.push_back(make_pair(i + 1, j + 1));
			}
			
		printf("%d\n", (int)ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf("%d %d\n", ans[i].first, ans[i].second);
	}
	
	return 0;
}
