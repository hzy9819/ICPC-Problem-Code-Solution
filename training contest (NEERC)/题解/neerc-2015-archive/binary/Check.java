import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem B: Binary vs Decimal.
 *
 * @author Mikhail Tikhomirov
 */
public class Check implements Checker {
    private String readOut(InStream ouf, Outcome.Type pe) {
        String s = ouf.nextToken();
        if (s.isEmpty())
            throw new Outcome(pe, "Empty output");
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (i == 0 && c == '0')
                throw new Outcome(pe, "Leading zeros in the output");
            if (c < '0' || c > '9')
                throw new Outcome(pe, String.format(Locale.US, "Non-digit symbol at position %d", i + 1));
        }
        if (!ouf.seekEoF())
            throw new Outcome(pe, "Extra data in output file");
        return s;
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        inf.nextInt();
        String ja = readOut(ans, FAIL);
        String pa = readOut(ouf, PE);
        if (!ja.equals(pa)) {
            return new Outcome(WA, String.format(Locale.US, "Expected %s, found %s", ja, pa));
        }
        return new Outcome(OK, "OK");
    }
}
