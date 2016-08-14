#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int a[1100000], n;
int main(){
	while(scanf("%d",&n) == 1){
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
		}
		int ans = 0;
		LL sum = 0;
		for(int i = n; i >= 1; i--){
			sum += a[i];
			if(i == 1) assert(sum >= 0);
			if(sum >= 0){
				sum = 0;
				ans++;
			}
		}
		printf("%d\n",ans);
	}
}
