#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1010;
const int MOD = 1e9 + 7;
int a[N], b[N], n, m, ans;
LL f[N][N];
LL s[N][N];
int lowbit(int x){
	return x & (-x);
}
void add(int x, int y, int delt){
	x++;
	y++;
	for(int i = x; i <= n + 1; i+=lowbit(i))
	for(int j = y; j <= m + 1; j+=lowbit(j))
		s[i][j] = (s[i][j] + delt) % MOD;
}
int get(int x, int y){
	x++;
	y++;
	int sum = 0;
	for(int i = x; i; i -= lowbit(i))
	for(int j = y; j; j -= lowbit(j))
		sum = (sum + s[i][j]) % MOD;
	return sum;
}
int main(){
	while(scanf("%d%d", &n, &m) == 2){
		for(int i = 1; i <= n; i++)	scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		for(int i = 0; i <= n + 5; i++)
		for(int j = 0; j <= m + 5; j++)
			f[i][j] = s[i][j] = 0;
		f[0][0] = 1;
		add(0,0,1);
		ans = 0;
		for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i] == b[j]){
				f[i][j] = get(i - 1,j - 1);
				//cout<<i<<' '<<j<<' '<<f[i][j]<<endl;
				add(i,j,f[i][j]);
				ans = (ans + f[i][j]) % MOD;
			}	
		ans = ans % MOD;
		printf("%d\n",(int)ans);
	}
}
