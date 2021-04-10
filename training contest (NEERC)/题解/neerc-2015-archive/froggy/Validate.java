import ru.ifmo.validate.ValidatingScanner;
import ru.ifmo.validate.Validator;

import java.util.HashSet;
import java.util.Set;

public class Validate implements Validator {
	@Override
	public void validate(ValidatingScanner in) {
		int w = in.nextInt("w", 1, Tests.MAX_C);
		int n = in.nextInt("n", 0, Tests.MAX_N);
		in.eoln();
		Set<Tests.Point> points = new HashSet<>();
		for (int i = 0; i < n; i++) {
			int x = in.nextInt("x_" + i, 1, w - 1);
			int y = in.nextInt("y_" + i, -Tests.MAX_C, Tests.MAX_C);
			Tests.Point point = new Tests.Point(x, y);
			assert !points.contains(point) : "Point " + i + " is duplicate";
			points.add(point);
			in.eoln();
		}
		in.close();
	}
}
          