#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
int dp_king[N][N];
int dp_rock[N][N], heng_rock[N][N], shu_rock[N][N];
int dp_knight[N][N];
int dp_queen[N][N], heng_queen[N][N], shu_queen[N][N], xie_queen[N][N];

void print(int x) {
	puts(x == 1 ? "B" : (x == 0 ? "D" : "G"));
}

int main() {
	int n = 1000;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == 1 && j == 1) dp_king[i][j] = -1;
			else {
				int tmp = 1;
				if (i > 1) tmp = min(tmp, dp_king[i-1][j]);
				if (j > 1) tmp = min(tmp, dp_king[i][j-1]);
				if (i > 1 && j > 1) tmp = min(tmp, dp_king[i-1][j-1]);
				dp_king[i][j] = -tmp;
				//printf("%d %d %d\n", i, j, dp_king[i][j]);
			}
			
			if (i == 1 && j == 1) dp_rock[i][j] = heng_rock[i][j] = shu_rock[i][j] = -1;
			else {
				int tmp = 1;
				if (i > 1) tmp = min(tmp, shu_rock[i-1][j]);
				if (j > 1) tmp = min(tmp, heng_rock[i][j-1]);
				dp_rock[i][j] = -tmp;
				shu_rock[i][j] = min(dp_rock[i][j], i > 1 ? shu_rock[i-1][j] : 1);
				heng_rock[i][j] = min(dp_rock[i][j], j > 1 ? heng_rock[i][j-1] : 1);
			}
			
			if (i == 1 && j == 1) dp_knight[i][j] = -1;
			else {
				if (i < 3 && j < 3 || i == 1 || j == 1) dp_knight[i][j] = 0;
				else {
					int tmp = 1;
					if (i > 2) tmp = min(tmp, dp_knight[i-2][j-1]);
					if (j > 2) tmp = min(tmp, dp_knight[i-1][j-2]);
					dp_knight[i][j] = -tmp;
				}
			}
			
			if (i == 1 && j == 1) dp_queen[i][j] = shu_queen[i][j] = heng_queen[i][j] = xie_queen[i][j] = -1;
			else {
				int tmp = 1;
				//printf("%d %d \n", i, j);
				if (i > 1) tmp = min(tmp, shu_queen[i-1][j]);
				//printf("%d\n", -tmp);
				if (j > 1) tmp = min(tmp, heng_queen[i][j-1]);
				//printf("%d\n", -tmp);
				if (i > 1 && j > 1) tmp = min(tmp, xie_queen[i-1][j-1]);
				//printf("%d\n", -tmp);
				dp_queen[i][j] = -tmp;
				shu_queen[i][j] = min(dp_queen[i][j], i > 1 ? shu_queen[i-1][j] : 1);
				heng_queen[i][j] = min(dp_queen[i][j], j > 1 ? heng_queen[i][j-1] : 1);
				xie_queen[i][j] = min(dp_queen[i][j], i > 1 && j > 1 ? xie_queen[i-1][j-1] : 1);
				//printf("%d %d %d\n", i, j, dp_queen[i][j]);
			}
		}
		
		
	}
	
	int T; scanf("%d", &T);
		for (; T--; ) {
			int t, n, m; scanf("%d%d%d", &t, &n, &m);
			if (t == 1) print(dp_king[n][m]);
			if (t == 2) print(dp_rock[n][m]);
			if (t == 3) print(dp_knight[n][m]);
			if (t == 4) print(dp_queen[n][m]);
		}
	return 0;
}
