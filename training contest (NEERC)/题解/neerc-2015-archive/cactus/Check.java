import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.*;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2015 Problem C: Cactus Jubilee.
 *
 * @author Roman Elizarov
 */
public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        long ja = ans.nextLong();
        long pa = ouf.nextLong();
        if (pa != ja)
            return new Outcome(WA, String.format(Locale.US, "Expected %d, found %d", ja, pa));
        return new Outcome(OK, String.format(Locale.US, "%d", pa));
    }
}
