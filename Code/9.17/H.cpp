#include <bits/stdc++.h>
using namespace std;

const int MAXN = 666;
const int MAXL = MAXN * MAXN * 4 * 2;
const double pi = acos(-1.0);
int n, m, id[MAXN][MAXN * 2], R[MAXL];
double D, p[MAXN][MAXN * 2], mat[MAXN][MAXN * 2];

struct Complex {
    double a, b;
    Complex() {};
    Complex(double _a, double _b): a(_a), b(_b) {};

inline Complex operator + (const Complex &q) {
    return Complex(a + q.a, b + q.b);
}

inline Complex operator - (const Complex &q) {
    return Complex(a - q.a, b - q.b);
}

inline Complex operator * (const Complex &q) {
    return Complex(a * q.a - b * q.b, a * q.b + b * q.a);
}

} a[MAXL], b[MAXL], tmp[MAXL];

inline void FFT(Complex *a, int n, int f) {
    for (register int i = 0; i < n; ++i)
        if (R[i] < i) swap(a[i], a[R[i]]);
    int ff = f == 1 ? 1 : 0;
    for (register int i = 1, h = 0; i < n; i <<= 1, h++) {
        Complex wn = Complex(cos(pi / i), f * sin(pi / i));
        Complex w = Complex(1, 0);
        for (int k = 0; k < i; ++k, w = w * wn) tmp[k] = w; 
        for (register int p = i << 1, j = 0; j < n; j += p) {
            for (int k = 0; k < i; ++k) {
                Complex x = a[j + k], y = a[j + k + i] * tmp[k];
                a[j + k] = x + y; a[j + k + i] = x - y;
            }
        }
    }
}

int main() {
    double tD;
    while (scanf("%d%d%lf", &n, &m, &tD) != EOF) {
        D = (long double)tD;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                double t;
                scanf("%lf", &t);
                mat[i][j] = (double)t;
            }
        int nn = max(n, int(floor(D)) * 2 + 1);
        int mm = max(m * 2, int(floor(D)) * 2 + 1);
        for (int i = 1; i <= nn; ++i)
            for (int j = 1; j <= mm; ++j)
                if (i > n || j > m) mat[i][j] = 0.0;
        n = nn; m = mm;
        
        int l = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) id[i][j] = l++;
        }
        int x = int(floor(D)) + 1, y = int(floor(D)) + 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                double dist = (i - x) * (i - x) + (j - y) * (j - y);
                if (dist < D * D - 1e-6) p[i][j] = 1.0 / (sqrt(dist) + 1);
                else p[i][j] = 0.0;
            }
        
        int L, D;
        for (L = 1, D = 0; L < l * 2 - 1; L <<= 1, D++);
        for (int i = 0; i < L; ++i) {
            a[i] = b[i] = Complex(0, 0);
            if (i) R[i] = (R[i >> 1] >> 1) | ((i & 1) << D - 1);
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                a[id[i][j]].a = mat[i][j];
                b[l - 1 - id[i][j]].a = p[i][j];
            }
            
        FFT(a, L, 1); FFT(b, L, 1);
        for (int i = 0; i < L; ++i) a[i] = a[i] * b[i];
        FFT(a, L, -1);
        for (int i = 0; i < L; ++i) a[i].a /= 1.0 * L;
        
        long double ans = 0.0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                long double nowans;
                nowans = a[l - 1 + (id[i][j] - id[x][y])].a;
                ans = max(nowans, ans);
            }
        printf("%.3f\n", (double)(ans));
    }
}

