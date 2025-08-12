import java.util.*;
import java.io.*;



//oacaykp 
//kcapcak

class Main{
  static int [][] dp; //A는 i번째, B는 j번째 문자열

  public static void main(String[] args)
  {
    Scanner sc= new Scanner(System.in);
    String A= sc.next();
    String B= sc.next();
    int alen=A.length();
    int blen=B.length();
    dp=new int[alen+1][blen+1]; //1-based
    for(int i=1;i<=alen;i++)
    {
      for(int j=1;j<=blen;j++)
      {
        
        if(A.charAt(i-1)==B.charAt(j-1))
        {
          dp[i][j]=dp[i-1][j-1]+1;
        }
        else
        {
          dp[i][j]=Math.max(dp[i][j-1],dp[i-1][j]);
        }
        
      }
    }
    System.out.println(dp[alen][blen]);

  }
}