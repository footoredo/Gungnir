#include <bits/stdc++.h>
typedef long double LD;
using namespace std;

const LD eps = 1e-7;
int T, l, v1, v2;

int main() {
	while (cin >> l >> v1 >> v2) {
		if (l == 0) {
			printf("0\n");
			continue;
		}
		if (v1 <= v2) {
			printf("Infinity\n");
			continue;
		}
		
		/*LD x = 0, y = l, t = 0, dt = 1e-7;
		while (x + y > eps) {
			LD xx, yy;
			xx = x + dt * (v2 - v1 * x / sqrt(x * x + y * y));
			yy = y - dt * v1 * y / sqrt(x * x + y * y);
			x = xx, y = yy;
			t += dt;
		}
		printf("%.10f\n", double(t));*/
		printf("%.10f\n", double(l) * v1 / (v1 * v1 - v2 * v2));
	}	
}
