#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11111;
//const int MAXN = 5;
int nxtA[MAXN], nxtB[MAXN];
char A[MAXN], B[MAXN], ans[MAXN];
bitset<MAXN> f[MAXN], g[MAXN], SA[MAXN], SB[MAXN];

int main() {
	while (scanf("%s%s", A + 1, B + 1) != EOF) {
		int l = strlen(A + 1);
		for (int i = 0; i <= l; ++i) f[i].reset(), g[i].reset(), SA[i].reset(), SB[i].reset();
		nxtA[0] = nxtA[1] = nxtB[0] = nxtB[1] = 0;
		A[0] = B[0] = '?';
		SA[0].reset(); SB[0].reset();
		SA[0][l] = SA[1][l] = SA[1][l - 1] = SB[0][0] = SB[1][0] = SB[1][1] = 1;
		for (int i = 2; i <= l; ++i) {
			int j = nxtA[i - 1];
			while (j && A[j + 1] != A[i]) j = nxtA[j];
			if (A[j + 1] == A[i]) j++;
			nxtA[i] = j;
			SA[i] = SA[j];
			SA[i][l - i] = 1;
		}
		for (int i = 2; i <= l; ++i) {
			int j = nxtB[i - 1];
			while (j && B[j + 1] != B[i]) j = nxtB[j];
			if (B[j + 1] == B[i]) j++;
			nxtB[i] = j;
			SB[i] = SB[j];
			SB[i][i] = 1;
		}
		
		f[0].reset(); g[0].reset();
		int j = 0;
		for (int i = 1; i <= l; ++i) {
			while (j && B[j + 1] != A[i]) j = nxtB[j];
			if (B[j + 1] == A[i]) j++;
			f[i] = SB[j];
		}
		j = 0;
		for (int i = 1; i <= l; ++i) {
			while (j && A[j + 1] != B[i]) j = nxtA[j];
			if (A[j + 1] == B[i]) j++;
			g[i] = SA[j];
		}
		for (int i = 1; i <= l; ++i) {
			if ((f[i] & (g[i] >> (l - i))).count()) ans[i - 1] = '1';
			else ans[i - 1] = '0';
		}
		ans[l] = '\0';
		puts(ans);
	}
}
