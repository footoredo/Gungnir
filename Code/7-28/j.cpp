#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9 + 7;
const int N = 110;
const int M = N * N;
LL c[N][N], jc[M], jcn[M], f[N][N][N];
LL mi(LL x, int n){
	if(!n) return 1;
	LL tmp = mi(x, n >> 1);
	tmp = tmp * tmp % MOD;
	if(n & 1) tmp = tmp * x % MOD;
	return tmp;
}
LL get_c(int n, int m){
	return m > n ? 0 : (jc[n] * jcn[m] % MOD * jcn[n - m] % MOD);
}
LL work(int mask, int n, int m, int k){
	static int array[4];
	int sum = n * m;
	for(int i = 0; i < 4; i++, (mask >>= 1)){
		array[i] = mask & 1;
		//printf("(%d,%d,%d) ",mask,i,array[i]);
	}
	for(int i = 0; i < 4; i++)
		if(array[i]) sum -= (i & 1) ? n : m;
	for(int i = 0; i < 4; i++)
	for(int j = i; j < 4; j++)
		if(array[i] && array[j] && (i & 1) != (j & 1)) sum++;
	//cout<<array[0]<<' '<<array[1]<<' '<<array[2]<<' '<<array[3]<<' '<<sum<<' '<<k<<' '<<get_c(sum, k)<<endl;
	return get_c(sum, k); 
}
int main(){
	memset(c, 0, sizeof(c));
	jc[0] = jcn[0] = 1;
	for(int i = 1; i < M; i++){
		jc[i] = jc[i - 1] * i % MOD;
		jcn[i] = mi(jc[i], MOD - 2);	
	}
	for(int i = 1; i < N; i++)
	for(int j = 0; j <= i; j++)
		if(i == j || j == 0) c[i][j] = 1;
		else c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
	for(int i = 1; i < N; i++){
		f[i][0][0] = 1;
		for(int j = 1; j < N; j++)
		for(int k = 0; k < N; k++)
			for(int t = 1; t <= i && t <= k; t++) f[i][j][k] = (f[i][j][k] + f[i][j - 1][k - t] * c[i][t]) % MOD;
	}
	int T;cin>>T;
	for(int ii = 1; ii <= T; ii++){
		int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		printf("Case %d: ",ii);
		if(n == 1 || m == 1){
			printf("%d\n",(int)c[n * m][k]);
			continue;
		}
		LL ans = 0;
		for(int i = 0; i < (1<<4); i++){
			ans = (ans + mi(-1, __builtin_popcount(i)) * work(i,n,m,k)) % MOD;
		}
		ans = (ans + 2 * f[n - 1][m][k] - f[n - 2][m][k]) % MOD;
		ans = (ans + 2 * f[m - 1][n][k] - f[m - 2][n][k]) % MOD;
		ans = (ans+ MOD) % MOD;
		printf("%d\n", (int)ans);
	}
}
