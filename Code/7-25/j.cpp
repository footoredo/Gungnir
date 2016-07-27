#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 30;
int n, len, K, m, T;
int A_tot[N], B_tot[N];
char cha[11111], chb[11111];

struct KM {
	int w[N][N], lx[N], ly[N], match[N], way[N], slack[N];
	bool used[N];
	void initialization() {
		memset(w, 0, sizeof(w));
		for (int i = 1; i <= n; ++i) {
			match[i] = lx[i] = ly[i] = way[i] = 0;
		}
	}
	void hungary(int x) {
		match[0] = x;
		int j0 = 0;
		for (int j = 0; j <= n; ++j) {
			slack[j] = INF;
			used[j] = false;
		}
		do {
			used[j0] = true;
			int i0 = match[j0], delta = INF, j1;
			for (int j = 1; j <= n; ++j) {
				if (used[j] == false) {
					int cur = -w[i0][j] - lx[i0] - ly[j];
					if (cur < slack[j]) {
						slack[j] = cur;
						way[j] = j0;
					}
					if (slack[j] < delta) {
						delta = slack[j];
						j1 = j;
					}
				}
			}
			for (int j = 0; j <= n; ++j) {
				if (used[j]) {
					lx[match[j]] += delta;
					ly[j] -= delta;
				} else slack[j] -= delta;
			}
			j0 = j1;
		} while (match[j0] != 0);
		
		do {
			int j1 = way[j0];
			match[j0] = match[j1];
			j0 = j1;
		} while (j0);
	}
	int get_ans() {
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			if (match[i] > 0) sum += -w[match[i]][i];
		}
		return sum;
	}
}KM_solver;

int main() {
	scanf("%d", &T);
	for (; T; --T) {
		scanf("%d%d%d\n", &len, &K, &m);
		//for (int i = 1; i <= 26; ++i) A[i].reset();
		gets(cha + 1);
		//for (int i = 1; i <= len; ++i) {
		//	A[ch[i * 2 - 1] - 'A' + 1][i] = 1;
		//}
		//for (int i = 1; i <= 26; ++i) A_tot[i] = A[i].count();
		for (int i = 1; i <= m; ++i) {
			//for (int j = 1; j <= 26; ++j) B[j].reset();
			gets(chb + 1);
			//for (int j = 1; j <= len; ++j) B[ch[j * 2 - 1] - 'A' + 1][j] = 1;
			//for (int j = 1; j <= 26; ++j) B_tot[j] = B[j].count();
			n = 26;
			KM_solver.initialization();
			/*for (int j = 1; j <= n; ++j) {
				for (int k = 1; k <= n; ++k) {
					if (B_tot[k] && A_tot[j]) KM_solver.w[j][k] = (A[j] & B[k]).count();
					else KM_solver.w[j][k] = 0;
				}
			}*/
			for (int j = 1; j <= len; ++j) KM_solver.w[cha[j * 2 - 1] - 'A' + 1][chb[j * 2 - 1] - 'A' + 1]++;
			for (int j = 1; j <= n; ++j) KM_solver.hungary(j);
			int ans = -KM_solver.get_ans();
			printf("%.4f\n", 1.0 * ans / len);
		} 
	}
}
