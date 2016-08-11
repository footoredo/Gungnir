#include<bits/stdc++.h>
using namespace std;
const int N = 510; 
char ch[N];
int a[10][10], len[10], len_ch, length[10], n, lim[10];
int ans_ch[5][1000];
int character[1000], dfs_len[10];
bool ans;
void check(){
	int now = 0;
	/*
	for(int i = 1; i <= n; i++){
		length[i] = 0;
		for(int j = 1; j <= len[i]; j++){
			if(!a[i][j]) ans_ch[i][++length[i]] = ++now;
			else{
				for(int k = 1; k <= length[a[i][j]]; k++)
					ans_ch[i][++length[i]] = ans_ch[a[i][j]][k];				
			}
		}
	}
	for(int i = 1; i <= now; i++)
		character[i] = -1;
	for(int i = 1; i <= length[n]; i++){
		int c = ans_ch[n][i];
		if(character[c] != -1 && character[c] != ch[i]) return;
		character[c] = ch[i];
	}
	ans = 1;
	*/
}
void dfs(int x, int y, int __len){
	if (ans) return;
	if(__len > len_ch) return;
	if(x > n) {
		if(dfs_len[n] == len_ch) check();
	}else{
		for(int i = 0; i < x; i++){
			int new_len = __len + (i == 0 ? 1 : dfs_len[i]);
			a[x][y] = i;
			if(y < lim[x]) dfs(x, y + 1, new_len);
			len[x] = y;
			dfs_len[x] = new_len;
			dfs(x + 1, 1, 0);
		}
	}
}
main(){
	while(scanf("%d",&n) == 1){
		for(int i = 1;  i <= n; i++)
			scanf("%d",&lim[i]);
		scanf("%s",ch + 1);
		len_ch = strlen(ch + 1);
		reverse(lim + 1, lim + n + 1);
		ans = 0;
		dfs(1,1,0);
		if(ans) puts("Yes");
		else puts("No");
	}
}
