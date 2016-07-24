package a_7_23_DP;
import java.math.*;
import java.util.Scanner;
public class Main {
	static int NUM = 100000;
	static BigInteger Zero = BigInteger.ZERO;
	static BigInteger One = BigInteger.ONE;
	static BigInteger Two = BigInteger.valueOf(2);
	static BigInteger []a = new BigInteger [NUM];
	static BigInteger [][] f = new BigInteger[NUM][2];
	static public BigInteger min(BigInteger a, BigInteger b){
		if(a.compareTo(b) < 0) return a;
		return b;
	}
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		while(true){
			BigInteger N = cin.nextBigInteger();
			BigInteger M = cin.nextBigInteger();
			if(N.compareTo(Zero) == 0 && M.compareTo(Zero) == 0) break;
			if(M.compareTo(N) > 0){
				System.out.println(M.subtract(N));
				continue;
			}
			BigInteger N_bak = N;
			BigInteger M_bak = M;
			
			int tot = 0;
			while(N.equals(Zero) == false){
				a[++tot] = N.mod(Two);
				N = N.divide(Two);
			}
			//for(int i = 1; i <= tot; i++)
			//	System.out.println(i + " " + a[i]);
			for(int i = 1; i * 2 <= tot; i++){
				BigInteger tmp = a[i];
				a[i] = a[tot + 1 - i];
				a[tot + 1 -i] = tmp;
			}
			BigInteger now = Zero;
			
			for(int i = 1; i <= tot; i++){
				now = (now.multiply(Two)).add(a[i]);
				f[i][0] = (now.subtract(M)).abs();
				f[i][1] = ((now.add(One)).subtract(M)).abs();
			}
			for(int i = 1; i <tot; i++){
				if(a[i + 1].equals(Zero) == true){
					f[i + 1][0] = min(f[i + 1][0], f[i][0].add(One));
					f[i + 1][1] = min(f[i + 1][1], f[i][0].add(Two));
					f[i + 1][0] = min(f[i + 1][0], f[i][1].add(Two));
					f[i + 1][1] = min(f[i + 1][1], f[i][1].add(Two));
				}else{
					f[i + 1][0] = min(f[i + 1][0], f[i][0].add(Two));
					f[i + 1][1] = min(f[i + 1][1], f[i][0].add(Two));
					f[i + 1][1] = min(f[i + 1][1], f[i][1].add(One));
					f[i + 1][0] = min(f[i + 1][0], f[i][1].add(Two));
				}
			}
			//System.out.println(tot);
			System.out.println(min(f[tot][0], f[tot][1].add(One)));
		}
	}

}
