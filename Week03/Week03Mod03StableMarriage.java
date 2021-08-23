import java.util.*;
import java.io.*;

/*
Author: Bhishmaraj S
Discord: @TravellingSalesman
Submission: https://www.codechef.com/viewsolution/50038495
 */

class Week03Mod03StableMarriage {


    /************************ SOLUTION STARTS HERE ***********************/


    private static void solve(FastScanner scan, PrintWriter out) {

        int T = scan.nextInt();
        while (T-->0) {
            int N = scan.nextInt();
            int[][] womenChoice = new int[N][];
            int[][] menChoice = new int[N][];

            for (int i = 0; i < N; i++) {
                int w = scan.nextInt() - 1;
                womenChoice[w] = scan.nextIntArray(N);
                for (int j = 0; j < N; j++)
                    womenChoice[w][j]--;
            }
            for (int i = 0; i < N; i++) {
                int m = scan.nextInt() - 1;
                menChoice[m] = scan.nextIntArray(N);
                for (int j = 0; j < N; j++)
                    menChoice[m][j]--;
            }

            int[][] womenChoiceInverse = new int[N][N]; // for women w : wci[w][i] = position of man i in w's preference

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    womenChoiceInverse[i][womenChoice[i][j]] = j; // my cache is gonna cry :(

            ArrayDeque<Integer> unMatched = new ArrayDeque<>();
            for (int i = 0; i < N; i++)
                unMatched.add(i);

            // This holds the index
            int[] menMatching = new int[N];
            // This holds actual value
            int[] womenMatching = new int[N];

            for (int i = 0; i < N; i++)
                menMatching[i] = womenMatching[i] = -1; // un matched

            while (unMatched.size() > 0) {
                int m = unMatched.remove();
                int ptr = menMatching[m] + 1;
                for (; ptr < N; ptr++) {
                    int w = menChoice[m][ptr];
                    if (womenMatching[w] == -1) {
                        womenMatching[w] = m;
                        break;
                    } else if (womenChoiceInverse[w][m] < womenChoiceInverse[w][womenMatching[w]]) {
                        unMatched.add(womenMatching[w]);
                        womenMatching[w] = m;
                        break;
                    }
                }
                menMatching[m] = ptr;
            }

            for (int i = 0; i < N; i++)
                out.println((i + 1) + " " + (menChoice[i][menMatching[i]] + 1));

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