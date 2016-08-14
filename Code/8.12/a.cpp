#include<bits/stdc++.h>
using namespace std;
const int N = 2010;
double f[N][N];
int g[N][N];
int n,m;
int main(){
	for(int i = 1; i < N; i++){
		f[0][i] = 0;
	}
	for(int i = 1; i < N; i++)
		f[i][0] = -1;
	memset(g, -1,sizeof(g));
	for(int i = 1; i < N; i++)
		for(int j = 1; j < N; j++){
			f[i][j] = -1;
			int l = (i == 1)?1:g[i-1][j];
			for(int k = l; k <= i; k++){
				if(f[i-k][j] < -0.5) continue;
				if(f[k-1][j-1] < -0.5) continue;
				double t = (f[i-k][j] * (i - k + 1) + f[k-1][j-1] * (k)) / (double)(i + 1) + 1.0;
				if(f[i][j] < -0.5 || t< f[i][j]) {
					g[i][j] = k;
					f[i][j] = t;
				}
				else break;
			}	
			//printf("f[%d][%d] = %.5f  %d %d %d\n",i,j,f[i][j],g[i][j],g[i-1][j], g[i][j-1]);
		}
	while(scanf("%d%d", &n, &m) == 2){	
		printf("%.6f\n",f[n][m]);
	}
}
