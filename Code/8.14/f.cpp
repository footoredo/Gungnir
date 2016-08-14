#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int DD = 1000;
const int N = 300;
const int M = 30;
int num[M], n, m, k, kk;
int c[2000][2000], f[N], px[M][N], py[M][N];
int step_x[M][2100], step_y[M][2100];
int calc(int x){
	if(x < 0) x *= -1;
	if(x > k || (x & 1) != (k & 1)) return 0;
	return c[k][x + k >> 1];
}
int main(){
	for(int i = 0; i < 2000; i++)
		for(int j = 0; j <= i; j++)
			if(i == j || j == 0) c[i][j] = 1;
			else c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD; 
	int T;
	cin>>T;
	for(int ii = 1; ii <= T; ii++){
		scanf("%d%d%d",&n,&m,&k);
		kk = k & 1;
		for(int i = 1; i <= m; i++) scanf("%d", &num[i]);
		for(int i = 1; i <= m; i++){
			for(int j = 1; j <= num[i]; j++){
				int x, y;
				scanf("%d%d", &x, &y);
				px[i][j] = x + y;
				py[i][j] = x - y;
			}
			for(int d = -1000; d <= 1000; d++){
				int now_x = 1, now_y = 1;
				for(int j = 1; j <= num[i]; j++){
					now_x = (1LL * now_x * calc(px[i][j] - d)) % MOD;
					now_y = (1LL * now_y * calc(py[i][j] - d)) % MOD;
				}
				step_x[i][d + DD] = now_x;
				step_y[i][d + DD] = now_y;
			}
		}
		f[0] = 1;
		int k_min = -k + 1000;
		int k_max = k + 1000;
		for(int i = 1; i <= m; i++){
			f[i] = 0;
			for(int dx = k_min; dx <= k_max; dx +=2)
				for(int dy = k_min; dy <= k_max; dy +=2){
					int now = 1, xx = px[i][1] + dx, yy = py[i][1] + dy;
					for(int j = i; j >= 1; j--){
						now = 1LL * now * step_x[j][xx] % MOD * step_y[j][yy] % MOD;
						if(!now) break;
						if(i - j & 1) f[i] = (f[i] - 1LL * now * f[j - 1]) % MOD;
							else f[i] = (f[i] + 1LL * now * f[j - 1]) % MOD;
					}
				}
		}
		int ans = (f[m] + MOD) % MOD;
		printf("Case #%d: %d\n",ii, ans);
	}
}