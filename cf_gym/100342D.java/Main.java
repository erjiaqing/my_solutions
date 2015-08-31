import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;
import java.lang.*;
public class Main{
    final static int maxn = 100 + 5;
    public static void main(String[] args) {
        try {
            InputStream fin = new FileInputStream(new File("dinner.in"));
            Scanner cin = new Scanner(new BufferedInputStream(fin));
            BigInteger f[][] = new BigInteger[maxn][maxn];
            BigInteger frac[] = new BigInteger[maxn];
            frac[0] = new BigInteger("1");
            f[1][1] = new BigInteger("1");
            f[0][0] = new BigInteger("0");
            for (int i = 1; i < maxn; i++)
            {
                frac[i] = frac[i - 1].multiply(new BigInteger("" + i));
                f[1][i] = new BigInteger("1");
                f[i][1] = new BigInteger("0");
                f[0][i] = new BigInteger("0");
                f[i][0] = new BigInteger("0");
            }
            f[1][1] = new BigInteger("1");
            for (int i = 1; i < maxn; i++)
                for (int j = 2; j < maxn; j++)
                    f[i][j] = f[i - 1][j - 1].multiply(new BigInteger("" + i)).add(f[i][j - 1].multiply(new BigInteger("" + i)));
            int k = cin.nextInt();
            int n = cin.nextInt();
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream("dinner.out")));
            pw.println(f[k][n].toString());
            fin.close();
            pw.close();
        }catch(Exception e) {
            e.printStackTrace();
        }
    }
}
