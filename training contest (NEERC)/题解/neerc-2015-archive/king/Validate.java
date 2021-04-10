import ru.ifmo.validate.*;

public class Validate implements Validator {
	public static final int MAX = 100_000;
	public static final int EXTRA = 20;

	@Override
	public void validate(ValidatingScanner in) {
		int n = in.nextInt("n", 2, MAX);
		int m = in.nextInt("m", 0, n + EXTRA);
		in.eoln();
		for (int i = 0; i < m; i++) {
			in.nextInt("a[" + (i + 1) + "]", 1, n);
			in.nextInt("b[" + (i + 1) + "]", 1, n);
			in.eoln();
		}
	}
}
