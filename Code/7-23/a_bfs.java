package a_7_23;
import java.math.*;
import java.util.Scanner;
import java.util.*;
public class Main {
	static int NNN = 1000000;
	static BigInteger N;
	static BigInteger M;
	static BigInteger One = new BigInteger("1");
	static BigInteger Two = new BigInteger("2");
	static BigInteger Zero = new BigInteger("0");
	static BigInteger[] queue = new BigInteger[NNN];
	static BigInteger[] num_step = new BigInteger[NNN];
	static Collection c = new HashSet();
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		while(true){
			N = cin.nextBigInteger();
			M = cin.nextBigInteger();
			BigInteger ans = N.add(M);
			if(N.compareTo(Zero) == 0 && M.compareTo(Zero) == 0) break;
			c.clear();
			c.add(N);
			int head = 1;
			int tail = 1;
			queue[1] = N;
			num_step[1] = Zero;
			BigInteger tmp, p;
			while (head <= tail){
				N = queue[head];
				BigInteger now = num_step[head++];
				tmp = ((N.subtract(M)).abs()).add(now);
				now = now.add(One);
				//System.out.println(N + " " + M+" " + now + " " + tmp);
				if(tmp.compareTo(ans) < 0) ans = tmp;
				if(N.compareTo(Zero) != 0){
					if((N.mod(Two)).compareTo(Zero) == 0){
						p = N.divide(Two);
						if(c.contains(p) == false) {
							c.add(p);
							tail++;
							queue[tail] = p;
							num_step[tail] = now;
						}
					}else{
						p = N.add(One);
						if(c.contains(p) == false) {
							c.add(p);
							tail++;
							queue[tail] = p;
							num_step[tail] = now;
						}
						
						p = N.subtract(One);
						if(c.contains(p) == false) {
							c.add(p);
							tail++;
							queue[tail] = p;
							num_step[tail] = now;
						}
					}
				}
				
			}
			System.out.println(ans);
		}
	}

}
