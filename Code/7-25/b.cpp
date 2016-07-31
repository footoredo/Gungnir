#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL N = 2e5 + 10;
const LL M = 2e6 + 10;
const LL INF = 1e18 + 7;
struct Edge{
	LL v, next;
	Edge(){}
	Edge(LL v, LL next):v(v), next(next){}
}edge[M];
struct Extra_Edge{
	LL u, v, c, next;
	Extra_Edge(){}
	Extra_Edge(LL u, LL v, LL c, LL next = 0):u(u), v(v), c(c),next(next){}
}E_E[M],Edge_read[M];
LL edn, p[N], dep[N], fa[N][15], son[N], size[N], place[N], top[N], n, m, now, rest, uu[M], vv[M], cc[M], f[M], pp[N], edn_EE;
LL jzh[N], tree[N * 4];
vector<Extra_Edge> vec;
LL ff(LL x){
	return f[x] == x ? x : f[x] = ff(f[x]);
}
bool cmp(const Extra_Edge &a, const Extra_Edge &b){
	return a.c < b.c;
}
void addedge(LL u, LL v){
	edge[edn] = Edge(v, p[u]);
	p[u] = edn++;
}
void add_Extra_Edge(LL x, LL u, LL v, LL c){
	E_E[edn_EE] = Extra_Edge(u,v,c,pp[x]);
	pp[x] = edn_EE++;
}
void dfs1(LL x){
	for(LL i = 1; i < 15; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	size[x] = 1;
	son[x] = 0;
	dep[x] = dep[fa[x][0]] + 1;
	for(LL i = p[x]; ~i; i = edge[i].next){
		LL y = edge[i].v;
		if(y != fa[x][0]){
			fa[y][0] = x;
			dfs1(y);
			size[x] += size[y];
			if(size[y] > size[son[x]]) son[x] = y;
		}
	}
}
void dfs2(LL x){
	place[x] = ++now;
	if(!son[x]) return;
	top[son[x]] = top[x];
	dfs2(son[x]);
	for(LL i = p[x]; ~i; i = edge[i].next){
		LL y = edge[i].v;
		if(y != fa[x][0] && y != son[x]){
			top[y] = y;
			dfs2(y);
		}
	}
}
LL get_lca(LL u, LL v){
	if(dep[u] < dep[v]) swap(u, v);
	for(LL i = 14; i >= 0; i--)
		if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(LL i = 14; i >= 0; i--)
		if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

LL climb(LL x, LL dep){
	for(LL i = 14; i >= 0; i--)
		if(dep >= (1 << i)){
			dep -= (1 << i);
			x = fa[x][i];
		}
	return x;
}
void change(LL x, LL l, LL r, LL ll, LL rr, LL c){
	if(l >= ll &&  r <= rr) tree[x] = min(tree[x], c);
	else{
		LL mid = (l + r) >> 1;
		if(ll < mid) change(x << 1, l, mid, ll, rr, c);
		if(rr > mid) change((x << 1) + 1, mid, r, ll, rr, c);
	}
}
LL get(LL x, LL l, LL r, LL t){
	if(l + 1 == r) return tree[x];
	LL mid = (l + r) >> 1;
	if(t < mid) return min(tree[x], get(x << 1, l, mid, t));
	else return min(tree[x], get((x << 1) + 1, mid, r, t));
}
void modify(LL x, LL step, LL c){
	while (true){
		LL t = top[x];
		if(dep[x] - dep[t] >= step){
			change(1, 1, n + 1, place[x] - step, place[x] + 1, c);
			return;
		}	
		step -= dep[x] - dep[t] + 1;
		change(1, 1, n + 1, place[t], place[x] + 1, c);
		x = fa[t][0];
		step -= dep[x] - dep[t] + 1;
	}
} 
void update(LL &a, LL &b){
	if(a == INF || b == INF) a = INF;
		else a += b;
}
int main(){
	//freopen("b.in","r",stdin);
	LL T;
	cin >> T;
	while (T--){
		scanf("%d%I64d", &n, &m);
		memset(fa, 0, sizeof(fa));
		memset(p, -1, sizeof(p));
		memset(pp, -1, sizeof(pp));
		edn_EE = edn = rest = 0;
		LL tot = 0;
		for(LL i = 1; i <= n; i++)
			jzh[i] = 0;
		for(LL i = 1; i <= m; i++){
			LL u, v, c, type;
			scanf("%d%I64d%I64d%I64d",&u,&v,&c,&type);
			if(type) c = 0;
			Edge_read[i] = Extra_Edge(u,v,c);
		}
		sort(Edge_read + 1, Edge_read + m + 1, cmp);
		for(LL i = 1; i <= n; i++)
			f[i] = i;
		long long now_jzh = 0;
		for(LL i = 1; i <= m; i++){
			LL u = ff(Edge_read[i].u);
			LL v = ff(Edge_read[i].v);
			if(u == v) {
				rest++;
				uu[rest] = Edge_read[i].u;
				vv[rest] = Edge_read[i].v;
				cc[rest] = Edge_read[i].c;
			}else{
				f[u] = v;
				addedge(Edge_read[i].u, Edge_read[i].v);
				addedge(Edge_read[i].v, Edge_read[i].u);
				now_jzh += Edge_read[i].c;
				jzh[Edge_read[i].u] += Edge_read[i].c;
				jzh[Edge_read[i].v] += Edge_read[i].c;
			}
		}
		dfs1(1);
		top[1] = 1;
		now = 0;
		dfs2(1);
		for(LL i = 1; i <= 4 * n; i++)
			tree[i] = INF;
		for(LL i = 1; i <= rest; i++){
				LL u = uu[i];
				LL v = vv[i];
				LL c = cc[i];
				LL lca = get_lca(u, v);
				LL k_u, k_v;
				if(u != lca && v != lca){
					k_u = climb(u, dep[u] - dep[lca] - 1);
					k_v = climb(v, dep[v] - dep[lca] - 1);
					add_Extra_Edge(lca, k_u, k_v, c);
				}
				if(dep[u] - dep[lca] > 1) modify(u, dep[u] - dep[lca] - 2, c);
				if(dep[v] - dep[lca] > 1) modify(v, dep[v] - dep[lca] - 2, c);
			}
		for(LL k = 1; k <= n; k++){
			LL cnt = 0;
			vec.clear();
			for(LL i = p[k]; ~i; i = edge[i].next)
			{
				cnt++;
				LL y = edge[i].v;
				f[y] = y;
				if(fa[y][0] == k && k != 1) vec.push_back(Extra_Edge(y, fa[k][0], get(1, 1, n + 1, place[y])));
			}
			for(LL i = pp[k]; ~i; i = E_E[i].next) vec.push_back(E_E[i]);
			cnt --;
			sort(vec.begin(), vec.end(), cmp);
			LL ans = 0;
			for(LL i = 0; i < vec.size(); i++){
				LL u = ff(vec[i].u);
				LL v = ff(vec[i].v);
				if(u != v) {
					cnt--;
					update(ans, vec[i].c);
					f[u] = v;
				}
			}
			if(ans == INF || cnt > 0) puts("inf");
				else printf("%I64d\n",ans + now_jzh - jzh[k]);
		}
	}
}
