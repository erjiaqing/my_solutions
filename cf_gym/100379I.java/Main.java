import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;
import java.lang.*;
public class Main {
    static BigDecimal sqrt5p1 = new BigDecimal("3.23606797749978969640917366873127623544061835961152572427089");
	static BigDecimal r2 = new BigDecimal("2.0");
	static BigDecimal phi = sqrt5p1.divide(r2);
	static Scanner cin = new Scanner(new BufferedInputStream(System.in));
	public static long get_a(long tk) {
		return phi.multiply(new BigDecimal(tk)).longValue();
	}
	public static long get_b(long tk) {
		return phi.multiply(new BigDecimal(tk)).longValue() + tk;
	}
	public static void work() {
		boolean flg = false;
		long a , b , swp;
		a = cin.nextLong();
		b = cin.nextLong();
		if (b < a) {
			swp = b;
			b = a;
			a = swp;
			flg = true;
		}
		if (a <= 3) {
			if (a == 3) {
				if (b == 3) {
					System.out.printf("2\n");
				} else {
					if (flg) {
						System.out.printf("1 %d 0\n" , b - 3);
					} else {
						System.out.printf("1 0 %d\n" , b - 3);
					}
				}
			}
			if (a == 2) {
				if (flg) {
					System.out.printf("1 %d 0\n" , b - 1);
				} else {
					System.out.printf("1 0 %d\n" , b - 1);
				}
			}
			return;
		}
		if (a == b) {
			System.out.printf("1 %d %d\n" , a - 3 , a - 3);
			return;
		}
		if (b == a + 1) {
			System.out.printf("1 %d %d\n" , a - 1 , a - 1);
			return;
		}
		a--;
		b--;
		long k0 = 0;
		for (long i = 1l << 40 ; i > 0 ; i >>= 1) {
			long rb = get_b(k0 + i);
			if (rb <= a) {
				k0 += i;
			}
		}
		if (get_b(k0) == a) {
			if (get_a(k0) == b) {
				System.out.printf("2\n");
				return;
			}
			long ansa = 0;
			long ansb = b - get_a(k0);
			if (flg) {
				swp = ansa;
				ansa = ansb;
				ansb = swp;
			}
			System.out.printf("1 %d %d\n" , ansa , ansb);
			return;
		}
		//--
		k0 = 0;
		for (long i = 1l << 40 ; i > 0 ; i >>= 1) {
			long ra = get_a(k0 + i);
			if (ra <= a) {
				k0 += i;
			}
		}
		if (get_a(k0) == a) {
			if (get_b(k0) == b) {
				System.out.printf("2\n");
				return;
			}
			if (get_b(k0) < b) {
				long ansa = 0;
				long ansb = b - get_b(k0);
				if (flg) {
					swp = ansa;
					ansa = ansb;
					ansb = swp;
				}
				System.out.printf("1 %d %d\n" , ansa , ansb);
				return;
			}
		}
		k0 = a;
		for (long i = 1l << 40 ; i > 0 ; i>>= 1) {
			if (k0 - i <= 0)
				continue;
			long ra = get_a(k0 - i);
			long rb = get_b(k0 - i);
			long delta = a - ra;
			//System.err.printf("> k0 = %d k0 - i = %d ra = %d rb = %d (a = %d , b = %d) <\n" , k0 , k0 - i , ra , rb , a , b);
			//if (ra > a)
			//	continue;
			if (b - delta <= rb)
				k0 -= i;
		}
		/*
		if (get_a(k0) == a && get_b(k0) == b) {
			System.out.printf("2\n");
			return;
		}*/
		long ansa = a - get_a(k0);
		System.out.printf("1 %d %d\n" , ansa , ansa);
	}
	public static void main(String[] args) {
		//for (int i = 0 ; i < 10 ; i++)
		//	System.out.printf("(%d %d)\n" , get_a(i) , get_b(i));
		phi.setScale(60 , BigDecimal.ROUND_FLOOR);
		int t;
		t = cin.nextInt();
		for (int i = 0 ; i < t ; i++) {
			work();
		}
	}
}
