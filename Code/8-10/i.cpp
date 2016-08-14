#include<bits/stdc++.h>
using namespace std;
const int N = 2000;
const int MOD = 1e9 + 7;
int f[N][2][2][9][9][2];//col1 col2 num1 num2 connect
int n, m, num_point, p[N], edn;
int type[N];
/*
0:2-not_connect
1:2-connect
2:4
*/
struct cmp {
	int operator ()(const vector<pair<bool, short> > &vec)const{
		int sum = 0;
		for(int i = 0; i < vec.size(); i++){
			sum = sum * 2 + vec[i].first;
			sum = sum * 9 + vec[i].second;
		}
		sum <<= 1;
		if(vec.size() == 4) sum++;
		return sum;
	}
};
unordered_map<vector<pair<bool,short> >, int,cmp> ff, gg;
unordered_map<vector<pair<bool,short> >, int,cmp>::iterator it; 
pair<int,int> zz[N][N];
int len[100];
struct Edge{
	int v, next;
	pair<short, short> e[2];
	Edge(){}
	Edge(int v, int next, int p1, int p2, int q1, int q2):v(v), next(next){
		e[0] = make_pair(p1, p2);
		e[1] = make_pair(q1, q2);
	}
}edge[N];
void addedge(int u, int v, int p1, int p2, int q1, int q2){
	edge[edn] = Edge(v,p[u],p1,p2,q1,q2);
	p[u] = edn++;
	
	edge[edn] = Edge(u,p[v],p2,p1,q2,q1);
	p[v] = edn++;
}
int fafa[5], numnum[5];
int find(int x){
	return x == fafa[x] ? x : (fafa[x] = find(fafa[x]));
}
void update(int &x, int y){
	x += y;
	x %= MOD;
}
void dfs(int x, int fa, int p1, int p2){
	for(int i = p[x]; ~i; i = edge[i].next){
		int y = edge[i].v;
		if(y == fa) continue;
		dfs(y, x, edge[i].e[0].second, edge[i].e[1].second);
	}
	int num = 2;
	if(type[x] == 2) num = 4;
	ff.clear();
	for(int mask = 0; mask < (1 << num); mask++){
		vector<pair<bool, short> >vec;
		int x = mask;
		for(int i = 0; i < num; i++, x >>= 1)
			vec.push_back(make_pair(x % 2, 1));
		ff[vec] = 1;
	}
	for(int ii = p[x]; ~ii; ii = edge[ii].next){
		int y = edge[ii].v, u = edge[ii].e[0].first, v = edge[ii].e[1].first;
		if(y == fa) continue;
		gg.clear();
		for(it = ff.begin(); it != ff.end(); it++){
			vector<pair<bool, short> >bak = it -> first, vec;
			for(int col1 = 0; col1 < 2; col1 ++)
			for(int col2 = 0; col2 < 2; col2 ++)
			for(int s1 = 1; s1 <= m; s1++)
			for(int s2 = 1; s2 <= m; s2++){
				if(f[y][col1][col2][s1][s2][0]){
					vec = bak;
					bool flag = 1;
					if(vec[u].first == col1){
						vec[u].second += s1;
						if(vec[u].second > m) flag = 0;
					}
					if(vec[v].first == col2){
						vec[v].second += s2;
						if(vec[v].second > m) flag = 0;
					}
					if(flag) (gg[vec] += 1LL * it -> second * f[y][col1][col2][s1][s2][0] % MOD) %= MOD;
				}
				if(f[y][col1][col2][s1][s2][1]){
					vec = bak;
					bool flag = 1;
					if(vec[u].first == col1){
						vec[u].second += s1;
						if(vec[u].second > m) flag = 0;
					}else
					if(vec[v].first == col2){
						vec[v].second += s2;
						if(vec[v].second > m) flag = 0;
					}
					if(flag) (gg[vec] += 1LL * it -> second * f[y][col1][col2][s1][s2][1] % MOD) %= MOD;
				}
			}	
		}
		ff = gg;
	}
	for(int i = 1; i < 2; i++)
	for(int j = 1; j < 2; j++)
	for(int k = 0; k <= m; k++)
	for(int t = 0; t <= m; t++)
		f[x][i][j][k][t][0] = f[x][i][j][k][t][1] = 0;
	for(it = ff.begin(); it != ff.end(); it++){
		vector<pair<bool, short> > vec = it -> first;
		for(int i = 0; i < num; i++){
			fafa[i] = i;
			numnum[i] = vec[i].second;
		}
		bool flag = 1;
		if(type[x] != 0){
			for(int i = 0; i < num; i++)
			if(vec[i].first == vec[(i + 1) % num].first){
				int u = find(i);
				int v = find((i + 1) % num);
				if(u != v){
					numnum[u] += numnum[v];
					if(numnum[u] > m) flag = 0;
					numnum[v] = 0;
					fafa[v] = u;
				}
			}		
		}
		if (flag) {
			update(f[x][vec[p1].first][vec[p2].first][numnum[find(p1)]][numnum[find(p2)]][find(p1) == find(p2)], it -> second);
		}
	}
}
int main(){
	//freopen("i.in","r",stdin);
	while(1){
		scanf("%d%d",&n,&m);
		memset(f,0,sizeof(f));
		if(!n && !m) break;
		for(int i = 0; i < n; i++){
			scanf("%d", &len[i]);
			len[i] += 3;
		}
		num_point = 0;
		for(int i = 0; i < n; i++){
			type[++num_point] = 0;
			zz[i][0] = make_pair(num_point, 0);
			zz[i][1] = make_pair(num_point, 1);
			
			type[++num_point] = 0;
			zz[i][2 * len[i] - 2] = make_pair(num_point, 0);
			zz[i][2 * len[i] - 1] = make_pair(num_point, 1);
		}
		static int flag[33][66];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < len[i]; j++)
				flag[i][j * 2] = flag[i][j * 2 + 1] = 0;
		for(int ii = 1; ii < n; ii++){
			int i, j, p, q;
			scanf("%d%d%d%d",&i,&p,&j,&q);
			type[++num_point] = 2;
			zz[i][2 * p + 2] = zz[j][2 * q + 2] = make_pair(num_point, 0);
			zz[i][2 * p + 3] = zz[j][2 * q + 4] = make_pair(num_point, 1);
			zz[i][2 * p + 5] = zz[j][2 * q + 5] = make_pair(num_point, 2);
			zz[i][2 * p + 4] = zz[j][2 * q + 3] = make_pair(num_point, 3);
			flag[i][2 * p + 2] = flag[i][2 * p + 4] = flag[j][2 * q + 2] = flag[j][2 * q + 4] = ii;
		}
		for(int i = 0; i < n; i++)
			for(int j = 1; j < len[i] - 1; j++)
				if(!flag[i][j * 2]){
					type[++num_point] = 1;
					zz[i][j * 2] = make_pair(num_point, 0);
					zz[i][j * 2 + 1] = make_pair(num_point, 1);
				}
		memset(p,-1,sizeof(*p) * (num_point + 1));
		edn = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < len[i] - 1; j++)
				if(zz[i][j * 2].first != zz[i][j * 2 + 2].first){
					addedge(zz[i][j * 2].first, zz[i][j * 2 + 2].first, zz[i][j * 2].second,zz[i][j * 2 + 2].second, zz[i][j * 2 + 1].second,zz[i][j * 2 + 3].second);
				}
		int root = num_point;
		dfs(root, 0, 0, 1);
		int ans = 0;
		for(int col1 = 0; col1 < 2; col1++)
		for(int col2 = 0; col2 < 2; col2++)
		for(int sum1 = 1; sum1 <= m; sum1++)
		for(int sum2 = 1; sum2 <= m; sum2++){
			update(ans, f[root][col1][col2][sum1][sum2][0]);
			update(ans, f[root][col1][col2][sum1][sum2][1]);
		}
		printf("%d\n",ans);
	}
}
