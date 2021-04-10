import java.io.OutputStream;
import java.io.IOException; 
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Random ;

public class D {
	public static void main(String [] args) {
		Scanner sc = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int ok,ok2;
        int va,vb;
        va = 0;
        vb = 0;
        out.println("? "+va+" "+vb);
        out.flush();
        ok = sc.nextInt();
        for(int i=29;i>=0;i--){
            if(ok==0){
                va += (1<<i);
                out.println("? "+va+" "+vb);
                out.flush();
                ok2 = sc.nextInt();
                if(ok2==1){
                    va -= (1<<i);
                }else{
                    vb += (1<<i);
                }
            }else{
                va += (1<<i);
                vb += (1<<i);
                out.println("? "+va+" "+vb);
                out.flush();
                ok2 = sc.nextInt();
                if(ok==ok2){
                    vb -= (1<<i);
                    out.println("? "+va+" "+vb);
                    out.flush();
                    ok2 = sc.nextInt();
                    if(ok2==1){
                        va -= (1<<i);
                    }else{
                        vb += (1<<i);
                    }
                }else{
                    if(ok==1){
                        vb -= (1<<i);
                        out.println("? "+va+" "+vb);
                        out.flush();
                        ok = sc.nextInt();
                    }
                    else {
                        va -= (1<<i);
                        out.println("? "+va+" "+vb);
                        out.flush();
                        ok = sc.nextInt();
                    }
                }
            }
        }
        out.println("! "+va+" "+vb);
        out.flush();
	}

	static class Checker {
		int x, y;
		Checker() {
			int min = 0, max = (1 << 30) - 1;
			Random rd = new Random();

			x = rd.nextInt(max) % (max - min + 1) + min;
			y = rd.nextInt(max) % (max - min + 1) + min;
		}
		public int check(int a, int b) {
			int _x = x ^ a, _y = y ^ b;
			if(_x > _y) return 1;
			else if(_x < _y) return -1;
			return 0;
		}
		public void check_ans(int _x, int _y) {
			System.out.println("Answer is " + x + " " + y);
			System.out.println("Your Answer is " + _x + " " + _y);
			if(x != _x || y != _y) 
				System.out.println("WA");
			else
				System.out.println("AC");
		}
		
	}

	static class Solver {
		Checker ck;
		Solver() {
			ck = new Checker();
		}
		public int ask(int c, int d, Scanner in, PrintWriter out) {
			System.out.println("? " + c + " " + d);
			System.out.flush();
			//return in.nextInt();
			return ck.check(c, d);
		}

		public void solve(Scanner in, PrintWriter out) {
			int [] bin = new int[30];
			int [] a = new int[30];
			int [] b = new int[30];
			int c = 0; int d = 0;
			int fg = 0;

			bin[0] = 1;
			for(int i = 1; i < 30; ++i)
				bin[i] = bin[i - 1] << 1;

			// for(int i = 0; i < 30; ++i)
			//	System.out.println(bin[i]);

			fg = ask(c, d, in, out);
			for(int i = 29; i >= 0; --i) {
				if(fg == 1) { // a > b
					int cc = c, dd = d | bin[i];
					int _fg = ask(cc, dd, in, out);

					if(_fg == 1) {
						cc = c | bin[i]; dd = d ;
						int __fg = ask(cc, dd, in, out);
						if(__fg == 1) {
							a[i] = 0; b[i] = 0;
						}
						else {
							a[i] = 1; b[i] = 1;
						}
					}
					else if(_fg == 0) {
						a[i] = 0; b[i] = 1;
					}
					else {
						cc = c | bin[i]; dd = d | bin[i];
						int __fg = ask(cc, dd, in, out);
						if(__fg == 0) {
							a[i] = 0; b[i] = 0;
						}
						else {
							a[i] = 1; b[i] = 0;
						}
					}
				}
				else if(fg == -1) {
					int cc = c | bin[i], dd = d | bin[i];
					int _fg = ask(cc, dd, in, out);

					if(_fg == 1) {
						cc = c; dd = d | bin[i];
						int __fg = ask(cc, dd, in, out);
						if(__fg == 1) {
							a[i] = 0; b[i] = 1;							
						}
						else {
							a[i] = 0; b[i] = 0;
						}
					}
					else if(_fg == 0) {
						a[i] = 1; b[i] = 0;
					}
					else {
						cc = c ; dd = d | bin[i];
						int __fg = ask(cc, dd, in, out);
						if(__fg == 1) {
							a[i] = b[i] = 1;
						}
						else {
							a[i] = b[i] = 0;
						}
					}
				}
				else {
					int cc = c | bin[i], dd = d;
					int _fg = ask(cc, dd, in, out);
					if(_fg == 1) {
						a[i] = b[i] = 0;
					}
					else {
						a[i] = b[i] = 1;
					}
				}
				// System.out.println(a[i] + " " + b[i]);
				c |= a[i] * bin[i];
				d |= b[i] * bin[i];
			}
			int aa = 0, bb = 0;
			for(int i = 29; i >= 0; --i) {
				aa += a[i] * bin[i];
				bb += b[i] * bin[i];
			}
			out.println("! " + aa + " " + bb);
			ck.check_ans(aa, bb);
		}
	}
}