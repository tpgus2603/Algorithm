import java.util.*;
import java.io.*;

class Main{


  static void ac(String func,String [] tokens)
  {
      Deque<Integer> dq=new ArrayDeque<>();
      StringBuilder sb=new StringBuilder();
      sb.append("[");
      if(!tokens[0].isEmpty())
      {
        for(String cur: tokens)
        {
          dq.offerLast(Integer.parseInt(cur));
        }
      }
      boolean reverse=false; //뒤집혀진상태

      for(char c:func.toCharArray())
      {
        if(c=='R')
        {
          reverse=!reverse;
        }
        else if(c=='D')
        {
          if(dq.isEmpty())
          {
            System.out.println("error");
            return;
          }
          if(reverse)
          {
            dq.pollLast();
          }
          else
          {
            dq.pop();
          }
        }
      }
      if(!dq.isEmpty())
      {
        List<Integer> arr=new ArrayList<>(dq);
        if(reverse)
        {
          Collections.reverse(arr);
        }
        for(Integer cur: arr)
        {
          sb.append(cur.toString());
          sb.append(",");
        }
        sb.deleteCharAt(sb.length()-1);
      }
      sb.append("]");
      System.out.println(sb);      
  }

  public static void main(String [] args) throws IOException
  {
    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st=new StringTokenizer(br.readLine());
    int t=Integer.parseInt(st.nextToken());
    while(t-->0)
    {
      st=new StringTokenizer(br.readLine());
      String func=st.nextToken();
      st=new StringTokenizer(br.readLine());
      st=new StringTokenizer(br.readLine());
      String arr=st.nextToken();
      String [] tokens=arr.substring(1,arr.length()-1).split(",");
      ac(func,tokens);
    }
  }





}