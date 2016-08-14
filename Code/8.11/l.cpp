#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
struct Edge{
	int v, next;
	Edge(){}
	Edge(int v, int next):v(v), next(next){}
}edge[N];
int dep[N], top[N], fa[N], size[N], son[N], S[N], T[N], p[N], edn, n, m, Time;
int ch[N][26], fail[N];
LL tree[N * 4], tag[N * 4];
vector<pair<int,int> > vec;
void addedge(int u, int v){
	edge[edn] = Edge(v, p[u]);
	p[u] = edn++;
}
void dfs1(int x){
	son[x] = 0;
	size[x] = 1;
	for(int i = p[x]; ~i; i = edge[i].next){
		int y = edge[i].v;
		dep[y] = dep[x] + 1;
		fa[y] = x;
		dfs1(y);
		size[x] += size[y];
		if(size[y] > size[son[x]]) son[x] = y;
	}
}
void dfs2(int x){
	S[x] = ++Time;
	if(son[x]){
		top[son[x]] = top[x];
		dfs2(son[x]);
		for(int i = p[x]; ~i; i = edge[i].next){
			int y = edge[i].v;
			if(y != son[x]){
				top[y] = y;
				dfs2(y);
			}
		}
	}
	T[x] = Time;
}
void init(){
	static int ff[N];
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 26; j++)
			ch[i][j] = -1;
	for(int i = 2; i <= n; i++){
		static char cc[5];
		scanf("%d%s", &ff[i], cc);
		ch[ff[i]][cc[0] - 'a'] = i;
	}
	static queue<int> q;
	while (!q.empty()) q.pop();
	for(int i = 0; i < 26; i++)
		if(~ch[1][i]){
			fail[ch[1][i]] = 1;
			q.push(ch[1][i]);
		}
	while (!q.empty()){
		int x = q.front();
		q.pop();
		for(int i = 0; i < 26; i++)
			if(~ch[x][i]){
				int k = fail[x];
				while(k != 1 && ch[k][i] == -1) k = fail[k];
				if(ch[k][i] != -1) k = ch[k][i];
				fail[ch[x][i]] = k;
				q.push(ch[x][i]);
			}
	}
	memset(p + 1, -1, sizeof(*p) * n);
	edn = 0;
	for(int i = 2; i <= n; i++)
		addedge(fail[i], i);
	dep[1] = 1;
	dfs1(1);
	top[1] = 1;
	Time = 0;
	dfs2(1);
	memset(tree + 1, 0, sizeof(*tree) * 4 * n);
	memset(tag + 1, 0, sizeof(*tag) * 4 * n);
}
void work(){
	vector<pair<int,int> > tmp;
	sort(vec.begin(), vec.end());
	int l = vec[0].first;
	int r = vec[0].second;
	for(int i = 1; i < vec.size(); i++){
		if(vec[i].first <= r + 1) r = max(r, vec[i].second);
		else{
			tmp.push_back(make_pair(l,r));
			l = vec[i].first;
			r = vec[i].second;
		}
	}
	tmp.push_back(make_pair(l, r));
	vec = tmp;
}
void add(int x, int l, int r, int ll, int rr){
	if(l >= ll && r <= rr){
		tag[x] ++;
		tree[x] += r - l;
		return;
	}	
	int mid = l + r >> 1;
	if(ll < mid) add(x << 1, l, mid, ll, rr);
	if(rr > mid) add((x << 1) + 1, mid, r, ll, rr);
	tree[x] = tree[x << 1] + tree[(x << 1) + 1] + tag[x] * (r - l);
}
LL get(int x, int l, int r, int ll, int rr, LL now_tag){
	if(l >= ll && r <= rr) return tree[x] + now_tag * (r - l);
	int mid = l + r >> 1;
	LL sum = 0;
	if(ll < mid) sum += get(x << 1, l, mid, ll, rr, now_tag + tag[x]);
	if(rr > mid) sum += get((x << 1) + 1, mid, r, ll, rr, now_tag + tag[x]);
	return sum;
}
void __change(){
	int m, t;
	vec.clear();
	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		scanf("%d", &t);
		vec.push_back(make_pair(S[t], T[t]));
	}
	work();
	for(int i = 0; i < vec.size(); i++)
		add(1, 1, n + 1, vec[i].first, vec[i].second + 1);
}
LL __get(){
	int m, x;
	vec.clear();
	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		scanf("%d",&x);
		while(x){
			int t = top[x];
			vec.push_back(make_pair(S[t], S[x]));
			x = fa[t];
		}
	}
	work();
	LL sum = 0;
	for(int i = 0; i < vec.size(); i++)
		sum += get(1, 1, n + 1, vec[i].first, vec[i].second + 1, 0);
	return sum;
}
int main(){
	int T;
	cin>>T;
	while (T--) {
		init();
		int m, type;
		scanf("%d", &m);
		while (m--){
			scanf("%d", &type);
			if(type == 1) __change();
				else printf("%I64d\n", __get());
		}
	}
}
