import java.util.*;
import java.io.*;
import java.util.stream.IntStream;

/*
Author: Bhishmaraj S
Discord: @TravellingSalesman
Submission: https://atcoder.jp/contests/abc103/submissions/25247290
 */

class Week03Mod02IslandWars {


    /************************ SOLUTION STARTS HERE ***********************/

    static class Interval {
        int l, r, index;

        public Interval(int l, int r, int index) {
            this.l = l;
            this.r = r;
            this.index = index;
        }
    }

    private static void solve(FastScanner scan, PrintWriter out) {

        int N = scan.nextInt();
        int M = scan.nextInt();

        Interval[] sortedRight = new Interval[M];
        IntStream.range(0, M).forEach(i -> sortedRight[i] = new Interval(scan.nextInt(), scan.nextInt(), i));

        boolean[] covered = new boolean[M];

        Interval[] sortedLeft = Arrays.copyOf(sortedRight, M);

        Arrays.sort(sortedRight, (i1, i2) -> Integer.compare(i1.r, i2.r));
        Arrays.sort(sortedLeft, (i1, i2) -> Integer.compare(i1.l, i2.l));

        int cnt = 0;
        int ptr = 0;

        for (Interval interval : sortedRight) {
            if (!covered[interval.index]) {
                cnt++;
                while (ptr < M && sortedLeft[ptr].l < interval.r) {
                    covered[sortedLeft[ptr].index] = true;
                    ptr++;
                }
            }
        }

        out.println(cnt);
    }


    /************************ SOLUTION ENDS HERE ************************/


    /************************ TEMPLATE STARTS HERE *********************/

    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        PrintWriter out =
                new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)), false);
        solve(in, out);
        in.close();
        out.close();
    }

    static class FastScanner {
        BufferedReader reader;
        StringTokenizer st;

        FastScanner(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream));
            st = null;
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    String line = reader.readLine();
                    if (line == null) {
                        return null;
                    }
                    st = new StringTokenizer(line);
                } catch (Exception e) {
                    throw new RuntimeException();
                }
            }
            return st.nextToken();
        }

        String nextLine() {
            String s = null;
            try {
                s = reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return s;
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        char nextChar() {
            return next().charAt(0);
        }

        int[] nextIntArray(int n) {
            int[] arr = new int[n];
            int i = 0;
            while (i < n) {
                arr[i++] = nextInt();
            }
            return arr;
        }

        long[] nextLongArray(int n) {
            long[] arr = new long[n];
            int i = 0;
            while (i < n) {
                arr[i++] = nextLong();
            }
            return arr;
        }

        int[] nextIntArrayOneBased(int n) {
            int[] arr = new int[n + 1];
            int i = 1;
            while (i <= n) {
                arr[i++] = nextInt();
            }
            return arr;
        }

        long[] nextLongArrayOneBased(int n) {
            long[] arr = new long[n + 1];
            int i = 1;
            while (i <= n) {
                arr[i++] = nextLong();
            }
            return arr;
        }

        void close() {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /************************ TEMPLATE ENDS HERE ************************/
}