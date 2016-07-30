#include <bits/stdc++.h>
using namespace std;

const int maxn = 222222;
const int alphabet = 26;
int c[maxn][alphabet], l[maxn], f[maxn], T, size, last;
char cc[2], ch[maxn];

void add(int x, int &last) {
	int lastnode = last;
	if (c[lastnode][x]) {
		int nownode = c[lastnode][x];
		if (l[nownode] == l[lastnode] + 1) last = nownode;
		else {
			int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
			for (int i = 0; i < 26; ++i) c[auxnode][i] = c[nownode][i];
			f[auxnode] = f[nownode]; f[nownode] = auxnode;
			for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) c[lastnode][x] = auxnode;
			last = auxnode;
		}
	} else {
		int newnode = ++size; l[newnode] = l[lastnode] + 1;
		for (; lastnode && !c[lastnode][x]; lastnode = f[lastnode]) c[lastnode][x] = newnode;
		if (!lastnode) f[newnode] = 1;
		else {
			int nownode = c[lastnode][x];
			if (l[lastnode] + 1 == l[nownode]) f[newnode] = nownode;
			else {
				int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
				for (int i = 0; i < 26; ++i) c[auxnode][i] = c[nownode][i];
				f[auxnode] = f[nownode]; f[nownode] = f[newnode] = auxnode;
				for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) c[lastnode][x] = auxnode;
			}
		}
		last = newnode;
	}
}

void clear() {
	size = 1; last = 1;
	memset(c, 0, sizeof(c));
	memset(f, 0, sizeof(f));
	memset(l, 0, sizeof(l));
}

int main() {
	scanf("%d", &T);
	for (int Q = 1; Q <= T; ++Q) {
		scanf("%s", cc);
		scanf("%s", ch + 1);
		int len = strlen(ch + 1);
		clear();
		long long ans = 0;
		for (int i = 1; i <= len; ++i) add(ch[i] - 'a', last);
		for (int i = 2; i <= size; ++i) ans += (long long)(l[i] - l[f[i]]);
		clear();
		for (int i = 1; i <= len; ++i) {
			if (ch[i] == cc[0]) last = 1;
			else add(ch[i] - 'a', last);
		}
		for (int i = 2; i <= size; ++i) ans -= (long long)(l[i] - l[f[i]]);
		cout << "Case #" << Q << ": " << ans << endl;
	}
}
