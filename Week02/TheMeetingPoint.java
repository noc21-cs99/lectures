import java.util.*;
public class TheMeetingPoint{

    int n,xi[],vi[];

    public double rightmost(double t){
        double res = Integer.MIN_VALUE;
        for(int i=0;i<n;i++){
            res=Math.max(res, xi[i]-vi[i]*t);
        }
        return res;
    }

    public double leftmost(double t){
        double res=Integer.MAX_VALUE;
        for(int i=0;i<n;i++){
            res=Math.min(res, xi[i]+vi[i]*t);
        }
        return res;
    }

    public boolean is_feasible(double K){
        return rightmost(K) <= leftmost(K);
    }

    public void main() {
        Scanner sc=new Scanner(System.in);
        n=sc.nextInt();
        xi=new int[n];
        vi=new int[n];
        for(int i=0;i<n;i++){
            xi[i]=sc.nextInt();
        }
        for(int i=0;i<n;i++){
            vi[i]=sc.nextInt();
        }
        sc.close();
    }
}


public class Run {
    public static void main(String[] args) {
        
    TheMeetingPoint m=new TheMeetingPoint();
    m.main();
    double l=0.0, r=1e9;
    double mid=0.0;
    while(Math.abs(r-l)>1e-6){
        mid=(l+r)/2;
        if(m.is_feasible(mid))
        r=mid;
        else
        l=mid;
    }
    System.out.println(mid);
}
}
