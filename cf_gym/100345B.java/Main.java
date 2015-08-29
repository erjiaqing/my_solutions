import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;
import java.lang.*;
public class Main{
    final static int maxn = 200 + 5;
    public static BigInteger bigPow(BigInteger a, int b) {
        BigInteger ret = new BigInteger("1");
        BigInteger x = a;
        while (b > 0) {
            if ((b & 1) == 1) {
                ret = ret.multiply(x);
            }
            x = x.multiply(x);
            b = b >> 1;
        }
        return ret;
    }
    public static void main(String[] args) {
        try{
            InputStream fin = new FileInputStream(new File("derangements.in"));
            Scanner cin = new Scanner(new BufferedInputStream(fin));
        BigInteger c[][] = new BigInteger[maxn][maxn];
        BigInteger frac[] = new BigInteger[maxn];
        BigInteger f[] = new BigInteger[maxn];
        c[0][0] = new BigInteger("1");
        frac[0] = new BigInteger("1");
        for (int i = 1; i < maxn; i++)
            c[0][i] = new BigInteger("0");
        for (int i = 1; i < maxn; i++) {
            frac[i] = frac[i - 1].multiply(new BigInteger("" + i));
            c[i][0] = new BigInteger("1");
            for (int j = 1; j < maxn; j++)
                c[i][j] = c[i - 1][j - 1].add(c[i - 1][j]);
        }
        f[1] = new BigInteger("1");
        for (int i = 2; i < maxn; i++) {
            f[i] = bigPow(new BigInteger("2"), i).multiply(frac[i]);
            for (int j = 1; j < i; j++) {
                f[i] = f[i].subtract(c[i][j].multiply(f[i - j]));
            }
            f[i] = f[i].subtract(new BigInteger("1"));
        }
        int n = cin.nextInt();
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream("derangements.out")));
        pw.println(f[n].toString());
        fin.close();
        pw.close();
        /*
        for (int i = 1; i < maxn; i++) {
            System.out.printf("\"%s\" ,\n", f[i].toString());
        }*/
        }catch(Exception e) {
        }
    }
}
