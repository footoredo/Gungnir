#include <bits/stdc++.h>
using namespace std;

const int D = 20;
const int maxq = 20;
const int maxn = 22222;
int n, Q, K, q[maxq], H;
bool flag;

struct unionset {
	int node, f, tag;
	unionset() {};
	unionset(int x, int y, int z): node(x), f(y), tag(z) {}; 
} fa[D][maxn];

bool cmp(int p, int q) {
	return fa[H][p].node < fa[H][q].node;
}

int getfa(int h, int u) {
	if (fa[h][u].node == u) return u;
	int tmp = getfa(h, fa[h][u].node);
	fa[h][u].f ^= fa[h][fa[h][u].node].f;
	fa[h][u].node = tmp;
	return tmp;
}

void bomb(int k) {
	if (flag) printf("The first %d facts are conflicting.\n", k);
}

int main() {
	//freopen("E.in", "r", stdin);
	//freopen("WA.out", "w", stdout);
	
	int T = 0;
	while (1) {
		scanf("%d%d", &n, &Q);
		if (n == 0) return 0;
		printf("Case %d:\n", ++T);
		for (int h = 0; h < D; ++h)
			for (int i = 1; i <= n; ++i)
				fa[h][i] = unionset(i, 0, -1);
		flag = true;
		int facts = 0;
		for (int ques = 1; ques <= Q; ++ques) {
		
			char order[5], buf[30];
			scanf("%s", order);
			if (order[0] == 'I') {
				facts++;
				gets(buf);
				if (!flag) continue;
				int x, y, z; int t = sscanf(buf, "%d%d%d", &x, &y, &z);
				//cout << x << " " << y << " " << z << endl;
				if (t == 2) {
					x++;
					//cout << x << " " << y << endl;
					for (int h = 0; h < D; ++h, y >>= 1) {
						 int fx = getfa(h, x), temp = y & 1;
						// cout << "modify: " << h << " " << y << " " << temp << endl; 
						 if (fa[h][fx].tag != -1) {
						 	if ((fa[h][x].f ^ fa[h][fx].tag) != temp) {
						 		bomb(facts);
						 		flag = false;
						 		continue;
						 	}
						 } else fa[h][fx].tag = fa[h][x].f ^ temp;
					}
				} else {
					x++, y++;
					//cout << x << " " << y << " " << z << endl;
					for (int h = 0; h < D; ++h, z >>= 1) {
						int temp = z & 1, fx = getfa(h, x), fy = getfa(h, y);
						//cout << x << " " << y << " " << fx << " " << fy << endl;
						if (fx == fy) {
							if ((fa[h][x].f ^ fa[h][y].f) != temp) {
						 		bomb(facts);
								flag = false;
								continue;
							}
						} else {
							if (fa[h][fx].tag > -1 && fa[h][fy].tag > -1) {
								//cout << temp << " " << (temp ^ fa[h][x].f ^ fa[h][y].f )<< " " << (fa[h][x].tag ^ fa[h][y].tag) << endl;
								if ((temp ^ fa[h][x].f ^ fa[h][y].f) != (fa[h][fx].tag ^ fa[h][fy].tag)) {
						 			bomb(facts);
									flag = false;
									continue;
								}
							} else {
								fa[h][fx].node = fy;
								fa[h][fx].f = temp ^ fa[h][x].f ^ fa[h][y].f;
								if (fa[h][fy].tag == -1 && fa[h][fx].tag > -1) fa[h][fy].tag = fa[h][fx].tag ^ fa[h][fx].f;
						//cout << fx << " " << fy << endl;
							}
						}
					}
				}
			} else {
				scanf("%d", &K);
				for (int i = 1; i <= K; ++i) {
					scanf("%d", &q[i]);
					q[i]++;
				}
				if (!flag) continue;
				for (int h = 0; h < D; ++h)
					for (int i = 1; i <= K; ++i)
						getfa(h, q[i]);
				//sort(q + 1, q + K + 1, cmp);
				int ans = 0;
				for (int h = 0; h < D; ++h) {
					H = h;
					sort(q + 1, q + K + 1, cmp);
					int left = 1, nowans = 0;
					while (left <= K) {
						int right = left;
						while (right < K && fa[0][q[right + 1]].node == fa[0][q[right]].node) ++right;
						int fx = getfa(h, q[left]);
						if ((right - left + 1) % 2 == 0) {
							for (int i = left; i <= right; ++i)	{
								getfa(h, q[i]);
								if (nowans > -1) nowans ^= fa[h][q[i]].f;
							}
						} else {
							if (fa[h][fx].tag == -1) {
								nowans = -1;
								//break;
							} else {
								for (int i = left; i <= right; ++i) {
									getfa(h, q[i]);
									if (nowans > -1)nowans ^= fa[h][q[i]].f ^ fa[h][fx].tag;
								}
							}
						}
						left = right + 1;
					}
					if (nowans == -1) {
						ans = -1;
					} else 
					if (ans != -1) ans |= nowans << h;
					//cout << "Getans: " << h << " " << nowans << " " << ans << endl;
				}
				if (ans == -1) printf("I don't know.\n");
				else printf("%d\n", ans);
			}
/*for (int h = 0; h < D; ++h)
	for (int i = 1; i <= n; ++i)
		cout << h << " " << i << " " << fa[h][i].node << " " << fa[h][i].f << " " << fa[h][i].tag << endl;
puts("-------------------------");*/
		}
		puts("");

	}
}
