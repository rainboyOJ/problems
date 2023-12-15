import java.io.* ;
public class fib {
    public static int[] mult(int[] a, int[] b) {
	return new int[]
	    { (a[0]*b[0]+a[1]*b[1]) % 10000, 
	      (a[0]*b[1]+a[1]*b[2]) % 10000,
	      (a[1]*b[1]+a[2]*b[2]) % 10000 } ;
    }
    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in)) ;
	while (true) {
	    String s = br.readLine() ;
	    int n = Integer.parseInt(s) ;
	    if (n < 0)
		return ;
	    int[] up = new int[] { 1, 1, 0 } ;
	    int[] r = new int[] { 1, 0, 1 } ;
	    while (n > 0) {
		if (0 != (n & 1))
		    r = mult(r, up) ;
		up = mult(up, up) ;
		n >>= 1 ;
	    }
	    System.out.println(r[1]) ;
	}
    }
}
