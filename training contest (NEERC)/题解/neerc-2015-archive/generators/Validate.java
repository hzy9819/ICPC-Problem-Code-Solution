import ru.ifmo.validate.*;

public class Validate implements Validator {
	@Override
	public void validate(ValidatingScanner in) {
		int n = in.nextInt("n", 1, Tests.MAX_N);
		in.nextInt("k", 1, Tests.MAX_K);
		in.eoln();
		for (int i = 0; i < n; i++) {
			int x = in.nextInt("x_" + i, 0, Tests.MAX_ABC);
			in.nextInt("a_" + i, 0, Tests.MAX_ABC);
			in.nextInt("b_" + i, 0, Tests.MAX_ABC);
			in.nextInt("c_" + i, x + 1, Tests.MAX_ABC);
			in.eoln();
		}
		in.close();
	}
}
          