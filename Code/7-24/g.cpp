#include <bits/stdc++.h>
#define stack STACK123
using namespace std;

const int N=1000;
const int INF = 1e9;
const int inf = 1e9;
int n, n1, n2, nn, m, cc, tot, x, y, Q, mp[N][N], dist[N][N], from[N][N], col[N], pri_col[N], tmpmatch[N], f[N], g1[N], g2[N], ansX[N * N], ansY[N * N], tmp[N], used[N], seq[N], stack[N];
char ch[N];
struct KM{
	int w[N][N];
	int lx[N], ly[N], match[N],way[N], slack[N];
	bool used[N];
	void initialization(){
		for(int i = 1; i <= n; i++){
			match[i] = 0;
			lx[i] = 0;
			ly[i] = 0;
			way[i] = 0;
		}
	}
	void hungary(int x){//for i(1 -> n) : hungary(i);
		match[0] = x;
		int j0 = 0;
		for(int j = 0; j <= n; j++){
			slack[j] = INF;
			used[j] = false;
		}
		
		do{
			used[j0] = true;
			int i0 = match[j0], delta = INF, j1;
			for(int j = 1; j <= n; j++){
				if(used[j] == false){
					int cur = -w[i0][j] - lx[i0] - ly[j];
					if(cur < slack[j]){
						slack[j] = cur;
						way[j] = j0;
					}
					if(slack[j] < delta){
						delta = slack[j];
						j1 = j;
					}
				}
			}
			for(int j = 0; j <= n; j++){
				if(used[j]){
					lx[match[j]] += delta;
					ly[j] -= delta;
				}
				else slack[j] -= delta;
			}
			j0 = j1;
		}while (match[j0] != 0);
		
		do{
			int j1 = way[j0];
			match[j0] = match[j1];
			j0 = j1;
		}while(j0);
	}
	
	int get_ans(){//maximum ans
		int sum = 0;
		for(int i = 1; i<= n; i++)
			if(match[i] > 0) sum += -w[match[i]][i];
		return sum;
	}
}KM_solver;

bool dfs(int k, int c) {
	col[k] = c; used[k] = 1;
	for (int i = 1; i <= mp[k][0]; ++i)
		if (col[mp[k][i]] == -1) dfs(mp[k][i], c ^ 1);
		else {
			if (c == col[mp[k][i]]) return false;
		}
	return true;
}
int now_col[N];
void getans(int u, int v) {
	int ind = 0, k = v, top, c = now_col[u] ^ 1;
	//cout << "  --  "<<u << " "  << v << " " << c << " " << col[u] << " " << col[v] << endl;
	for (; k; k = from[u][k]) tmp[++ind] = k;
	reverse(tmp + 1, tmp + ind + 1);
	top = 1; stack[1] = u;
	for (int i = 2; i <= ind; ++i)
		if (now_col[tmp[i]] != c) stack[++top] = tmp[i];
		else {
			stack[++top] = tmp[i];
			while (top > 1) {
				++tot; ansX[tot] = stack[top - 1]; ansY[tot] = stack[top];
				
				//cout<<ansX[tot]<<' '<<ansY[tot]<<' '<<pri_col[ansX[tot]]<<' '<<pri_col[ansY[tot]]<<endl;
				--top;
			}
			stack[top] = tmp[i];
		}
	swap(now_col[u], now_col[v]);
	while (top > 1) {
		++tot; ansX[tot] = stack[top - 1]; ansY[tot] = stack[top];
		--top;
	}
}

int main() {
	scanf("%d", &Q);
	for (; Q; --Q) {
		scanf("%d%d", &nn, &m);
		scanf("%s", ch + 1);
		for (int i = 1; i <= nn; ++i) mp[i][0] = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			mp[x][++mp[x][0]] = y;
			mp[y][++mp[y][0]] = x;
		}
		for (int i = 1; i <= nn; ++i) now_col[i] = pri_col[i] = ch[i] - '0';
		for (int i = 1; i <= nn; ++i) col[i] = -1;
		
		for (int i = 1; i <= nn; ++i) {
			for (int j = 1; j <= nn; ++j) dist[i][j] = inf;
			int h = 1, t = 1;
			seq[1] = i; dist[i][i] = 0; from[i][i] = 0;
			for (; h <= t; ++h) {
				int u = seq[h];
				for (int k = 1; k <= mp[u][0]; ++k) {
					int v = mp[u][k];
					if (dist[i][v] == inf) {
						dist[i][v] = dist[i][u] + 1;
						from[i][v] = u;
						seq[++t] = v;
					}
				}
			}
		}
		
		int ans = 0;
		tot = 0;
		memset(used, 0, sizeof(used));
		for (int i = 1; i <= nn; ++i) {
			if (used[i]) continue;
		//cout << i << endl;
			if (!dfs(i, 0)) {
				ans = -1;
				break;
			}
//for (int j = 1; j <= nn; ++j) cout << col[j] << " "; cout << endl;
			int nowans = inf, cc;
			for (int c = 0; c < 2; ++c) {
				n1 = 0; n2 = 0;
				for (int j = 1; j <= nn; ++j) col[j] ^= c;
				for (int j = 1; j <= nn; ++j)
					if (dist[i][j] < inf){
						if (col[j] == 0) {
							if (pri_col[j] != 0) {
								f[j] = ++n1; g1[n1] = j;
								//cout << "No.1:" << j << endl; 
							}
						} else {
							if (pri_col[j] == 0) {
								f[j] = ++n2; g2[n2] = j;
								//cout << "No.2:" << j << endl; 
							}
						}
					}
				for (int j = 1; j <= nn; ++j) col[j] ^= c;
					
				//cout << c << " " << n1 << " " << n2 << endl;
				if (n1 != n2) continue;
				n = n1;
				if (n == 0) {
					nowans = 0;
					break;
				}
				KM_solver.initialization();
				for (int j = 1; j <= n; ++j)
					for (int k = 1; k <= n; ++k)
						KM_solver.w[j][k] = -dist[g1[j]][g2[k]];
/*for (int t1 = 1; t1 <= n; ++t1) {
	for (int t2 = 1; t2 <= n; ++t2)
	 	cout << KM_solver.w[t1][t2] << " ";
	 cout << endl;
}*/
				for (int j = 1; j <= n; ++j) KM_solver.hungary(j);
				int tmpans = KM_solver.get_ans();
				if (tmpans < nowans) {
					cc = c;
					for (int j = 1; j <= n; ++j) tmpmatch[j] = KM_solver.match[j];
					nowans = tmpans;
				}
			}
			if (nowans == inf) {
				ans = -1;
				break;
			}
			if (nowans == 0) {
				continue;
			}
			ans += nowans;
			n1 = 0; n2 = 0;
			for (int j = 1; j <= nn; ++j) col[j] ^= cc;
			for (int j = 1; j <= nn; ++j)
				if (dist[i][j] < inf){
					if (col[j] == 0) {
						if (pri_col[j] != 0) {
							f[j] = ++n1; g1[n1] = j;
						}
					} else {
						if (pri_col[j] == 0) {
							f[j] = ++n2; g2[n2] = j;
						}
					}
				}
			for (int j = 1; j <= nn; ++j) col[j] ^= cc;
			n = n1;
//for (int j = 1; j <= n; ++j) cout << g1[tmpmatch[j]] << " " << g2[j] << endl;
			for (int j = 1; j <= n; ++j) getans(g1[tmpmatch[j]], g2[j]);
		}
		
		if (ans == -1) printf("-1\n");
		else {
			printf("%d\n", ans);
			for (int i = 1; i <= tot; ++i) printf("%d %d\n", ansX[i], ansY[i]);
		}
	}
}
