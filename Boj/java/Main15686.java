import java.util.*;
import java.io.*;

class Main{
  static class pair{
    int X,Y;
    pair(int X,int Y)
    {
      this.X=X;
      this.Y=Y;
    }
  }
;  
  static pair[] select;
  static List<pair> house=new ArrayList<>();
  static List<pair> chicken=new ArrayList<>();
  static int n,m,len;
  static int ans=1_000_000_000;

  static void func()
  {
    int sum=0;
    for(pair cur:house)
    {
      int minn=1_000_000_000;
      for(int i=0;i<m;i++)
      {
        minn=Math.min(minn,calc(cur,select[i]));
      }
      sum+=minn;
    }
    ans=Math.min(sum,ans);
  } 
  //
  //  static void func() {
  //       // 스트림을 이용한 간결한 로직
  //       int sum = house.stream()
  //           // 각 집(cur)에 대해 스트림을 생성
  //           .mapToInt(cur -> {
  //               // select 배열의 치킨집들과의 거리를 계산하여 스트림으로 변환
  //               return IntStream.range(0, m)
  //                   .map(i -> calc(cur, select[i]))
  //                   // 가장 가까운 거리(최소값)를 찾음
  //                   .min()
  //                   .orElse(Integer.MAX_VALUE); // 값이 없을 경우를 대비한 처리
  //           })
  //           // 모든 집의 최소 치킨 거리 합계를 계산
  //           .sum();
        
  //       ans = Math.min(sum, ans);
  //   }
  static int calc(pair a,pair b)
  {
    return Math.abs(a.X-b.X)+Math.abs(a.Y-b.Y);
  } 
  static void combi(int start, int depth)
  {
    if(depth==m)
    {
      func();
      return;
    }
    for(int i=start;i<len;i++)
    {
      select[depth]=chicken.get(i);
      combi(i+1,depth+1);
    }
  }


  public static void main(String [ ] args)
  {
    Scanner sc= new Scanner(System.in);
    n=sc.nextInt();
    m=sc.nextInt();
    select =new pair[m];
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {
         int t=sc.nextInt();
         if(t==1) house.add(new pair(i,j));
         else if(t==2)chicken.add(new pair(i,j));
      }
    }
    len=chicken.size();
    combi(0,0);
    System.out.println(ans);
  }




}