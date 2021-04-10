import ru.ifmo.validate.*;

public class Validate implements Validator {
	static final int MAXN = 10;
	static final int MINN = 2;
	static final int MAXK = 14;
	static final int MINK = 8;
	static final int MAXP = 10;
	static final int MAXE = 49;

	@Override
	public void validate(ValidatingScanner in) {
		int n = in.nextInt("n", MINN, MAXN);
		in.nextInt("k", MINK, MAXK);
		in.eoln();
		for (int i = 0; i < n; i++) {
			int p = in.nextInt("p_" + i, 1, MAXP);
			for (int j = 0; j < p; j++) {
				in.nextInt("e_" + i + "," + j, 0, MAXE);
			}
			in.eoln();
		}
		in.close();
	}
}
          