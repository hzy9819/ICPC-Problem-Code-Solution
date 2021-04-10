import java.io.*;
import java.util.*;

public class Tests {
    private static final int MAX_N = 1000;
	private static int testNumber = 0;

	private static final String path = "tests/";

	static Random rnd = new Random(23917);

    static void writeTest(int k, int a[][]) throws IOException {
        try (PrintWriter out = new PrintWriter(String.format("%s%02d", path, ++testNumber))) {
            out.println(a.length + " " + k);
            for (int i = 0; i < a.length; i++) {
        	out.print(a[i].length);
        	for (int j = 0; j < a[i].length; j++) {
        	    out.print(" " + a[i][j]);
        	}
        	out.println();
    	    }
        }
    }

    static void rmrf(File file) {
        if (file.isDirectory()) {
            File[] children = file.listFiles();
            if (children != null) {
                for (File f : children) {
                    rmrf(f);
                }
            }
        }
        file.delete();
    }
    
    
    static int [][] randomTest(int n, int b) {
      int [][] res = new int [n][];
      for (int i = 0; i < n; i++) {
        res[i] = new int[Math.max(1, rnd.nextInt(b))];
        for (int j = 0; j < res[i].length; j++) {
          res[i][j] = rnd.nextInt(50);
        }
      }
      return res;
    }
    static int [][] randomTest2(int n, int b, int c) {
      int [][] res = new int [n][];
      for (int i = 0; i < n; i++) {
        res[i] = new int[Math.max(1, Math.min(10, rnd.nextInt(b)))];
        for (int j = 0; j < res[i].length; j++) {
          res[i][j] = rnd.nextInt(Math.min(50, c * j + c));
        }
      }
      return res;
    }
    static int [][] randomTest3(int n, int b, int c) {
      int [][] res = new int [n][];
      for (int i = 0; i < n; i++) {
        res[i] = new int[Math.max(1, Math.min(10, rnd.nextInt(b)))];
        for (int j = 0; j < res[i].length; j++) {
          res[i][j] = rnd.nextInt(rnd.nextInt(Math.min(50, c * j + c)) + 1);
        }
      }
      return res;
    }

	public static void main(String[] args) throws IOException {
	    File root = new File(path);
	    rmrf(root);
	    root.mkdir();

	    writeTest(8, new int[][] {{0, 3, 12, 1, 10}, {1, 1, 23, 20}, {1, 5, 17, 49}});
	    writeTest(10, new int[][] {{1, 3}, {1}, {2, 5}});
	    writeTest(10, new int[][] {{49, 17}, {20, 10, 5}});
	    writeTest(14, new int[][] {{49}, {49}});
	    writeTest(10, new int[][] {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}});
	    writeTest(14, new int[][] {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}});
	    writeTest(14, new int[][] {{0}, {0, 1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}});
	    writeTest(14, new int[][] {{0, 1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}});
	    writeTest(13, randomTest(5, 6));
	    writeTest(12, randomTest2(3, 7, 5));
	    writeTest(11, randomTest2(4, 10, 5));
	    writeTest(14, randomTest2(5, 10, 5));
	    writeTest(14, randomTest2(6, 10, 5));
	    writeTest(9, randomTest2(7, 10, 5));
	    writeTest(14, randomTest3(6, 10, 5));
	    writeTest(14, randomTest3(10, 10, 5));
	    writeTest(14, randomTest2(10, 10, 5));
	    writeTest(14, randomTest3(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	    writeTest(14, randomTest3(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	    writeTest(14, randomTest2(10, 1000, 5));
	}
}
