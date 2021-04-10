import ru.ifmo.validate.*;

public class Validate implements Validator {
	@Override
	public void validate(ValidatingScanner in) {
		int w = in.nextInt("w", 1, Tests.MAX_W);
		in.nextLong(0, Tests.MAX_N);
		in.eoln();
		for (int i = 0; i < w; i++) {
			in.nextInt("h_" + i, 0, Tests.MAX_H);
			in.eoln();
		}
		in.close();
	}
}
          