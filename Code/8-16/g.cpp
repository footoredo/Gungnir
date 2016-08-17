#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

const int N = 15;

int n;

int cc = 0;
std::map<std::pair<bool, std::pair<int, int> >, int> pool;

struct Node {
	Node *ch[2], *p;
	int hash[N], dep, state, hash_all;
	bool term;
} *root = NULL;

Node *build_tree(int dep, Node *p) {
	if (dep > n) return NULL;
	Node *T = new Node;
	T->p = p;
	T->dep = dep;
	T->ch[0] = build_tree(dep + 1, T);
	T->ch[1] = build_tree(dep + 1, T);
	return T;
}

void ins(Node *T, char *S, bool term) {
	if (*S == 0) {
		T->term = term;
	}
	else {
		ins(T->ch[*S == '1'], S + 1, term);
	}
}

int get_hash(const std::pair<bool, std::pair<int, int> >& tuple) {
//	std::cout << tuple.first << " " << tuple.second.first << " " << tuple.second.second << std::endl;
	if (pool[tuple]) return pool[tuple];
	else return pool[tuple] = ++cc;
}

void get_hash(Node *T) {
	T->hash[0] = get_hash(std::make_pair(
				T->term, std::make_pair(0, 0)));
	if (T->ch[0]) {
		get_hash(T->ch[0]); get_hash(T->ch[1]);
		for (int d = 0; T->ch[0]->hash[d]; ++ d)
			T->hash[d + 1] = get_hash(std::make_pair(T->term,
						std::make_pair(T->ch[0]->hash[d], 
							T->ch[1]->hash[d])));
	}
	T->hash_all = T->hash[n - T->dep];
}

int state = 0, phi[1 << N][2];
std::vector<int> terminal_state;

std::map<int, int> storage;
std::queue<Node *> Q;
void build_DFA() {
	Q.push(root);
	for (; !Q.empty(); ) {
		Node *u = Q.front(); Q.pop();
		if (storage[u->hash_all]) 
			phi[u->p->state][u == u->p->ch[1]] = storage[u->hash_all];
		else {
			storage[u->hash_all] = u->state = ++ state;
			if (u->term) terminal_state.push_back(u->state);
			if (u->p) phi[u->p->state][u == u->p->ch[1]] = u->state;
			for (int d = 0; u->hash[d]; ++ d)
				storage[u->hash[d]] = u->state;
			if (u->ch[0]) {
				Q.push(u->ch[0]); Q.push(u->ch[1]);
			}
		}
	}
}

int main() {
//	freopen("learning.in", "r", stdin);
//	freopen("learning.out", "w", stdout);
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	root = build_tree(0, NULL);
	for (int i = 1; i < 1 << n + 1; ++ i) {
		char buf[N + 5];
		std::cin >> buf;
		ins(root, buf + 1, buf[0] == '+');
	}

	get_hash(root);
	build_DFA();
//	std::cout << cc << std::endl;

//	std::cout << state << std::endl; return 0;
	std::cout << state << " " << root->state << std::endl;
	std::cout << terminal_state.size();
	std::sort(terminal_state.begin(), terminal_state.end());
	foreach(s, terminal_state)
		std::cout << " " << *s;
	std::cout << std::endl;
	for (int i = 1; i <= state; ++ i) {
		if (!phi[i][0]) phi[i][0] = i;
		if (!phi[i][1]) phi[i][1] = i;
		std::cout << phi[i][0] << " " << phi[i][1] << std::endl;
	}

	return 0;
}
