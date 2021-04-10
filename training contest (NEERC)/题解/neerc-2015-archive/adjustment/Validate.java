import ru.ifmo.validate.*;

public class Validate implements Validator {
        static final int MAXN = 1000000;
        static final int MAXQ = 100000;

	@Override
	public void validate(ValidatingScanner in) {
		int n = in.nextInt("n", 1, MAXN);
		int q = in.nextInt("q", 1, MAXQ);
                in.eoln();                    
                for (int i = 0; i < q; i++) {
			String type = in.next("RC", 1, 1);
			assert type.equals("R") || type.equals("C");
			int x = in.nextInt("x_" + i, 1, n);
                        in.eoln();
		} 
                in.close();
	}
}
          