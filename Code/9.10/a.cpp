#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
typedef long long LL;
struct Matrix{
	LL a[2][2];
}m0;
Matrix operator * (const Matrix &a, const Matrix &b){
	Matrix c;
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < 2; j++){
		c.a[i][j] = (a.a[i][0] * b.a[0][j] + a.a[i][1] * b.a[1][j]) % MOD;
	}
	return c;
}
LL f(LL n){
	if(n == 1) return 1;
	if(n == 2) return 3;
	n -= 2;
	Matrix tmp = m0;
	Matrix ans;
	ans.a[0][0] = ans.a[1][1] = 1;
	ans.a[0][1] = ans.a[1][0] = 0;
	for(LL i = 1; i <= n; i <<= 1){
		if(n & i) ans = ans * tmp;
		tmp = tmp * tmp;
	}
	return (ans.a[1][0] + 3 * ans.a[1][1]) % MOD;
}
LL a[1000], b[1000], top, ans, n;
LL mi(LL x, LL n){
	LL ans = 1;
	for(LL i = 1; i <= n; i <<= 1){
		if(n & i) ans = ans * x % MOD;
		x = x * x % MOD;
	}
	return ans;
}
void dfs(LL x, LL phi, LL d){
	if(x > top){
		ans += phi * d % MOD * f(n / d);
		ans %= MOD;
		return;
	}
	LL tmp = (a[x] - 1) * mi(a[x], MOD - 2) % MOD;
	for(LL i = 0; i <= b[x]; i++){
		if(i == 0) dfs(x + 1, phi, d);
		else dfs(x + 1, phi * tmp % MOD, d);
		d = d * a[x] % MOD;
	}
}
int main(){
	m0.a[0][0] = 0;
	m0.a[0][1] = m0.a[1][0] = m0.a[1][1] = 1;
	while (cin>>n){
		if(n == 1){
			cout<<2<<endl;
			continue;
		}
		LL n_bak = n;
		top = 0;
		for(LL i = 2; i * i <= n; i++)
		if(n % i == 0){
			a[++top] = i;
			b[top] = 0;
			while ((n % i)==0){
				n /= i;
				b[top]++;
			}
		}
		if(n!=1){
			a[++top] = n;
			b[top] = 1;
		}
		n = n_bak;
		ans = 0;
		dfs(1, 1, 1);
		ans = ans * mi(n, MOD - 2) % MOD;
		cout<<ans<<endl;
	}
}
