#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

const char SUIT[5] = "SHDC";

struct Card {
	int rank;
	char suit;
	__inline Card() {}
	__inline Card(int r, int s) {
		rank = r; suit = SUIT[s];
	}
	__inline bool read() {
		char buf[3];
		if (!(std::cin >> buf)) return false;
		if (buf[0] == '#') return false;
		suit = buf[0];
		if (isdigit(buf[1])) rank = buf[1] - '0';
		else if (buf[1] == 'T') rank = 10;
		else if (buf[1] == 'J') rank = 11;
		else if (buf[1] == 'Q') rank = 12;
		else if (buf[1] == 'K') rank = 13;
		else if (buf[1] == 'A') rank = 14;
		else {
			assert(0);
			return false;
		}
//		std::cout << rank << " " << suit << std::endl;
		return true;
	}
	__inline bool operator<(const Card& rhs) const {
		return rank == rhs.rank ? suit < rhs.suit : rank < rhs.rank;
	}
	__inline bool operator==(const Card& rhs) const {
		return rank == rhs.rank && suit == rhs.suit;
	}
};

typedef std::vector<Card> Deck;
typedef std::vector<Deck> Group;

__inline bool cmp_c(const Card& a, const Card& b) {
	return b < a;
}

__inline bool cmp(const Deck& a, const Deck& b) {
	if (a.size() == b.size()) {
		for (int i = 0; i < (int)a.size(); ++ i) {
			if (b[i].rank < a[i].rank) return 1;
			if (a[i].rank < b[i].rank) return 0;
		}
		return 0;
	}
	else return a.size() > b.size();
}

template <typename T>
__inline void clear(T& container) {
	container.clear();
	T(container).swap(container);
}

__inline Group make_group(Deck& d) {
	std::sort(d.begin(), d.end(), cmp_c);
	Deck cur;
	Group ret;
	foreach(it, d) {
		if (!cur.size() || it->rank == cur[0].rank) {
			cur.push_back(*it);
		}
		else {
			ret.push_back(cur);
			clear(cur);
			cur.push_back(*it);
		}
	}
	if (cur.size()) ret.push_back(cur);
	std::sort(ret.begin(), ret.end(), cmp);
	return ret;
}

__inline bool is_flush(const Deck& d) {
	char suit = d[0].suit;
	foreach(it, d) if (suit != it->suit) return false;
	return true;
}

__inline bool is_flush(const Group& g) {
	char suit = g[0][0].suit;
	foreach(it, g) {
		if (suit != (*it)[0].suit) return false;
		if (!is_flush(*it)) return false;
	}
	return true;
}

__inline bool is_straight(const Group& g) {
	if ((int)g.size() != 5) return false;
	for (int i = 2; i < 5; ++ i)
		if (g[i][0].rank != g[i - 1][0].rank - 1)
			return false;
	if (g[0][0].rank == g[1][0].rank + 1 ||
			g[0][0].rank == 14 && g[1][0].rank == 5)
		return true;
	else return false;
}

__inline bool is_four(const Group& g) {
	return (int)g[0].size() == 4;
}

__inline bool is_full_house(const Group& g) {
	return (int)g[0].size() == 3 && (int)g[1].size() == 2;
}

__inline bool is_three(const Group& g) {
	return (int)g[0].size() == 3 && (int)g[1].size() == 1;
}

__inline bool is_two_pairs(const Group& g) {
	return (int)g[0].size() == 2 && (int)g[1].size() == 2;
}

__inline bool is_one_pair(const Group& g) {
	return (int)g[0].size() == 2 && (int)g[1].size() == 1;
}

__inline int get_rank(const Group& g) {
	if (is_straight(g) && is_flush(g)) return 8;
	if (is_four(g)) return 7;
	if (is_full_house(g)) return 6;
	if (is_flush(g)) return 5;
	if (is_straight(g)) return 4;
	if (is_three(g)) return 3;
	if (is_two_pairs(g)) return 2;
	if (is_one_pair(g)) return 1;
	return 0;
}

__inline bool win(const Deck& _a, const Deck& _b) {
	Deck a(_a), b(_b);
	Group ga = make_group(a), gb = make_group(b);
	int ra = get_rank(ga), rb = get_rank(gb);
	if (ra > rb) return true;
	if (ra < rb) return false;
	if (ra == 4 || ra == 8) {
		if (ga[0][0].rank == 14 && ga[1][0].rank == 5)
			ga[0][0].rank = 1;
		if (gb[0][0].rank == 14 && gb[1][0].rank == 5)
			gb[0][0].rank = 1;
	}
	if (ga.size() != gb.size()) {
		foreach(it, ga) {
			foreach(jt, *it)
				std::cout << jt->rank<< "." << jt->suit << " ";
			std::cout << std::endl;
		}
		foreach(it, gb) {
			foreach(jt, *it)
				std::cout << jt->rank << "." << jt->suit << " ";
			std::cout << std::endl;
		}
	}
	for (int i = 0; i < (int)ga.size(); ++ i) {
		if (ga[i][0].rank > gb[i][0].rank) return 1;
		if (ga[i][0].rank < gb[i][0].rank) return 0;
	}
	return 0;
}

Card yr[2], op[2], cm[5];
std::set<Card> all;

Deck opt, tmp;
void search(int pos, int taken, const Deck& all) {
	if (taken == 5) {
		if (!opt.size() || win(tmp, opt)) {
			clear(opt);
			opt = tmp;
		}
	}
	else if (7 - pos >= 5 - taken) {
		search(pos + 1, taken, all);
		tmp.push_back(all[pos]);
		search(pos + 1, taken + 1, all);
		tmp.pop_back();
	}
}

Deck optimal(const Deck& a) {
	clear(opt); clear(tmp);
	search(0, 0, a);
	return opt;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(10);

	for (; ; ) {
		clear(all);
		if (!yr[0].read()) break;
		yr[1].read(); 
		op[0].read(); op[1].read();
		cm[0].read(); cm[1].read(); cm[2].read();
		all.insert(yr[0]); all.insert(yr[1]);
		all.insert(op[0]); all.insert(op[1]);
		all.insert(cm[0]); all.insert(cm[1]); all.insert(cm[2]);

		int all_cnt = 0, win_cnt = 0;
		for (int i = 2; i <= 14; ++ i)
			for (int j = 0; j < 4; ++ j) {
				cm[3] = Card(i, j);
				if (all.count(cm[3])) continue;
				all.insert(cm[3]);
				for (int k = 2; k <= 14; ++ k)
					for (int l = 0; l < 4; ++ l) {
						cm[4] = Card(k, l);
						if (all.count(cm[4]) || cm[3] < cm[4]) continue;
						++all_cnt;
						//std::cout << all_cnt << std::endl;
						Deck yrs, ops;
						yrs.push_back(yr[0]);
						yrs.push_back(yr[1]);
						ops.push_back(op[0]);
						ops.push_back(op[1]);
						for (int x = 0; x < 5; ++ x) {
							yrs.push_back(cm[x]);
							ops.push_back(cm[x]);
						}
						if (win(optimal(yrs), optimal(ops))) ++ win_cnt;
					}
				all.erase(cm[3]);
			}
		std::cout << win_cnt * 1. / all_cnt << std::endl;
	}


	return 0;
}
