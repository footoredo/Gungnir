#include <bits/stdc++.h>
using namespace std;

char graph[256][17][55];
char seq[55], query[55];

int main() {
	int n, q; scanf("%d%d", &n, &q);
	scanf("%s", seq);
	for (int i = 0; i < n; i++) {
		int p = seq[i];
		for (int j = 0; j < 17; j++)
			scanf("%s", graph[p][j]);
	}
	
	for (int i = 0; i < q; i++) {
		scanf("%s", query);
		int m = strlen(query);
		printf("Query %d: ", i + 1);
		for (int j = 0; j < m; j++) {
			bool succ = 0;
			for (int x = 0; x < 16; x++)
				for (int y = 0; y < 43; y++) if (graph[query[j]][x][y] == '*') {
					bool fail = 0;
					for (int k = 0; k < m; k++) if (k != j && graph[query[k]][x][y] == '*') {
						fail = 1; break;
					}
					if (!fail) {
						succ = 1; break;
					}
				}
			putchar(succ?'Y':'N');
		}
		puts("");
	}
	
	return 0;	
}
