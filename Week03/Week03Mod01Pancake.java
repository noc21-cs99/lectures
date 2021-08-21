import java.util.*;
import java.io.*;
import java.util.stream.IntStream;

/*
Author: Bhishmaraj S
Discord: @TravellingSalesman
 */

public class Week03Mod01Pancake {


    /************************ SOLUTION STARTS HERE ***********************/


    private static void solve(FastScanner scan, PrintWriter out) {

        int T = scan.nextInt();
        for (int tc = 1; tc <= T; tc++) {
            String str = scan.next();
            int K = scan.nextInt();
            int len = str.length();

            BitSet pancakes = new BitSet(len);
            IntStream.range(0, len).forEach(i -> pancakes.set(i, str.charAt(i) == '+'));

            int cost =
                IntStream.range(0, len - K + 1)
                    .map(i -> {
                        if (!pancakes.get(i)) {
                            pancakes.flip(i, i + K);
                            return 1;
                        } else {
                            return 0;
                        }
                    }).sum();

            // Cardinality Returns the number of bits set to true in BitSet

            out.println(String.format("Case #%d: %s",
                    tc, pancakes.get(len - K, len).cardinality() == K ? cost : "IMPOSSIBLE"));
        }

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