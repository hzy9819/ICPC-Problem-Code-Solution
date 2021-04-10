import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem A: Adjustment Office.
 *
 * @author Vitaliy Aksenov
 */
public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        inf.nextInt();
        int m = inf.nextInt();
  
        for (int i = 0; i < m; i++) {
            long ja = ans.nextLong();
            long pa = ouf.nextLong();
                    
            if (ja != pa) {
                return new Outcome(WA, String.format(Locale.US, "Expected %s, found %s in position %d", ja, pa, (i + 1)));
            }
        }
        return new Outcome(OK, String.format(Locale.US, "%d answers", m));
    }
}
