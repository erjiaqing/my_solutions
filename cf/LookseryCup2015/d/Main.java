import java.io.*;
import java.util.*;

public class Main {
	static final int maxN = 105;
	static int m , n;
	static int bit[][] = new int[maxN][maxN];
	static int needValue[][] = new int[maxN][maxN];

	public static int lowbit(int x) {
		return x & ( -x );
	}

	public static void addValue(int x , int y , int v) {
		for (int i = 1 ; i < maxN ; i += lowbit(i))
			for (int j = 1 ; j < maxN ; j += lowbit(j))
				bit[i][j] += v;
		for (int i = x + 1 ; i < maxN ; i += lowbit(i))
			for (int j = 1 ; j < maxN ; j += lowbit(j))
				bit[i][j] -= v;
		for (int i = 1 ; i < maxN ; i += lowbit(i))
			for (int j = y + 1 ; j < maxN ; j += lowbit(j))
				bit[i][j] -= v;
		for (int i = x + 1 ; i < maxN ; i += lowbit(i))
			for (int j = y + 1 ; j < maxN ; j += lowbit(j))
				bit[i][j] += v;
	}

	public static int getValue(int x , int y) {
		int ret = 0;
		for (int i = x ; i > 0 ; i -= lowbit(i))
			for (int j = y ; j > 0 ; j -= lowbit(j))
				ret += bit[i][j];
		return ret;
	}

	public void init() {
		for (int i = 0 ; i < maxN ; i++)
			for (int j = 0 ; j < maxN ; j++)
				bit[i][j] = 0;
	}

	public static void main(String[] argv) {
		int ans = 0;
		Scanner scan = new Scanner(System.in);
		n = scan.nextInt();
		m = scan.nextInt();
		for (int i = 1 ; i <= n ; i++) {
			String str = scan.next();
			for (int j = 1 ; j <= m ; j++)
				if (str.charAt(j - 1) == 'B')
					needValue[i][j] = -1;
				else
					needValue[i][j] = 1;
		}
		for (int i = n ; i > 0 ; i--) {
			for (int j = m ; j > 0 ; j--) {
				int val = getValue(i , j);
				if (val != needValue[i][j]) {
					int tmpVal = needValue[i][j] - val;
					ans++;
					addValue(i , j , tmpVal);
				}
			}
		}
		System.out.println(ans);
	}
}
