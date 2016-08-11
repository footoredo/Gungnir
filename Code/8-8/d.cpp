#include <bits/stdc++.h>
#define exit EXIT
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

struct Node {
	int tag, value;
	Node *ch[2];
	__inline Node() {
		ch[0] = ch[1] = NULL;
		tag = value = 0;
	}
	__inline void push() {
		if (!tag) return;
		ch[0]->tag += tag;
		ch[1]->tag += tag;
		value += tag;
		tag = 0;
	}
	__inline void update() {
		value = std::min(ch[0]->value + ch[0]->tag, ch[1]->value + ch[1]->tag);
	}
} *root;

Node *build(int l, int r) {
	Node *T = new Node;

	if (l < r) {
		int mid = (l + r) / 2;
		T->ch[0] = build(l, mid);
		T->ch[1] = build(mid + 1, r);
	}
	return T;
}

void elim(Node *T) {
	if (T == NULL) return;
	elim(T->ch[0]); elim(T->ch[1]);
	delete T;
}

void add(Node *T, int l, int r, int ql, int qr, int d) {
	if (ql <= l && qr >= r) {
		T->tag += d;
	}
	else {
		T->push();
		int mid = (l + r) / 2;
		if (ql <= mid) add(T->ch[0], l, mid, ql, qr, d);
		if (qr > mid) add(T->ch[1], mid + 1, r, ql, qr, d);
		T->update();
	}
}

int query(Node *T, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) return T->value + T->tag;
	else {
		T->push();
		int mid = (l + r) / 2;
		int ret = 1e9;
		if (ql <= mid) ret = query(T->ch[0], l, mid, ql, qr); 
		if (qr > mid) ret = std::min(ret, 
				query(T->ch[1], mid + 1, r, ql, qr));
		return ret;
	}
}

const int N = 222222;
int prv[N], nxt[N], A[N], n, curprv[N], curnxt[N];
int pool[N], cc;
std::vector<std::pair<int, int> > enter[N], exit[N];

template <typename T>
__inline void clear(T& v) {
	v.clear();
	T(v).swap(v);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T --; ) {
		std::cin >> n; cc = 0;
		for (int i = 0; i < n; ++ i) {
			std::cin >> A[i];
			pool[cc ++] = A[i];
			prv[i] = -1; nxt[i] = n;
			curprv[i] = -1; curnxt[i] = n;
			clear(enter[i]); clear(exit[i]);
		}
		std::sort(pool, pool + cc);
		cc = std::unique(pool, pool + cc) - pool;
		for (int i = 0; i < n; ++ i) {
			A[i] = std::lower_bound(pool, pool + cc, A[i]) - pool;
			prv[i] = curprv[A[i]];
			curprv[A[i]] = i;
		}
		for (int i = n - 1; i >= 0; -- i) {
			nxt[i] = curnxt[A[i]];
			curnxt[A[i]] = i;
//			std::cout << prv[i] + 1 << " " << i << " " << nxt[i] - 1 << std::endl;
			enter[prv[i] + 1].push_back(std::make_pair(i, nxt[i] - 1));
			exit[i].push_back(std::make_pair(i, nxt[i] - 1));
		}

		root = build(0, n - 1);
		bool fail = false;
		for (int i = 0; i < n; ++ i) {
			foreach(it, enter[i]) {
//				std::cout << "xx " << it->first << " " << it->second << std::endl;
				add(root, 0, n - 1, it->first, it->second, 1);
			}
			if (query(root, 0, n - 1, i, n - 1) == 0) {
//				std::cout << i << std::endl;
				fail = true; break;
			}
			foreach(it, exit[i])
				add(root, 0, n - 1, it->first, it->second, -1);
		}
		elim(root);

		std::cout << (fail ? "boring" : "non-boring") << std::endl;
	}
	
	return 0;
}
