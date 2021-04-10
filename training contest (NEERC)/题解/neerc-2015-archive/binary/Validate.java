import ru.ifmo.validate.*;

public class Validate implements Validator {
	@Override
	public void validate(ValidatingScanner in) {
		in.nextInt("n", 1, Tests.MAXN);
		in.eoln();
		in.close();
	}
}
          