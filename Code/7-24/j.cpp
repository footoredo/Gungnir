#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N = 50;
const int MOD = 1e9 + 7;
int fa[N], flag[N], n, m, l_bound[N], r_bound[N], big_vec[N], big_num, state[N], g[N][2], choice[N][2];
LL ans, f[N][2], num[N][2];
vector<pair<int,int> >vec[N];
vector<int> method;
int get_fa(int x){
	if(fa[x]!=x){
		int tmp = get_fa(fa[x]);
		flag[x] ^= flag[fa[x]];
		fa[x] = tmp;
	}
	return fa[x];
}
bool operator < (const vector<int> &a, const vector<int> &b){
	if(a.size() != b.size()) return a.size() > b.size();
	for(int i = 0; i < a.size(); i++)
		if(a[i] != b[i]) return a[i] < b[i];
	return 0;
}
void work(){
	if(state[0] == 1) return;
	state[0] = 0;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	if(state[n] != 0) f[n][1] = g[n][1] = 1;
	if(state[n] != 1) f[n][0] = g[n][0] = 1;
	for(int i = n - 1; i >= 0; i--)
		for(int j = 0; j < 2; j++){
			if((j ^ 1) == state[i]) continue;
			int first_choice = l_bound[i + 1] & 1;
			int second_choice = first_choice ^ 1;
			if(g[i + 1][j ^ second_choice] && num[i + 1][second_choice] > 0){
				g[i][j] = 1;
				f[i][j] = (f[i][j] + f[i + 1][j ^ second_choice] * num[i + 1][second_choice]) % MOD;
				choice[i][j] = second_choice;
			}
			
			if(g[i + 1][j ^ first_choice] && num[i + 1][first_choice] > 0){
				g[i][j] = 1;
				f[i][j] = (f[i][j] + f[i + 1][j ^ first_choice] * num[i + 1][first_choice]) % MOD;
				choice[i][j] = first_choice;
			}
		}
	if(g[0][0]){
		ans = (ans + f[0][0]) % MOD;
		vector<int> tmp;tmp.clear();
		int now = 0;
		for(int i = 0;i<n;i++){
			tmp.push_back(choice[i][now] == (l_bound[i + 1] & 1) ? l_bound[i + 1] : l_bound[i + 1] + 1);
			now ^= choice[i][now];
		}
		if(tmp < method) swap(tmp, method);
	}
}
int main(){
	//freopen("data.in","r",stdin);
	int T;
	cin >> T;
	while (T--){
		scanf("%d%d", &n, &m);
		for(int i = 0; i <= n; i++){
			fa[i] = i;
			flag[i] = 0;
			vec[i].clear();
		}
		for(int i = 1; i <= n; i++){
			scanf("%d%d", &l_bound[i], &r_bound[i]);
			int tot = r_bound[i] - l_bound[i] + 1;
			num[i][l_bound[i] & 1] = (tot + 1) / 2;
			num[i][(l_bound[i] & 1) ^ 1] = tot / 2;
		}
		ans = 0;
		method.clear();
		for(int i = 1; i <= m; i++){
			int u, v, s;
			scanf("%d%d%d", &u, &v, &s);
			u--;
			int fa_u = get_fa(u);
			int fa_v = get_fa(v);
			if(fa_u != fa_v){
				fa[fa_u] = fa_v;
				flag[fa_u] = flag[u] ^ flag[v] ^ s;
			}else{
				if(flag[u] ^ flag[v] != s) ans = -1;
			}
		}
		if(ans < 0){
			puts("0");
			puts("-1");
			continue;
		}
		
		for(int i = 0; i <= n; i++){
			int t = get_fa(i);
			vec[t].push_back(make_pair(i, flag[i]));
		}
		big_num = 0;
		for(int i = 0; i <= n; i++)
			if(vec[i].size() > 1)
				big_vec[big_num++] = i;
		for(int mask = 0; mask < (1 << big_num); mask++){
			for(int i = 0; i <= n; i++) state[i] = -1;
			for(int i = 0; i < big_num; i++){
				int tmp = (mask >> i) & 1, t = big_vec[i];
				for(int j = 0; j < vec[t].size(); j++)
					state[vec[t][j].first] = vec[t][j].second ^ tmp;
			}
			work();
		}
		if(method.size() == 0){
			puts("0");
			puts("-1");
		}
		else{
			printf("%d\n", (int)ans);
			for(int i = 0; i < n; i++)
				printf("%d%c",method[i], i == n - 1 ? '\n' : ' ');
		}
	}
}