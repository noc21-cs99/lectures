/*
Problem: Magic Ship
URL: https://codeforces.com/problemset/problem/1117/C
Author : Ayush Modi
Discord Tag : hot9cups#3125
*/

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

public class Mod3magicship {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Origin
        int x1 = sc.nextInt(), y1 = sc.nextInt();

        // Destination
        int x2 = sc.nextInt(), y2 = sc.nextInt();

        // Length of weather forecast
        int n = sc.nextInt();
        sc.nextLine(); // to scan \n before scanning weather forecast

        // Weather forecast
        String weather = sc.nextLine();
        sc.close();

        // Storing the impact of the winds
        int x = 0, y = 0;
        List<List<Integer>> walkList = new ArrayList<>();
        walkList.add(Arrays.asList(0, 0));
        for (char wind : weather.toCharArray()) {
            if (wind == 'U')
                y++;
            else if (wind == 'D')
                y--;
            else if (wind == 'R')
                x++;
            else
                x--;
            walkList.add(Arrays.asList(x, y));
        }

        // initial limits
        long left = 0, right = (long) n * (Math.abs(x1 - x2) + Math.abs(y1 - y2)), ans = -1;
        while (left <= right) {
            long mid = left + (right - left) / 2;

            // Getting complete and partial cycles of weather
            int completeCycles = (int) (mid / n);
            int partialCycles = (int) (mid % n);

            // Getting the offset
            long x3 = x1 + ((long) completeCycles * x) + walkList.get(partialCycles).get(0);
            long y3 = y1 + ((long) completeCycles * y) + walkList.get(partialCycles).get(1);

            // Checking the Manhattan distance
            if (Math.abs(x2 - x3) + Math.abs(y2 - y3) <= mid) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        System.out.println(ans);
    }
}