import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Egor Kulikov (egor@egork.net)
 */
public class froggy_egor {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("froggy.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("froggy.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Froggy solver = new Froggy();
		solver.solve(1, in, out);
		out.close();
	}

	static class Froggy {
		public void solve(int testNumber, InputReader in, OutputWriter out) {
			int w = in.readInt();
			int n = in.readInt();
			Point[] points = new Point[n];
			for (int i = 0; i < n; i++) {
				points[i] = Point.readPoint(in);
			}
			double[][] distance = new double[n][n];
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i; j++) {
					distance[i][j] = distance[j][i] = points[i].distance(points[j]);
				}
			}
			double[] fromLeft = new double[n];
			for (int i = 0; i < n; i++) {
				fromLeft[i] = points[i].x;
			}
			recalculate(fromLeft, distance);
			double[] fromRight = new double[n];
			for (int i = 0; i < n; i++) {
				fromRight[i] = w - points[i].x;
			}
			recalculate(fromRight, distance);
			Point answer = new Point(w / 2d, 0);
			double leap = w / 2d;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					double current = Math.max(Math.max(fromLeft[i], fromRight[j]), distance[i][j] / 2d);
					if (current < leap) {
						leap = current;
						answer = new Segment(points[i], points[j]).middle();
					}
				}
				double current = Math.max(fromLeft[i], (w - points[i].x) / 2d);
				if (current < leap) {
					leap = current;
					answer = new Point((w + points[i].x) / 2d, points[i].y);
				}
				current = Math.max(fromRight[i], points[i].x / 2d);
				if (current < leap) {
					leap = current;
					answer = new Point(points[i].x / 2d, points[i].y);
				}
			}
			out.printLine(answer.x, answer.y);
		}

		private void recalculate(double[] value, double[][] distance) {
			int n = value.length;
			boolean[] was = new boolean[n];
			for (int i = 0; i < n; i++) {
				int minAt = -1;
				double min = Double.POSITIVE_INFINITY;
				for (int j = 0; j < n; j++) {
					if (!was[j] && value[j] < min) {
						minAt = j;
						min = value[j];
					}
				}
				was[minAt] = true;
				for (int j = 0; j < n; j++) {
					value[j] = Math.min(value[j], Math.max(value[minAt], distance[minAt][j]));
				}
			}
		}

	}

	static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;
		private SpaceCharFilter filter;

		public InputReader(InputStream stream) {
			this.stream = stream;
		}

		public int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public int readInt() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public boolean isSpaceChar(int c) {
			if (filter != null)
				return filter.isSpaceChar(c);
			return isWhitespace(c);
		}

		public static boolean isWhitespace(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		public double readDouble() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			double res = 0;
			while (!isSpaceChar(c) && c != '.') {
				if (c == 'e' || c == 'E')
					return res * Math.pow(10, readInt());
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			}
			if (c == '.') {
				c = read();
				double m = 1;
				while (!isSpaceChar(c)) {
					if (c == 'e' || c == 'E')
						return res * Math.pow(10, readInt());
					if (c < '0' || c > '9')
						throw new InputMismatchException();
					m /= 10;
					res += (c - '0') * m;
					c = read();
				}
			}
			return res * sgn;
		}

		public interface SpaceCharFilter {
			public boolean isSpaceChar(int ch);

		}

	}

	static class Point {
		public final double x;
		public final double y;


		public String toString() {
			return "(" + x + ", " + y + ")";
		}

		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}


		public boolean equals(Object o) {
			if (this == o)
				return true;
			if (o == null || getClass() != o.getClass())
				return false;

			Point point = (Point) o;

			return Math.abs(x - point.x) <= GeometryUtils.epsilon && Math.abs(y - point.y) <= GeometryUtils.epsilon;
		}


		public int hashCode() {
			int result;
			long temp;
			temp = x != +0.0d ? Double.doubleToLongBits(x) : 0L;
			result = (int) (temp ^ (temp >>> 32));
			temp = y != +0.0d ? Double.doubleToLongBits(y) : 0L;
			result = 31 * result + (int) (temp ^ (temp >>> 32));
			return result;
		}

		public double distance(Point other) {
			return GeometryUtils.fastHypot(x - other.x, y - other.y);
		}

		public static Point readPoint(InputReader in) {
			double x = in.readDouble();
			double y = in.readDouble();
			return new Point(x, y);
		}

	}

	static class GeometryUtils {
		public static double epsilon = 1e-8;

		public static double fastHypot(double x, double y) {
			return Math.sqrt(x * x + y * y);
		}

	}

	static class OutputWriter {
		private final PrintWriter writer;

		public OutputWriter(OutputStream outputStream) {
			writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
		}

		public OutputWriter(Writer writer) {
			this.writer = new PrintWriter(writer);
		}

		public void print(Object... objects) {
			for (int i = 0; i < objects.length; i++) {
				if (i != 0)
					writer.print(' ');
				writer.print(objects[i]);
			}
		}

		public void printLine(Object... objects) {
			print(objects);
			writer.println();
		}

		public void close() {
			writer.close();
		}

	}

	static class Segment {
		public final Point a;
		public final Point b;

		public Segment(Point a, Point b) {
			this.a = a;
			this.b = b;
		}

		public Point middle() {
			return new Point((a.x + b.x) / 2, (a.y + b.y) / 2);
		}

	}
}

