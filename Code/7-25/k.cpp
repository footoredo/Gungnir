#include <bits/stdc++.h>
using namespace std;

string ball_name[9] = {
	"White", "Red", "Yellow", "Green", "Brown", "Blue", "Pink", "Black", "None"
};

int get_ball_x(string s) {
	for (int i = 0; i < 9; i++) if (ball_name[i] == s) return i;
}

struct Ball {
	int x;
	__inline Ball(int _x = 0): x(_x) {}
	__inline bool read(char *&s) {
		for (; *s != 0 && *s == 32; ) s++;
		if (*s == 0) return 0;
		string na = "";
		for (; isalpha(*s); s++) na += *s;
		x = get_ball_x(na);
		return 1;
	}
	__inline bool operator == (const Ball& rhs) const {
		return x == rhs.x;
	}
	__inline bool operator != (const Ball& rhs) const {
		return x != rhs.x;
	}
} white(0), red(1), yellow(2), green(3), brown(4), blue(5), pink(6), black(7), none(8);

char buf[111111];
typedef pair<Ball, vector<Ball> > Hit;
Hit hit() {
	gets(buf); char *s = buf;
	Ball hit_ball, pot_ball; hit_ball.read(s);
	vector<Ball> pot_balls;
	for (; pot_ball.read(s); ) {
		pot_balls.push_back(pot_ball);
	}
	return make_pair(hit_ball, pot_balls);
}

#define HIT_NONE 1
#define HIT_NOT_ON 2
#define POT_NOT_ON 3
#define POT_WHITE 4

typedef vector<Ball> Respot;
typedef vector<Ball> On;

__inline bool in(Ball b, const vector<Ball>& v) {
	for (int i = 0; i < v.size(); i++)
		if (b == v[i]) return 1;
	return 0;
}

Ball on_ball;
int foul_value, foul;
Respot check(const On& on, const Hit& h) {
	Respot respot;
	foul = 0; foul_value = 4;
	if (h.first == none) {
		foul = HIT_NONE; return respot;
	}
	if (!in(h.first, on)) {
		foul = HIT_NOT_ON; 
		for (int i = 0; i < h.second.size(); i++) {
			if (h.second[i] != red) {
				foul_value = max(foul_value, h.second[i].x);
				respot.push_back(h.second[i]);
			}
		}
		return respot;	
	}
	on_ball = h.first;
	for (int i = 0; i < h.second.size(); i++) {
		if (h.second[i] != h.first) {
			foul = POT_NOT_ON;
			foul_value = max(foul_value, h.second[i].x);
		}
		if (h.second[i] != red) {
			respot.push_back(h.second[i]);
		}
	}
	return respot;
}

string player[2];

int main() {
	int T; scanf("%d", &T);
	for (int frame = 1; frame <= T; frame++) {
		printf("Frame %d\n", frame);
		cin >> player[0] >> player[1];
		cout << player[0] << "'s turn, in-hand" << endl;
		bool cur = 0;
		On on; on.push_back(red);
		int score[2] = {0, 0};
		for (; ;) {
			Hit h = hit();
			Respot r = check(on, h);
			if (!foul) {
				score[cur] += h.first.x * h.second.size();
				printf("%d : %d\n", score[0], score[1]);
				if (r.size()) {
					printf("Respot");
					for (int i = 0; i < r.size(); i++)
						cout << " " + ball_name[r[i].x];
					puts("");
				}
			}
			else {
				puts("Foul!");
				score[!cur] += foul_value;
				printf("%d : %d\n", score[0], score[1]);
				if (r.size()) {
					printf("Respot");
					for (int i = 0; i < r.size(); i++)
						cout << " " + ball_name[r[i].x];
					puts("");
				}
				cout << player[!cur] << "'s turn";
				if (foul == POT_WHITE) cout << ", in-hand";
				cout << endl;
				cur = !cur;
			}
		}
	}
	return 0;
}
