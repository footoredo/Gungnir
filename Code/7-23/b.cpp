#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

const int N = 111, M = 11111;
int n, m;

typedef std::set<int> S;
typedef S::iterator SIT;
__inline SIT left(const S& s, SIT pit) {
    assert(pit != s.end());
    if (pit == s.begin()) return s.end();
    else return --pit;
}
__inline SIT right(const S& s, SIT pit) {
    assert(pit != s.end());
    return ++pit;
}

S searchlights[N];

int gaps[N];

typedef std::vector<std::pair<int, int> > V;
typedef V::iterator VIT;
V dying[M];
bool exist[N][M];
int remain[M];

bool fvck_check(int level) {
    for (int i = 0; i < m; i++) {
	int upmost = -1;
	for (int j = 0; j < n; j++) if (exist[j][i]) {
	    if (j - upmost > level) return false;
	    upmost = j + level - 1;
	}
	if (upmost < n - 1) return false;
    }
    return true;
}

bool check_level(int level) {
    if (level <= n) if (!fvck_check(level)) return false;
//    std::cout << "done fvck" << std::endl;
    for (int i = 0; i < n; i++) {
	if (gaps[i] > level * 2) return false;
	if (searchlights[i].empty()) return false;
	if (*searchlights[i].begin() + 1 > level) return false;
	if (m - *searchlights[i].rbegin() > level) return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    for (; std::cin >> n >> m, n || m; ) {
	int maxlevel = 0;
	memset(remain, 0, sizeof(*remain)*m);
	for (int i = 0; i < n; i++) {
	    searchlights[i].clear();
	    gaps[i] = 0;
	    int leftmost = -1;
	    for (int j = 0; j < m; j++) {
		int level; std::cin >> level;
		exist[i][j] = !!level;
		if (level) {
		    remain[j]++;
		    dying[level].push_back(std::make_pair(i, j));
		    searchlights[i].insert(j);
		    if (~leftmost) 
			gaps[i] = std::max(j - leftmost + 1, gaps[i]);
		    leftmost = j;
		}
		maxlevel = std::max(level, maxlevel);
	    }
	}

	int ans = -1, level;
	bool alive = true;
	for (int j = 0; j < m; j++)
	    if (!remain[j]) {
		alive = false;
		break;
	    }
	for (level = 1; alive && level <= maxlevel; level++) {
//	    std::cout << level << std::endl;
	    if (check_level(level)) {
		ans = level; 
		break;
	    }
//	    std::cout << "done" << std::endl;
	    for (VIT it = dying[level].begin(); 
		    alive && it != dying[level].end(); it++) {
		int i = it->first, j = it->second;
		exist[i][j] = 0;
		SIT p = searchlights[i].find(j);
		SIT l = left(searchlights[i], p),
		    r = right(searchlights[i], p);
		if (l != searchlights[i].end() &&
			r != searchlights[i].end())
		    gaps[i] = std::max(*r - *l + 1, gaps[i]);
		searchlights[i].erase(p);

		if (!--remain[j]) {
		    alive = false;
		}
	    }

	    dying[level].clear();
	}
	for (; level <= maxlevel; level++) dying[level].clear();
	
	if (!~ans) std::cout << "NO ANSWER!" << std::endl;
	else std::cout << ans << std::endl;
    }

    return 0;
}