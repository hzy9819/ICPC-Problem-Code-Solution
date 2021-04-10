import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem D: Easy Problemset.
 *
 * @author Andrey Lopatin
 */
public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int ja = ans.nextInt();
        int pa = ouf.nextInt();
        if (ja != pa) {
            return new Outcome(WA, String.format(Locale.US, "Expected %d, found %d", ja, pa));
        }
        return new Outcome(OK, String.format(Locale.US, "OK %d", pa));
    }
}
