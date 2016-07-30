#include <bits/stdc++.h>
#define prev PREV
using namespace std;

const int MODN = 1e9 + 7 + 1e-9;
const int N = 5555;
int n, a[N];
int longest[N], sol[N], prev[N];
vector<pair<int, pair<int, int> > > modify;

int main() {
	//int T; scanf("%d", &T);
	//printf("%d\n", MODN);
	for (; ~scanf("%d", &n); ) {
		memset(a, 0, sizeof a);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		a[0] = 222222; a[++n] = 222222;
		memset(prev, 0, sizeof prev);
		for (int i = 0; i <= n; i++) {
			prev[i] = -1;
			for (int j = 0; j < i; j++)
				if (a[j] == a[i]) prev[i] = j;
		}
		
		memset(longest, 0, sizeof longest);
		memset(sol, 0, sizeof sol);
		for (int i = n; i >= 0; i--) {
			longest[i] = 1; sol[i] = 1;
			int tlongest = 2, tsol = 1;
//			printf("left %d:\n", i);
			for (int j = i + 1; j <= n; j++) {
				//printf("%d %d %d %d\n", i, j, longest[j], sol[j]);
				if (a[j] == a[i]) {
					int ttlongest = longest[j];
					int ttsol = sol[j];

					modify.push_back(make_pair(j, make_pair(tlongest, tsol)));
					
					if (ttlongest + 2 == tlongest) {
						if (prev[j] > i && longest[prev[j]] == ttlongest) tsol = ((tsol + ttsol) % MODN - sol[prev[j]] + MODN) % MODN;
						else tsol = (tsol + ttsol) % MODN;
						//tlongest = ttlongest + 2;
					}
					else if (ttlongest + 2 > tlongest) {
						tlongest = ttlongest + 2;
						tsol = ttsol;
					}
				}
				else if (a[j] < a[i]) {
					if (longest[j] + 2 == tlongest) {
						//printf("%d\n", j);
						if (prev[j] > i && longest[prev[j]] == longest[j]) tsol = ((tsol + sol[j]) % MODN - sol[prev[j]] + MODN) % MODN;
						else tsol = (tsol + sol[j]) % MODN;
						//tlongest = longest[j] + 2;
					}
					else if (longest[j] + 2 > tlongest) {
						tlongest = longest[j] + 2;
						tsol = sol[j];
					}
				}
//				printf(" %d,%d:%d,%d,%d ", tlongest, tsol, j, longest[j], sol[j]);
			}
//			puts("");
			for (int i = 0; i < modify.size(); i++) {
				int j = modify[i].first;
				longest[j] = modify[i].second.first;
				sol[j] = modify[i].second.second;
			}
			modify.clear();
			//printf("%d %d\n", i, longest[i]);
		}
		
		printf("%d %d\n", longest[n] - 2, (sol[n] + MODN) % MODN);
	}
	return 0;
}
