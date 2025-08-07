
import java.util.*;
import java.io.*;

class Main1003{

  static int [][] fibo= new int[41][2];
  public static void main(String[] args) throws IOException
  {
    Scanner sc= new Scanner(System.in);
    int t= sc.nextInt();
    fibo[0][0]=1;fibo[0][1]=0;
    fibo[1][0]=0;fibo[1][1]=1;
    for(int i=2;i<=40;i++)
    {
        fibo[i][0]=fibo[i-1][0]+fibo[i-2][0];
        fibo[i][1]=fibo[i-1][1]+fibo[i-2][1];
    }
    while(t-->0)
    {
      int n=sc.nextInt();
      System.out.println(fibo[n][0]+" "+fibo[n][1]);
    }
    
  }


}