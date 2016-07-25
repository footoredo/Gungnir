#include <bits/stdc++.h>

struct Node {
	int ans, tag_rank;
	bool tag;
	std::vector<int> b, source[2];
	Node *ch[2];
	__inline Node() {
		ans = tag_rank = tag = 0;
		b.clear(); source[0].clear(); source[1].clear();
		ch[0] = ch[1] = NULL;
	}
	__inline void entag(int rank) {
		tag = 1; tag_rank = rank;
		ans = rank + 1;
	}
	__inline void push() {
		if (!tag) return;
		if (ch[0]) ch[0]->entag(~tag_rank ? source[0][tag_rank] : -1);
		if (ch[1]) ch[1]->entag(~tag_rank ? source[1][tag_rank] : -1);
		tag = 0;
	}
	__inline void update() {
		ans = (ch[0] ? ch[0]->ans : 0) + (ch[1] ? ch[1]->ans : 0);
	}
} *root;

const int N = 111111;
int a[N], b[N];

__inline void clear(std::vector<int>& v) {
	v.clear();
	std::vector<int>(v).swap(v);
}

void delete_tree(Node *T) {
	if (T == NULL) return;
	clear(T->b); clear(T->source[0]); clear(T->source[1]);
	delete_tree(T->ch[0]);
	delete_tree(T->ch[1]);
	delete T;
}

Node *build_tree(int l, int r) {
	Node *T = new Node;
	if (l == r) {
		T->b.push_back(b[l]);
		T->ans = a[l] >= b[l];
	}
	else {
		int m = l + r >> 1;
		T->ch[0] = build_tree(l, m);
		T->ch[1] = build_tree(m+1, r);
		T->update();
		std::vector<int> &bl = T->ch[0]->b,
			&br = T->ch[1]->b;
		for (int j = 0, k = 0; j < bl.size() || k < br.size();) {
			if (k == br.size() || j < bl.size() && bl[j] < br[k]) 
				T->b.push_back(bl[j++]);
			else T->b.push_back(br[k++]);
			T->source[0].push_back(j - 1);
			T->source[1].push_back(k - 1);
		}
/*		std::cout << "b in " << l << " " << r << std::endl;
		for (int i = 0; i < r-l+1; i++) std::cout << T->b[i] << " ";
		std::cout << std::endl;
		for (int i = 0; i < r-l+1; i++) std::cout << T->source[0][i] << " ";
		std::cout << std::endl;
		for (int i = 0; i < r-l+1; i++) std::cout << T->source[1][i] << " ";
		std::cout << std::endl;
		assert(T->b.size() == r - l + 1); */
	}
	return T;
}

int query(Node *T, int l, int r, int ql, int qr) {
	if (ql <= l && qr >= r) return T->ans;
	T->push();
	int m = l + r >> 1, ret = 0;
	if (ql <= m) ret += query(T->ch[0], l, m, ql, qr);
	if (qr > m) ret += query(T->ch[1], m+1, r, ql, qr);
	return ret;
}

void modify(Node *T, int l, int r, int ql, int qr, int rank) {
//	std::cout << l << " " << r << " " << ql << " " << qr << " " << rank << std::endl;
	if (ql <= l && qr >= r) T->entag(rank);
	else {
		T->push();
		int m = l + r >> 1;
		if (ql <= m) modify(T->ch[0], l, m, ql, qr, 
				~rank ? T->source[0][rank] : -1);
		if (qr > m) modify(T->ch[1], m+1, r, ql, qr, 
				~rank ? T->source[1][rank] : -1);
		T->update();
	}
}

int A, B, C = ~(1<<31), M = (1<<16)-1;
int rnd(int last) {
	A = (36969 + (last >> 3)) * (A & M) + (A >> 16);
	B = (18000 + (last >> 3)) * (B & M) + (B >> 16);
	return (C & ((A << 16) + B)) % 1000000000;
}

const int MODN = 1e9 + 7 + 1e-9;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T--; ) {
		int n, m; std::cin >> n >> m >> A >> B;
		for (int i = 0; i < n; i++) std::cin >> a[i];
		for (int i = 0; i < n; i++) std::cin >> b[i];
		root = build_tree(0, n-1);
//		std::cout << "xx" << std::endl;

		int last = 0, ans = 0;
		for (int i = 1; i <= m; i++) {
			int l = rnd(last) % n, 
				r = rnd(last) % n, x = rnd(last) + 1;
			if (l > r) std::swap(l, r);
			if ((l + r + x) & 1) {
//				std::cout << "+ " << l << " " << r << " " << x << std::endl; 
				modify(root, 0, n-1, l, r, 
						std::upper_bound(root->b.begin(), root->b.end(), x) -
						root->b.begin() - 1); 
			}
			else {
//				std::cout << "? " << l << " " << r << std::endl;
				last = query(root, 0, n-1, l, r);
				ans = (ans + 1LL * i * last) % MODN;
//				std::cout << last << std::endl;
			}
		}

		std::cout << ans << std::endl;
		delete_tree(root);
	}

	return 0;
}
