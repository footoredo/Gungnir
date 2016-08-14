#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Trie_Node{
	int ch[26];
	void clear(){
		memset(ch, 0, sizeof(ch));
	}
}Trie[N];
struct Node{
	int l, r, sum;
	void clear(){
		l = r = sum = 0;
	}
}seg[4000000];
int num_Trie_Node, n, m, num_node;
int a[N], ll[N], rr[N], pre[N], last[N], root[N];
char ch[N];
int new_node(){
	seg[++num_node].clear();
	return num_node;
}
void add(int &rt, int u, int l, int r, int tar){
	rt = new_node();
	seg[rt].sum = seg[u].sum + 1;
	if(l + 1 == r) return;
	int mid = l + r >> 1;
	if(tar < mid){
		seg[rt].r = seg[u].r;
		add(seg[rt].l, seg[u].l, l, mid, tar);
	}else{
		seg[rt].l = seg[u].l;
		add(seg[rt].r, seg[u].r, mid, r, tar);
	}
}
int get(int r1, int r2, int l, int r, int tar){
	if(r <= tar) return seg[r2].sum - seg[r1].sum;
	if(l >= tar) return 0;
	int mid = l + r >> 1;
	return get(seg[r1].l, seg[r2].l, l, mid, tar) + get(seg[r1].r, seg[r2].r, mid, r, tar);
}
int main(){
	while(scanf("%d",&n)==1){
		int num = 0;
		num_Trie_Node = 1;
		Trie[1].clear();
		for(int i = 1; i <= n; i++){
			ll[i] = num + 1;
			scanf("%s",ch);
			int len = strlen(ch);
			int now = 1;
			for(int j = 0; j < len; j++){
				if(!Trie[now].ch[ch[j] - 'a']){
					Trie[++num_Trie_Node].clear();
					Trie[now].ch[ch[j] - 'a'] = num_Trie_Node;
				}
				now = Trie[now].ch[ch[j] - 'a'];
				a[++num] = now;
			}
			rr[i] = num;
		}
		root[0] = 1;
		num_node = 1;
		seg[1].clear();
		seg[0].clear();
		for(int i = 1; i <= num_Trie_Node; i++)
			last[i] = 0;
		for(int i = 1; i <= num; i++){
			pre[i] = last[a[i]];
			last[a[i]] = i;
			add(root[i], root[i - 1], 0, num + 1, pre[i]);
		}
		int Z = 0;
		scanf("%d",&m);
		while(m--){
			int l, r;
			scanf("%d%d",&l,&r);
			l = (l + Z) % n + 1;
			r = (r + Z) % n + 1;
			if(l > r) swap(l, r);
			Z = get(root[ll[l]-1], root[rr[r]], 0, num + 1, ll[l]);
			printf("%d\n",Z);
		}
	}
}
