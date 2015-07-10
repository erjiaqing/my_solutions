import java.io.*;
import java.util.*;

public class Main{
	public static void main(String[] args) {
		int n , k;
		int odd = 0 , even = 0 , tmp;
		int flag;
		Scanner reader = new Scanner(System.in);
		n = reader.nextInt();
		k = reader.nextInt();
		for (int i = 0 ; i < n ; i++) {
			tmp = reader.nextInt();
			if (tmp % 2 == 0) even++;
			else odd++;
		}
		if (n == k) {
			if (odd % 2 == 0) {
				System.out.printf("Daenerys\n");
			} else {
				System.out.printf("Stannis\n");
			}
			return;
		}
		flag = (n - k) % 2;
		// even -> D
		// odd  -> S
		if (flag == 1) {
			// S make the last move
			int moves = (n - k) / 2;
			if (odd <= moves || (even <= moves && (k % 2 == 0))) {
				System.out.printf("Daenerys\n");
			} else {
				System.out.printf("Stannis\n");
			}
		} else {
			// D make the last move
			int moves = (n - k) / 2;
			if (even <= moves && (k % 2 == 1)) {
				System.out.printf("Stannis\n");
			} else {
				System.out.printf("Daenerys\n");
			}
		}
	}
}
