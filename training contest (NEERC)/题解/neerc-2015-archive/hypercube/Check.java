import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem H: Hypercube.
 *
 * @author Roman Elizarov
 */
public class Check implements Checker {
    private String nextAns(InStream ouf, Outcome.Type type) {
        String s = ouf.nextToken();
        if (!s.equals("Yes") && !s.equals("No"))
            throw new Outcome(type, "Invalid token '" + s + "'");
        if (!ouf.seekEoF())
            throw new Outcome(type, "Extra data in output file");
        return s;
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        String ja = nextAns(ans, FAIL);
        String pa = nextAns(ouf, PE);
        if (!pa.equals(ja))
            return new Outcome(WA, String.format(Locale.US, "Expected %s, found %s", ja, pa));
        return new Outcome(OK, String.format(Locale.US, "%s", pa));
    }
}
