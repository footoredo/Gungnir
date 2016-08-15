#include<bits/stdc++.h>
#define stack SSSSSS
using namespace std;
const int N = 5e5 + 10;
const int LOG = 18;
const int LIM = 25000;
struct Edge{
    int v, next;
    Edge(){}
    Edge(int v, int next):v(v), next(next){}
}edge[N], new_edge[N];
struct Query{
    int st, id, k, step, next;
    Query(){}
    Query(int st, int id, int k, int step, int next = -1):st(st), id(id), k(k), step(step), next(next){}
}query[N];
vector<Query> vec[1000];
template <typename T>
__inline void clear(T& container) {
    container.clear(); 
    T(container).swap(container);
}
int new_edn, new_p[N], edn, p[N], dep[N], fa[N][LOG], n, m, ans[N], val[N], edn_q, p_q[N], other_point, father[N], f[N], g[N];
void addedge(int u, int v){
    edge[edn] = Edge(v, p[u]);
    p[u] = edn++;
}
void new_addedge(int u, int v){
    new_edge[new_edn] = Edge(v, new_p[u]);
    new_p[u] = new_edn++;
}
void addquery(int u, int k, int step, int id){
    query[edn_q] = Query(u, id, k, step, p_q[u]);
    p_q[u] = edn_q++;
}
void dfs(int x, int f){
    dep[x] = dep[f] + 1;
    fa[x][0] = f;
    for(int i = 1; i < LOG; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(int i = p[x]; ~i; i = edge[i].next){
        int y = edge[i].v;
        if(y != f) dfs(y, x);
    }
}
int climb(int x, int d){
    for(int i = LOG - 1; i >= 0; i--)
        if((1 << i) <= d){
            x = fa[x][i];
            d -= (1 << i);
        }
    return x;
}
int get_lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = LOG - 1; i >= 0; i--)
        if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = LOG - 1; i >= 0; i--)
        if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0]; 
}
pair<int,int> get_query(int x, int len, int MOD, int ST){
    if(ST > len) return make_pair(-1, -1);
    x = climb(x, ST - 1);
    int t = (len - ST) / MOD;
    other_point = climb(x, t * MOD);
    return make_pair(x, t + 1);
}
int stack[N], top;
void update(int &a, int b){
    if(b > a) a = b;
}
void dfs_big(int x){
    stack[++top] = val[x];
    for(int i = p_q[x]; ~i; i = query[i].next){
        int now = 0, k = query[i].k, step = query[i].step;
        for(int pos = top; step--; pos -= k){
            now = max(now, stack[pos]);
        }
        update(ans[query[i].id], now);
    }
    for(int i = p[x]; ~i; i = edge[i].next){
        int y = edge[i].v;
        if(y != fa[x][0]) dfs_big(y);
    }    
    top--;
}
void build_tree(int x, int kk){
    if(top >= kk) father[x] = stack[top - kk + 1];
        else father[x] =0;
    stack[++top] = x;
    for(int i = p[x]; ~i; i = edge[i].next){
        int y = edge[i].v;
        if(y != fa[x][0]) build_tree(y, kk);
    }
    top--;
} 
pair<int, int> find(int x){
    if(x != f[x]){
        pair<int,int> tmp = find(f[x]);
        f[x] = tmp.first;
        g[x] = max(g[x],tmp.second);
    }
    return make_pair(f[x], g[x]);
}
void dfs_small(int x){
    for(int i = new_p[x]; ~i; i = new_edge[i].next){
        int y = new_edge[i].v;
        if(y != father[x]) dfs_small(y);
    }
    for(int i = p_q[x]; ~i; i = query[i].next){
        int y = query[i].step;
        pair<int,int> now = find(y);
        update(ans[query[i].id], now.second);
    }
    if(x)f[x] = father[x];
}
void work(int kk){    
    memset(p_q, -1, sizeof(*p_q) * (n + 1));
    memset(father + 1, 0, sizeof(*father) * n);
    edn_q = 0;
    memset(new_p, -1, sizeof(*new_p) * (n + 1));
    new_edn = 0;
    for(int i = 0; i < vec[kk].size(); i++)
        addquery(vec[kk][i].st, vec[kk][i].k, vec[kk][i].step, vec[kk][i].id); 
    build_tree(1, kk);
    for(int i = 1; i <= n; i++)
        new_addedge(father[i], i);
    for(int i = 0; i <= n; i++)
        f[i] = i, g[i] = val[i];
    dfs_small(0);
}
int main(){
    int T;
    cin>>T;
    for(int ii = 1; ii <= T; ii++){
        top = 0;
        scanf("%d%d", &n ,&m);
        edn = edn_q = 0;
        memset(p + 1, -1, sizeof(*p) * n);
        memset(p_q + 1, -1, sizeof(*p_q) * n); 
        for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
        for(int i = 1; i < n; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);  
        }
        dfs(1, 0);
        for(int i = 1; i <= m; i++){
            ans[i] = 0;
            int u, v, k;
            scanf("%d%d%d", &u, &v, &k);
            int lca = get_lca(u, v);
            int len = dep[u] - dep[lca] + 1 + dep[v] - dep[lca];
            pair<int,int> query;
            query = get_query(u, dep[u] - dep[lca] + 1, k, k);
            
            if(query.first != -1){
                if(query.second < LIM) addquery(query.first, k, query.second, i);
                else {
                    assert(k <1000);
                    vec[k].push_back(Query(other_point, i, k, query.first));
                }
            }
            
            query = get_query(v, dep[v] - dep[lca], k, (len % k) + 1);
            if(query.first != -1){
                if(query.second < LIM) addquery(query.first, k, query.second, i);
                else {
                    assert(k < 1000);
                    vec[k].push_back(Query(other_point, i, k, query.first));
                }
            }
            
        }
        top = 0;
        dfs_big(1);
        for(int kk = 1; kk < 1000; kk++)
            if(vec[kk].size()){
                work(kk);
                clear(vec[kk]);
            }
        
        printf("Case #%d:\n",ii);
        for(int i = 1; i <= m; i++)
            printf("%d\n", ans[i]);
    }
}
