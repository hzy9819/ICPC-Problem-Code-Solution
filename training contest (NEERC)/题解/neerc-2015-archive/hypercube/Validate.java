import ru.ifmo.validate.ValidatingScanner;
import ru.ifmo.validate.Validator;

import java.util.ArrayList;
import java.util.List;

public class Validate implements Validator {
	@Override
	public void validate(ValidatingScanner in) {
		int m = in.nextInt("m", 1, Tests.MAX_DIM);
		int n = in.nextInt("n", 1, Tests.MAX_DIM);
		int k = in.nextInt("k", 1, Tests.MAX_DIM);
		in.eoln();
		List<Cell> cells = new ArrayList<>();
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				String row = in.next(".x", m);
				for (int l = 0; l < m; l++) {
					if (row.charAt(l) == 'x') {
						cells.add(new Cell(i, j, l));
					}
				}
				in.eoln();
			}
		}
		assert cells.size() == 8 : "There are " + cells.size() + " cells";
		int[] color = new int[8];
		for (int i = 0; i < 8; i++) {
			color[i] = i;
		}
		for (int i = 0; i < 8; i++) {
			Cell first = cells.get(i);
			for (int j = 0; j < i; j++) {
				Cell second = cells.get(j);
				if (Math.abs(first.x - second.x) + Math.abs(first.y - second.y) + Math.abs(first.z - second.z) == 1) {
					assert color[i] != color[j] : "Cycle";
					int target = color[j];
					for (int l = 0; l < 8; l++) {
						if (color[l] == target) {
							color[l] = color[i];
						}
					}
				}
			}
		}
		for (int i = 0; i < 8; i++) {
			assert color[i] == color[0] : "Disconnected";
		}
		in.close();
	}

	static class Cell {
		int x, y, z;

		public Cell(int x, int y, int z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
	}
}
          