#include <bits/stdc++.h>
#define foreach(i, v) for (__typeof((v).begin()) i = ((v).begin()); i != ((v).end()); ++ i)

const int N = 111111;
int n, m;

int adj[N], nxt[N*2], v[N*2], e;
__inline void ins(int u0, int v0) {
    v[e] = v0; nxt[e] = adj[u0]; adj[u0] = e++;
}

typedef std::pair<std::pair<int, int>, int> Event;
std::vector<Event> events[N];
__inline void clear(std::vector<Event>& v) {
    v.clear(); 
    std::vector<Event>(v).swap(v);
}

int DFN, in[N], out[N], anc[N][20], dep[N];
void dfs(int u, int p) {
    in[u] = ++DFN;
    clear(events[DFN]);
    dep[u] = dep[p] + 1;
    anc[u][0] = p;
    for (int i = 1; anc[u][i - 1]; ++ i)
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int e = adj[u]; ~e; e = nxt[e])
        if (v[e] != p) dfs(v[e], u);
    out[u] = DFN;
}

__inline int leap_to(int u, int gap) {
    assert(gap < dep[u]);
    for (int i = 0; gap; gap >>= 1, ++ i)
        if (gap & 1) u = anc[u][i];
    return u;
}

__inline int lca(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    u = leap_to(u, dep[u] - dep[v]);
    assert(dep[u] == dep[v]);
    if (u == v) return u;
    for (int i = std::__lg(dep[u]); i >= 0; -- i) {
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i]; v = anc[v][i];
        }
    }
    assert(anc[u][0] == anc[v][0]);
    return anc[u][0];
}

__inline int spot(int u, int v) {
    assert(dep[v] > dep[u]);
    int ret = leap_to(v, dep[v] - dep[u] - 1);
    assert(anc[ret][0] == u);
    return ret;
}

__inline std::pair<int, int> get_subtree(int u) {
    if (u < 1 || u > n) {
        while (1) ++in[u];
    }
    return std::make_pair(in[u], out[u]);
}

__inline void add_rect(std::pair<int, int> from, std::pair<int, int> to, int w) {
    if (from.first > from.second || to.first > to.second) return;
    events[from.first].push_back(std::make_pair(to, w));
    if (from.second < n) events[from.second + 1].push_back(std::make_pair(to, -w));
}

int same[N];

struct Node {
    int tag, value;
    Node *ch[2];
    Node () {
        tag = value = 0;
        ch[0] = ch[1] = NULL;
    }
    __inline void push() {
        if (!tag) return;
        ch[0]->tag += tag; 
        ch[1]->tag += tag; 
        value += tag; tag = 0;
    }
    __inline void update() {
        ch[0]->tag += tag; 
        value = std::max(ch[0]->value + ch[0]->tag,
                ch[1]->value + ch[1]->tag);
    }
} *root;

Node *build_tree(int l, int r) {
    Node *T = new Node;
    if (l < r) {
        int mid = (l + r) / 2;
        T->ch[0] = build_tree(l, mid);
        T->ch[1] = build_tree(mid + 1, r);
    }
    return T;
}

void destruct_tree(Node *T) {
    if (T == NULL) return;
    destruct_tree(T->ch[0]);
    destruct_tree(T->ch[1]);
    delete T;
}

void add(Node *T, int l, int r, int ql, int qr, int x) {
    if (ql <= l && qr >= r) T->tag += x;
    else {
        T->push();
        int mid = (l + r) / 2;
        if (ql <= mid) add(T->ch[0], l, mid, ql, qr, x);
        if (qr > mid) add(T->ch[1], mid + 1, r, ql, qr, x);
        T->update();
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T; std::cin >> T;
    for (int curT = 1; curT <= T; ++ curT){
        std::cin >> n >> m;
        memset(adj + 1, -1, sizeof(*adj) * n); e = 0;
        for (int i = 0; i < n - 1; ++ i) {
            int u, v; std::cin >> u >> v;
            ins(u, v); ins(v, u);
        }

        memset(in + 1, 0, sizeof(*in) * n);
        DFN = 0; dfs(1, 0);

        memset(same + 1, 0, sizeof(*same) * n);
        for (; m--; ) {
            int u, v, w; std::cin >> u >> v >> w;
            int p = lca(u, v);
            if (u != p && v != p) {
                add_rect(get_subtree(u), get_subtree(v), w);
            }
            else if (u == p && v != p) {
                add_rect(std::make_pair(1, n), get_subtree(v), w);
                add_rect(get_subtree(spot(u, v)), get_subtree(v), -w);
            }
            else if (u != p && v == p) {
                add_rect(get_subtree(u), std::make_pair(1, n), w);
                add_rect(get_subtree(u), get_subtree(spot(v, u)), -w);
            }
            else {
                same[u] += w;
            }
        }

        int base = 0;
        for (int i = 1; i <= n; ++ i)
            if (same[i]) {
                base += same[i];
                std::pair<int, int> left(1, in[i] - 1),
                    right(out[i] + 1, n);
                add_rect(left, left, -same[i]);
                add_rect(left, right, -same[i]);
                add_rect(right, left, -same[i]);
                add_rect(right, right, -same[i]);
                for (int e = adj[i]; ~e; e = nxt[e]) 
                    if (v[e] != anc[i][0])
                        add_rect(get_subtree(v[e]), get_subtree(v[e]), -same[i]);
            }

        int ans = -1e9;
        root = build_tree(1, n);
        for (int i = 1; i <= n; ++ i) {
            foreach(it, events[i]) add(root, 1, n, it->first.first, it->first.second, it->second);
            int tmp = root->tag + root->value;
            if (tmp + base > ans) ans = tmp + base;
        }

        std::cout << "Case #" << curT << ": " << ans << std::endl;
        destruct_tree(root); root = NULL;
    }

    return 0;
}
