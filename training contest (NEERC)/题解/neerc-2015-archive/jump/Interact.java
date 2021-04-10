import java.io.*;
import java.util.*;

/**
 * Interact for NEERC'2015 Problem J: Jump.
 *
 * @author Maxim Buzdalov
 */
public class Interact {
    private static final int OK_EXIT_CODE = 0;
    private static final int EARLY_EXIT_CODE = 10;

    private static String checkQuery(int n, String query) {
        if (query == null) {
            return "Query is null";
        }
        if (query.length() != n) {
            return "Query's length != " + n;
        }
        for (int i = 0; i < n; ++i) {
            char c = query.charAt(i);
            if (c != '0' && c != '1') {
                return "Query has wrong character '" + c + "' at position " + (i + 1);
            }
        }
        return null;
    }

    private static int fitness(String value, String query) {
        int rv = 0;
        for (int i = 0; i < value.length(); ++i) {
            if (value.charAt(i) == query.charAt(i)) {
                ++rv;
            }
        }
        return rv == value.length() || rv == value.length() / 2 ? rv : 0;
    }

    private static int run(String inFilename, String outFilename) throws IOException {
        try (Scanner in = new Scanner(new File(inFilename));
             PrintWriter out = new PrintWriter(outFilename)) {
            int n = in.nextInt();
            String v = in.next();
            int qLimit = in.nextInt();
            int maxFitness = in.nextInt();
            try (Scanner pipeIn = new Scanner(System.in);
                 PrintWriter pipeOut = new PrintWriter(System.out)) {
                pipeOut.println(n);
                pipeOut.flush();
                for (int q = 0; q < qLimit; ++q) {
                    String query = pipeIn.nextLine();
                    String errorMessage = checkQuery(n, query);
                    if (errorMessage != null) {
                        out.println("PE");
                        out.println(errorMessage);
                        return EARLY_EXIT_CODE;
                    }
                    out.println("Query " + query);
                    int fitness = fitness(v, query);
                    out.println("Answer " + fitness);
                    pipeOut.println(fitness);
                    pipeOut.flush();
                    if (fitness == maxFitness) {
                        out.println("OK");
                        out.println((q + 1) + " out of " + qLimit);
                        return OK_EXIT_CODE;
                    }
                }
                out.println("WA");
                out.println("Too many queries");
                return EARLY_EXIT_CODE;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        System.exit(run(
            args.length >= 1 ? args[0] : "jump.in",
            args.length >= 2 ? args[1] : "jump.out"
        ));
    }
}
