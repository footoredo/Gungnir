#include <bits/stdc++.h>
#define convert CONVERT
using namespace std;

const char S[17] = "0123456789abcdef";

void convert(int x, int len) {
	char buf[5];
	for (int i = 0; i < len; ++ i, x /= 16)
		buf[len - i - 1] = S[x % 16];
	buf[len] = 0;
	printf("%s", buf);
}

char buf[5555];

int main() {
	for (; gets(buf); ) {
		int n = strlen(buf);
		for (int i = 0; i < n; i += 16) {
			convert(i, 4);
			putchar(':');
			int len = min(n - i, 16);
			for (int j = 0; j < 16; ++ j) {
				if (~j & 1) putchar(' ');
				if (j < len) convert(buf[i + j], 2);
				else {
					putchar(' '); putchar(' ');
				}
			}
			putchar(' ');
			for (int j = 0; j < len; ++ j)
				if (islower(buf[i + j])) putchar(buf[i + j] - 'a' + 'A');
				else if (isupper(buf[i + j])) putchar(buf[i + j] - 'A' + 'a');
				else putchar(buf[i + j]);
			puts("");
		}
	}
	return 0;
}
