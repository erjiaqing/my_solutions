import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;
import java.lang.*;

public class Main {
	private static String flip(String s) {
		String ret = "";
		int len = s.length();
		for (int i = len - 1; i >= 0; i--)
			ret = ret + s.charAt(i);
		return ret;
	}
	private static int check1(BigInteger a, BigInteger b) {
		String b0 = b.toString();
		b0 = b0 + flip(b0);
		return a.compareTo(new BigInteger(b0));
	}
	private static int check2(BigInteger a, BigInteger b) {
		String b0 = b.toString();
		b0 = b0 + flip(b0).substring(1);
		return a.compareTo(new BigInteger(b0));
	}
	private static void solve(BigInteger s) {
		List<String> ans = new ArrayList<>();
		while (s.compareTo(BigInteger.ZERO) > 0) {
			String rs = s.toString();
			String cs = null;
			BigInteger sub = null;
			int len = rs.length();
			cs = rs.substring(0, (len + 1) / 2);
			if (len % 2 == 0) {
				if (check1(s, new BigInteger(cs)) >= 0) {
					sub = new BigInteger(cs + flip(cs));
					ans.add(sub.toString());
				} else {
					sub = new BigInteger(cs);
					sub = sub.subtract(BigInteger.ONE);
					if (sub.compareTo(BigInteger.ZERO) <= 0) {
						sub = BigInteger.ONE;
						ans.add(BigInteger.ONE.toString());
					} else {
						String rc = sub.toString();
						if (rc.length() < (len + 1) / 2)
							sub = new BigInteger(rc + "9" + flip(rc));
						else
							sub = new BigInteger(rc + flip(rc));
						ans.add(sub.toString());
					}
				}
			} else {
				if (check2(s, new BigInteger(cs)) >= 0) {
					sub = new BigInteger(cs + flip(cs).substring(1));
					ans.add(sub.toString());
				} else {
					BigInteger rc = new BigInteger(cs);
					rc = rc.subtract(BigInteger.ONE);
					cs = rc.toString();
					if (cs.length() < (len + 1) / 2)
						sub = new BigInteger(cs + flip(cs));
					else
						sub = new BigInteger(cs + flip(cs).substring(1));
					ans.add(sub.toString());
				}
			}
			s = s.subtract(sub);
		}
		System.out.printf("%d\n", ans.size());
		for (String r : ans) {
			System.out.println(r);
		}
	}
	public static void main(String[] args) {
		try {
			Scanner cin = new Scanner(System.in);
			int n = cin.nextInt();
			for (int i = 1; i <= n; i++)
			{
				BigInteger bigint = cin.nextBigInteger();
				System.out.printf("Case #%d:\n", i);
				solve(bigint);
			}
		} catch (Exception e) {
			//Sad
		}
	}
}
