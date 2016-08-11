#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000000;
LL a[N], b[N], c[N], x[N], y[N];
string hh[N];
set<string>ss; 
int main(){
	int T;
	cin>>T;
	while(T--){
		int n, m;
		ss.clear();
		scanf("%d%d",&n ,&m);
		for(int i = 1; i <= n; i++){
			scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
		}
		for(int i = 1; i <= m; i++){
			hh[i] = "";
			scanf("%lld%lld", &x[i], &y[i]);
		}
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				if(a[i] * x[j] + b[i] * y[j] + c[i] < 0) hh[j] += '1';
					else hh[j] += '0';
			} 
		}
		int tmp = 0;
		for(int i = 1; i <= m; i++){
			if(ss.find(hh[i]) == ss.end()){
				tmp++;
				ss.insert(hh[i]);
			}
		}
		int sum = 1;
		for(int i = 1; i <= n; i++){
			sum++;
			for(int j = 1; j < i; j++)
				if(a[i] * b[j] != a[j] * b[i]) sum++;
		}
		if(sum == tmp) puts("PROTECTED");
			else puts("VULNERABLE");
	}
}
