import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

/**
 * Checker for NEERC'2015 Problem J: Jump.
 *
 * @author Maxim Buzdalov
 */
public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        while (true) {
            String verdict = ouf.nextLine();
            if (verdict.startsWith("Query") || verdict.startsWith("Answer")) {
                continue;
            }
            if (verdict.isEmpty()) {
                return new Outcome(Outcome.Type.WA, "User program terminated incorrectly");
            }
            String comment = ouf.nextLine();
            Outcome.Type type = Outcome.Type.valueOf(verdict);
            return new Outcome(type, comment);
        }
    }
}
