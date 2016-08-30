#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 2;
const int MAXN = 111111;
const int MAXL = MAXN * 4 + 11;
const int R[] = {107, 37, 139};
int fa[MAXL], f[MAXL], l, n;
LL pw[N][MAXL];
char str[MAXL], ans[MAXN];

struct Hash {
	LL hash[N];
	inline friend bool operator == (const Hash &p, const Hash &q) {
		for (int i = 0; i < N; ++i)
			if (p.hash[i] != q.hash[i]) return false;
		return true;
	}
	inline void getnext(const Hash &p, int c) {
		for (int i = 0; i < N; ++i)
			hash[i] = p.hash[i] * R[i] + c;
	}
} c[MAXL];

inline Hash gethash(int l, int r) {
	Hash ret;
	for (int i = 0; i < N; ++i) {
		ret.hash[i] = -c[l - 1].hash[i] * pw[i][r - l + 1] + c[r].hash[i];
	}
	return ret;
}

inline int getfa(int k) {
	return k == fa[k] ? k : fa[k] = getfa(fa[k]);
}

inline void cover(int left, int right, int id) {
	if (left >= l * 2) return;
	if (right >= l * 2) right = l * 2 - 1;
	for (int k = getfa(left); k <= right; k = fa[k]) {
		f[k] = id;
		fa[k] = k + 1;
	}
}

int main() {
    freopen("border.in", "r", stdin);
    freopen("border.out", "w", stdout);
	for (int i = 0; i < N; ++i) {
		pw[i][0] = 1;
		for (int j = 1; j < MAXN; ++j) pw[i][j] = pw[i][j - 1] * R[i];
	}
	
	scanf("%s", str + 1);
	l = strlen(str + 1); n = l * 4;
	for (int i = 1; i <= l; ++i) str[i + l + l + l] = str[i + l] = str[i + l + l] = str[i];
	for (int i = 1; i <= n; ++i) c[i].getnext(c[i - 1], str[i] - 'a' + 1);
	
	for (int i = l - 1; i <= l * 2 + 3; ++i) fa[i] = i;
	for (int i = l - 1; i; --i) {
		int K = (l - 1) / i;
		for (int j = 0; j <= K; ++j) {
			int left = 0, right = i, head = l + j * i + 1, tail = l + j * i, back, front;
			while (left < right) {
				int mid = left + right + 1 >> 1;
				if (gethash(head, head + mid - 1) == gethash(head + i, head + i + mid - 1)) left = mid;
				else right = mid - 1;
			}
			back = left;
			left = 0; right = i;
			while (left < right) {
				int mid = left + right + 1 >> 1;
				if (gethash(tail - mid + 1, tail) == gethash(tail + i - mid + 1, tail + i)) left = mid;
				else right = mid - 1;
			}
			front = left;
			if (back + front < i) continue;
			cover(head + i - 1 - front, head + back - 1, i);
		}
	}
	
	for (int i = 1; i <= l; ++i) {
		if (f[i - 1 + l]) ans[i] = '1';
		else ans[i] = '0';
	}
	ans[l + 1] = 0;
	puts(ans + 1);
}
