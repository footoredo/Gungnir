#include <bits/stdc++.h>
using namespace std;
typedef long double DB;

const int N = 33, M = 1111;
int n, m;
int fail[N];
DB p[N], f[M][N];
char key[N], word[N];

int main() {
	for (; scanf("%d%d", &n, &m), n || m; ) {
		for (int i = 0; i < n; i++) {
			char buf[3];
			scanf("%s", buf); cin >> p[i];
			key[i] = buf[0];
		}
		
		scanf("%s", word); fail[0] = -1;
		int len = strlen(word);
		for (int i = 1, j = -1; i < len; i++) {
			for (; ~j && word[j+1] != word[i]; ) j = fail[j];
			if (word[j+1] == word[i]) ++j;
			fail[i] = j;
		}
		
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= len; j++)
				f[i][j] = 0;
		f[0][0] = 1;
		DB ans = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < len; j++) {
				for (int k = 0; k < n; k++) {
					int nxt = j - 1;
					for (; ~nxt && word[nxt+1] != key[k]; ) nxt = fail[nxt];
					if (word[nxt+1] == key[k]) ++nxt;
					f[i+1][nxt+1] += p[k] * f[i][j];
				}
			}
		}
		for (int i = len; i <= m; i++) ans += f[i][len];
		printf("%.2f", (double)(ans * 100 + 1e-8));
		puts("\%");
	}
	return 0;
}