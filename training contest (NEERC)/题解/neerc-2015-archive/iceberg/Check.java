import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;

/**
 * Checker for NEERC'2015 Problem I: Iceberg Orders.
 *
 * @author Egor Kulikov
 */
public class Check implements Checker {
    private static String[] TRADE_FIELDS = {"buy ID", "sell ID", "price", "volume"};
    private static String[] ORDER_FIELDS = {"ID", "type", "price", "volume", "tip volume", "current volume"};

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int orderCount = 0;
        int tradeCount = 0;
        int line = 1;
        while (!ans.seekEoF() && !ouf.seekEoF()) {
            String nextAns = ans.nextLine().trim();
            String nextOuf = ouf.nextLine().trim();
            String[] ansTokens = nextAns.split("\\s+");
            String[] oufTokens = nextOuf.split("\\s+");
            if (ansTokens.length != oufTokens.length) {
                if (ansTokens.length != 6 && ansTokens.length != 4) {
                    return new Outcome(WA, String.format("Line %d: not an order or a trade", line));
                }
                if (ansTokens.length == 4) {
                    return new Outcome(WA, String.format("Line %d: order expected, trade found", line));
                } else {
                    return new Outcome(WA, String.format("Line %d: trade expected, order found", line));
                }
            }
            if (ansTokens.length == 4) {
                tradeCount++;
            } else {
                orderCount++;
            }
            for (int i = 0; i < ansTokens.length; i++) {
                if (!ansTokens[i].equals(oufTokens[i])) {
                    return new Outcome(WA, String.format("Line %d: %s differs, %s expected, %s found", line,
                        ansTokens.length == 4 ? TRADE_FIELDS[i] : ORDER_FIELDS[i], oufTokens[i], ansTokens[i]));
                }
            }
            line++;
        }
        if (!ouf.seekEoF()) {
            return new Outcome(WA, String.format("Not all orders are printed, only first %d ones", orderCount));
        }
        return new Outcome(OK, String.format("%d lines, %d trades, %d orders", line - 1, tradeCount, orderCount));
    }
}
