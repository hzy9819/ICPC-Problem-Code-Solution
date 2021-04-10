import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Iterator;
import java.io.BufferedWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.util.NoSuchElementException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Egor Kulikov (egor@egork.net)
 */
public class landscape_pm {
	public static void main(String[] args) {
		InputStream inputStream;
		try {
			inputStream = new FileInputStream("landscape.in");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		OutputStream outputStream;
		try {
			outputStream = new FileOutputStream("landscape.out");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		Landscape solver = new Landscape();
		solver.solve(1, in, out);
		out.close();
	}

	static class Landscape {
		public void solve(int testNumber, InputReader in, OutputWriter out) {
			int n = in.readInt();
			long w = in.readLong();

			long[] h = new long[n];
			for (int i = 0; i < n; i++) {
				h[i] = in.readLong();
			}
			long[] hr = h.clone();
			ArrayUtils.reverse(hr);
			long l = 0;
			for (int i = 0; i < n; i++) {
				if (h[i] > l) l = h[i];
			}
			long r = l + n + 1;

			long[] s = new long[n];
			long[] sr = new long[n];
			while (r > l + 1) {
				long m = (l + r) >> 1;
				build(h, m, s);
				build(hr, m, sr);
				ArrayUtils.reverse(sr);
				boolean ok = false;
				for (int i = 0; i < n; i++) {
					if (s[i] >= 0 && sr[i] >= 0) {
						long ss = s[i] + sr[i] - (m - h[i]);
						if (ss <= w) {
							ok = true;
							break;
						}
					}
				}
//			System.out.println(m + " " + ok + " " + Arrays.toString(s) + " " + Arrays.toString(sr));
				if (ok) {
					l = m;
				} else {
					r = m;
				}
			}
			out.printLine(l);
		}

		private void build(long[] h, long m, long[] s) {
			Arrays.fill(s, -1);
			int j = 1;
			long ss = m - h[0];
			for (int i = 0; i < h.length; i++) {
				while (j < h.length && h[j] < m + i - j) {
					ss += m + i - j - h[j];
					j++;
				}
				if (j == h.length) break;
				s[i] = ss;
				ss -= (m - h[i]);
				ss += (j - i - 1);
			}
		}

	}

	static interface LongCollection extends LongStream {
		public int size();

	}

	static interface LongStream extends Iterable<Long>, Comparable<LongStream> {
		public LongIterator longIterator();

		default public Iterator<Long> iterator() {
			return new Iterator<Long>() {
				private LongIterator it = longIterator();

				public boolean hasNext() {
					return it.isValid();
				}

				public Long next() {
					long result = it.value();
					it.advance();
					return result;
				}
			};
		}

		default public int compareTo(LongStream c) {
			LongIterator it = longIterator();
			LongIterator jt = c.longIterator();
			while (it.isValid() && jt.isValid()) {
				long i = it.value();
				long j = jt.value();
				if (i < j) {
					return -1;
				} else if (i > j) {
					return 1;
				}
				it.advance();
				jt.advance();
			}
			if (it.isValid()) {
				return 1;
			}
			if (jt.isValid()) {
				return -1;
			}
			return 0;
		}

	}

	static class LongArray extends LongAbstractStream implements LongList {
		private long[] data;

		public LongArray(long[] arr) {
			data = arr;
		}

		public int size() {
			return data.length;
		}

		public long get(int at) {
			return data[at];
		}

		public void removeAt(int index) {
			throw new UnsupportedOperationException();
		}

		public void set(int index, long value) {
			data[index] = value;
		}

	}

	static interface LongIterator {
		public long value() throws NoSuchElementException;

		public boolean advance();

		public boolean isValid();

	}

	static interface LongReversableCollection extends LongCollection {
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

		public long readLong() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			long res = 0;
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

		public interface SpaceCharFilter {
			public boolean isSpaceChar(int ch);

		}

	}

	static abstract class LongAbstractStream implements LongStream {

		public String toString() {
			StringBuilder builder = new StringBuilder();
			boolean first = true;
			for (LongIterator it = longIterator(); it.isValid(); it.advance()) {
				if (first) {
					first = false;
				} else {
					builder.append(' ');
				}
				builder.append(it.value());
			}
			return builder.toString();
		}


		public boolean equals(Object o) {
			if (!(o instanceof LongStream)) {
				return false;
			}
			LongStream c = (LongStream) o;
			LongIterator it = longIterator();
			LongIterator jt = c.longIterator();
			while (it.isValid() && jt.isValid()) {
				if (it.value() != jt.value()) {
					return false;
				}
				it.advance();
				jt.advance();
			}
			return !it.isValid() && !jt.isValid();
		}


		public int hashCode() {
			int result = 0;
			for (LongIterator it = longIterator(); it.isValid(); it.advance()) {
				result *= 31;
				result += it.value();
			}
			return result;
		}

	}

	static interface LongList extends LongReversableCollection {
		public abstract long get(int index);

		public abstract void set(int index, long value);

		public abstract void removeAt(int index);

		default public void swap(int first, int second) {
			if (first == second) {
				return;
			}
			long temp = get(first);
			set(first, get(second));
			set(second, temp);
		}

		default public LongIterator longIterator() {
			return new LongIterator() {
				private int at;
				private boolean removed;

				public long value() {
					if (removed) {
						throw new IllegalStateException();
					}
					return get(at);
				}

				public boolean advance() {
					at++;
					removed = false;
					return isValid();
				}

				public boolean isValid() {
					return !removed && at < size();
				}

				public void remove() {
					removeAt(at);
					at--;
					removed = true;
				}
			};
		}

		default public void inPlaceReverse() {
			for (int i = 0, j = size() - 1; i < j; i++, j--) {
				swap(i, j);
			}
		}

	}

	static class ArrayUtils {
		public static void reverse(long[] array) {
			new LongArray(array).inPlaceReverse();
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

		public void close() {
			writer.close();
		}

		public void printLine(long i) {
			writer.println(i);
		}

	}
}

