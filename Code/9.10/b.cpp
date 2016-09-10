#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

const int N = 100005;
std::pair<int, int> leftstop[N][25], rightstop[N][25];
int cl[N], cr[N];
int a[N], ans[N], K = 300, cnt[1000006];
typedef std::pair<std::pair<int, int>, int> Query;
Query query[N];
int n, q; 

__inline bool cmp(const Query& a, const Query& b) {
	return a.first.second < b.first.second;
}

__inline bool cmp_eq(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return b.second == a.second;
}

__inline void addright(int l, int r, int d, int& ans) {
	for (std::pair<int, int> *it = leftstop[l] + cl[l] - 1; it >= leftstop[l]; -- it) {
		if (it->first <= r) {
			cnt[it->second] += d;
			if (d > 0 && cnt[it->second] == 1) ++ ans;
			if (d < 0 && cnt[it->second] == 0) -- ans;
		}
		else break;
	}
}

__inline void addleft(int l, int r, int d, int& ans) {
	for (std::pair<int, int> *it = rightstop[r] + cr[r] - 1; it >= rightstop[r]; -- it) {
		if (it->first >= l) {
			cnt[it->second] += d;
			if (d > 0 && cnt[it->second] == 1) ++ ans;
			if (d < 0 && cnt[it->second] == 0) -- ans;
		}
		else break;
	}
}

__inline void clear(std::vector<std::pair<int, int> >& v) {
	v.clear();
	std::vector<std::pair<int, int> >(v).swap(v);
}

bool eof = false;
namespace Reader {  
    const int L = (1 << 15) + 5;  
    char buffer[L], *S, *T;  
    __inline void get_char(char &ch) {  
        if (S == T) {  
            T = (S = buffer) + fread(buffer, 1, L, stdin);  
            if (S == T) {
				ch = EOF;
				eof = true;
				return ;
			}
        }  
		ch = *S++;
    }  
    __inline void get_int(int &x) {  
		char ch; //bool neg = 0;
		for (; get_char(ch), ch != EOF && ( ch < '0' || ch > '9' ); )/* neg ^= ch == '-'*/;
		if (ch == EOF) {
			eof = true; return;
		}
		x = ch - '0';
		for (; get_char(ch), ch >= '0' && ch <= '9'; ) 
			x = x * 10 + ch - '0';
		//if (neg) x = -x;
    }
}

int rm[1000006];
long long d[N];
__inline int lowbit(int x) {
	return x & (-x);
}
__inline void add(int x, int sd) {
	for (; x>0; x -= lowbit(x)) d[x] += sd;
}
__inline void add(int l, int r, int d) {
	if (l > r) return;
	add(l - 1, d); add(r, -d);
}
__inline int queryx(int x) {
	long long ret = 0;
	for (; x <= n; x += lowbit(x)) ret += d[x];
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	for (; Reader::get_int(n), Reader::get_int(q), !eof; ) {
		//std::cerr << "xxx" << std::endl;
		//std::cerr << n << " " << q << std::endl;
		for (int i = 1; i <= n; ++ i) Reader::get_int(a[i]);
		for (int i = 0; i < q; ++ i) {
			Reader::get_int(query[i].first.first);
			Reader::get_int(query[i].first.second);
			//std::cin >> query[i].first.first >> query[i].first.second;
			query[i].second = i;
		}
		for (int i = 1; i <= n; ++ i) {
			static std::pair<int, int> tmp[25]; int ct = 0;
			for (int j = 0; j < cr[i - 1]; ++ j)
				tmp[ct ++] = std::make_pair(rightstop[i - 1][j].first, std::__gcd(a[i], rightstop[i - 1][j].second));
			tmp[ct ++] = std::make_pair(i, a[i]);
			cr[i] = 0;
			for (int j = 0; j < ct; ++ j) {
				if (j == ct - 1 || tmp[j].second != tmp[j + 1].second)
					rightstop[i][cr[i] ++] = tmp[j];
			}
//			std::cout << "right " << i << ": " << std::endl;
//			foreach(it, rightstop[i])
//				std::cout << it->first << " " << it->second << std::endl;
		}
		cl[n + 1] = 0;
		for (int i = n; i >= 1; -- i) {
			static std::pair<int, int> tmp[25]; int ct = 0;
			for (int j = 0; j < cl[i + 1]; ++ j)
				tmp[ct ++] = std::make_pair(leftstop[i + 1][j].first, std::__gcd(a[i], leftstop[i + 1][j].second));
			tmp[ct ++] = std::make_pair(i, a[i]);
			cl[i] = 0;
			for (int j = 0; j < ct; ++ j) {
				if (j == ct - 1 || tmp[j].second != tmp[j + 1].second)
					leftstop[i][cl[i] ++] = tmp[j];
			}
//			std::cout << "left " << i << ": " << std::endl;
//			foreach(it, leftstop[i])
//				std::cout << it->first << " " << it->second << std::endl;
		}

		int cur = 0;
		std::sort(query, query + q, cmp);
		memset(d, 0, sizeof d);
		memset(rm, -1, sizeof rm);
		
		int ccr = -1;
		for (int i = 0; i < q; ++ i) {
			int l = query[i].first.first, r = query[i].first.second, index = query[i].second;	
			//std::cout << l << " " << r << std::endl;
			for (; ccr < r; ) {
				++ ccr;
				for (int j = 0; j < cr[ccr]; ++ j) {
					add(rm[rightstop[ccr][j].second] + 1, rightstop[ccr][j].first, 1);
					rm[rightstop[ccr][j].second] = std::max(rm[rightstop[ccr][j].second], rightstop[ccr][j].first);
				}
			}
			ans[index] = queryx(l);
		}
		for (int i = 0; i < q; ++ i) std::cout << -ans[i] << std::endl;
	}

	return 0;
}
