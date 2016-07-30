#include <bits/stdc++.h>
using namespace std;

map<string, int> mp;
string st1, st2, st3;
int T;
char ch[1000];

int main() {
	/*freopen("K.in", "r", stdin);
	freopen("K.out", "w", stdout);
	mp.clear();
	while (gets(ch)) { 
		string st = " ";
		int l = strlen(ch), boo = 0;
		for (int i = 0; i < l; ++i) {
			if (boo) st = st + ch[i];
			else 
				if (ch[i] == ' ') boo = 1;
		}
		//cout << st << endl;
		if (mp.find(st) == mp.end()) mp[st] = 1;
		else mp[st]++;
	}
	for (map<string, int>::iterator it=mp.begin(); it != mp.end(); ++it) cout << "mp[\"" << it -> first << "\"] = " << it -> second << endl;*/
	mp.clear();
mp["Baltimore Bullets"] = 1;
mp["Boston Celtics"] = 17;
mp["Chicago Bulls"] = 6;
mp["Cleveland Cavaliers"] = 1;
mp["Dallas Mavericks"] = 1;
mp["Detroit Pistons"] = 3;
mp["Golden State Warriors"] = 2;
mp["Houston Rockets"] = 2;
mp["L.A. Lakers"] = 11;
mp["Miami Heat"] = 3;
mp["Milwaukee Bucks"] = 1;
mp["Minneapolis Lakers"] = 5;
mp["New York Knicks"] = 2;
mp["Philadelphia 76ers"] = 2;
mp["Philadelphia Warriors"] = 2;
mp["Portland Trail Blazers"] = 1;
mp["Rochester Royals"] = 1;
mp["San Antonio Spurs"] = 5;
mp["Seattle Sonics"] = 1;
mp["St. Louis Hawks"] = 1;
mp["Syracuse Nats"] = 1;
mp["Washington Bullets"] = 1;
	scanf("%d ", &T);
	//cout << 1 << endl;
	for (int Q = 1; Q <= T; ++Q) {
		//cout << 1 << endl;
		string st = "";
		gets(ch);
		//cout << ch << endl;
		int l = strlen(ch);
		for (int i = 0; i < l; ++i) st = st + ch[i];
		//cout << st << endl;
		if (mp.find(st) == mp.end()) printf("Case #%d: %d\n", Q, 0);
		else printf("Case #%d: %d\n", Q, mp[st]);
	}
}
