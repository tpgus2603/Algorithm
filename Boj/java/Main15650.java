import java.io.*;
import java.util.*;

class Main15650{

  static int n,m;
  static int [] sel;
  

  static void func(int start ,int depth)
  {
    if(depth==m)
    { 
      for(int i=0;i<m;i++)
        System.out.print(sel[i]+" ");
      System.out.print("\n");
      return;
    }

    for(int i=start;i<=n;i++)
    {
      sel[depth]=i;
      func(i+1,depth+1);
    }
  }

  public static void main(String [] args)
  {
      Scanner sc=new Scanner(System.in);
      n=sc.nextInt();
      m=sc.nextInt();
      sel=new int[m];
      func(1,0);

  }




}