#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10;
const int M = 5e3 + 10;
bitset<N> f[M], character[30], character_new[30];;
char s[N], a[N], ans[N];
int main(){
	int T, n, m;
	scanf("%d", &T);
	while (T--){
		scanf("%d%d", &n, &m);
		scanf("%s", s + 1);
		scanf("%s", a + 1);
		for(int i = 0; i < 26; i++){
			for(int j = 1; j <= n; j++)
				character[i][j] = ((s[j] - 'a') == i);
			character_new[i] = character[i] << 1;
		}
		f[0].set();
		for(int i = 1; i <= m; i++){
			f[i] = (f[i - 1] << 1) & character[a[i] - 'a'];
			if(i >= 2) f[i] |= character[a[i - 1] - 'a'] & (character_new[a[i] - 'a']) & (f[i - 2] << 2) ;
		}
		for(int i = 0; i < n; i++) ans[i] = '0';
		ans[n] = '\0';
		for(int i = m; i <= n; i++)
			if(f[m][i]) ans[i - m] = '1';
		puts(ans);
	}
}