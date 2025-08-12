import java.util.*;
import java.io.*;

class Main1541{



  //55-50+40+90-70+60
  // 10+20+30 -40+50+60
  public static void main(String [] args)
  {
    Scanner sc= new Scanner(System.in);
    String str= sc.next();
    String [] tokens =str.split("\\-");
    int ans=0;
    String [] token= tokens[0].split("\\+");
    for(int j=0;j<token.length;j++)
    {
        ans+=Integer.parseInt(token[j]);
    }

    int len=tokens.length;
    for(int i=1;i<len;i++)
    {
        String cur=tokens[i];
        token= cur.split("\\+");
        int temp=0;
        for(int j=0;j<token.length;j++)
        {
          temp+=Integer.parseInt(token[j]);
        }
        ans-=temp;
    }
    System.out.println(ans);
  }





}