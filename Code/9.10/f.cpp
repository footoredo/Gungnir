#include <bits/stdc++.h>
using namespace std;

const int MAXN = 21111;
int val[MAXN], n, T;

struct tree {
	int tag, mx;
} tr[MAXN * 4];

inline bool cmp(int x, int y) {
	return x > y;
}

inline int getnode(int l, int r) {
	return (l + r) | (l != r);
}

inline void update(int k, int l, int r) {
	int mid = l + r >> 1;
	int lc = getnode(l, mid), rc = getnode(mid + 1, r);
	tr[k].mx = max(tr[lc].mx, tr[rc].mx);
}

inline void pushdown(int k, int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	int lc = getnode(l, mid), rc = getnode(mid + 1, r);
	tr[lc].tag += tr[k].tag; tr[rc].tag += tr[k].tag;
	tr[lc].mx += tr[k].tag; tr[rc].mx += tr[k].tag;
	tr[k].tag = 0;
}

inline void buildtree(int l, int r) {
	int k = getnode(l, r);
	tr[k].tag = 0;
	if (l == r) {
		tr[k].mx = val[l];
		return;
	} else {
		int mid = l + r >> 1;
		buildtree(l, mid);
		buildtree(mid + 1, r);
		update(k, l, r);
	}
}

inline int query_less(int l, int r, int x) {
	int k = getnode(l, r);
	if (tr[k].tag) pushdown(k, l, r);
	if (tr[k].mx < x) return l;
	if (l == r) return r + 1;
	int mid = l + r >> 1;
	int lc = getnode(l, mid), rc = getnode(mid + 1, r);
	if (tr[rc].mx < x) return query_less(l, mid, x);
	else return query_less(mid + 1, r, x);
}

inline int query(int l, int r, int id) {
	int k = getnode(l, r);
	if (tr[k].tag) pushdown(k, l, r);
	if (l == r) return tr[k].mx;
	int mid = l + r >> 1;
	return id > mid ? query(mid + 1, r, id) : query(l, mid, id);
}

inline void modify(int l, int r, int a, int b, int x) {
	if (a > b) return;
	//cout << l << " " << r << " " << a << " " << b << endl;
//if (l == 1 && r == n) cout << "modify: " << a << " " << b << endl;
	int k = getnode(l, r);
	if (tr[k].tag) pushdown(k, l, r);
	if (l == a && b == r) {
		tr[k].mx += x; tr[k].tag += x;
		return;
	}
	int mid = l + r >> 1;
	if (a > mid) modify(mid + 1, r, a, b, x);
	else
		if (b <= mid) modify(l, mid, a, b, x);
		else {
			modify(l, mid, a, mid, x);
			modify(mid + 1, r, mid + 1, b, x);
		}
	update(k, l, r);
}

int main() {
	while(cin>>T){
	for (; T; --T) {
		scanf("%d", &n);
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &val[i]);
			val[i] -= n - 1;
			sum += val[i];
		}
		if (sum) {
			puts("F");
			continue;
		}
		
		sort(val + 1, val + n + 1, cmp);
		bool flag = true;
		buildtree(1, n);
//modify(1, n, 3, 4, 1);
//cout << query(1, n, 5) << " " << query_less(1, n, 0) << endl;
//return 0;
//for (int i = 1; i <= n; ++i) cout << val[i] << " "; cout << endl;
		for (int i = 1; i <= n; ++i) {
			val[i] = query(1, n, i);
//cout << "nowval: " << i << " " << val[i] << endl;
			if (val[i] < 0 || n - i < val[i]) {
				flag = false;
				break;
			}
			if (!val[i]) continue;
			int tmp = query(1, n, n - val[i] + 1);
//cout << "tmp: " << i << " " << tmp << endl;
			int l = query_less(1, n, tmp + 1), r = query_less(1, n, tmp) - 1;
			//cout << i << " " << l << " " << r << endl;
			if (l <= i) l = i + 1;
			if (l == n - val[i] + 1) modify(1, n, n - val[i] + 1, n, 1);
			else {
				modify(1, n, l, l + r - (n - val[i] + 1), 1);
				modify(1, n, r + 1, n, 1);
			}
			//return 0;
		}
		if (flag) puts("T"); else puts("F");
	}
	}
}
