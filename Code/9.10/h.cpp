#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned long long LL;
__int128 work(__int128 n){
	if(n < 4) return n - 1;
	return n * n / 4;
}
int main(){
	LL n,m;
	while (cin>>n>>m){
		if(m >= work(n)) puts("T");
		else puts("F");
	}
}
