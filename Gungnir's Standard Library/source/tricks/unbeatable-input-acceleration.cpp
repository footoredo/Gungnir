// getchar()读入优化 << 关同步cin << 此优化
// 用isdigit()会小幅变慢
namespace Reader {  
    const int L = (1 << 15) + 5;  
    char buffer[L], *S, *T;  
    __inline void get_char(char &ch) {  
        if (S == T) {  
            T = (S = buffer) + fread(buffer, 1, L, stdin);  
            if (S == T) {
				ch = EOF;
				return ;
			}
        }  
		ch = *S++;
    }  
    __inline void get_int(int &x) {  
		char ch; bool neg = 0;
		for (; get_char(ch), ch < '0' || ch > '9'; ) neg ^= ch == '-';
		x = ch - '0';
		for (; get_char(ch), ch >= '0' && ch <= '9'; ) 
			x = x * 10 + ch - '0';
		if (neg) x = -x;
    }  
}
