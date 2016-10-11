import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;
import java.lang.*;
public class A {
	static final int maxn = 100000 + 5;
	static int[] a = new int[maxn];
	static int[] b = new int[maxn];
	static int[] vis = new int[maxn];

	BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
	PrintWriter writer = new PrintWriter(System.out);
	StringTokenizer tokenizer = null;

	String next() throws Exception {
		for (; tokenizer == null || !tokenizer.hasMoreTokens();) {
			tokenizer = new StringTokenizer(reader.readLine());
		}
		return tokenizer.nextToken();
	}

	int nextInt() throws Exception {
		return Integer.parseInt(next());
	}

	private void sol() {
		try {
			int n;
			n = nextInt();
			for (int i = 1; i <= n; i++)
				a[i] = nextInt();
			for (int i = 1; i <= n; i++)
				b[i] = nextInt();
			for (int i = 1; i <= n; i++)
				vis[i] = 0;
			int last = 0, occ = 0;
			for (int i = 1; i <= n; i++) {
				vis[a[i]]++;
				if (vis[a[i]] == 0) occ--;
				else occ++;
				vis[b[i]]--;
				if (vis[b[i]] == 0) occ--;
				else occ++;
				if (occ == 0) {
					writer.printf("%d-%d ", last + 1, i);
					last = i;
				}
			}
			writer.print('\n');
			//System.out.println("");
		} catch (Exception e) {
		}
	}

	public void main2() {
		try {
			//Scanner cin = new Scanner(System.in);
			int t = nextInt();
			for (int i = 0; i < t; i++)
				sol();
		} catch (Exception e) {
		}
	}

	void run() throws Exception{
		try {
			main2();
		} catch (Exception e) {
		} finally {
			reader.close();
			writer.close();
		}
	}

	public static void main(String args[]) throws Exception{
		(new A()).run();
	}
}
