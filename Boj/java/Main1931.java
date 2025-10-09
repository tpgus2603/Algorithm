import java.io.*;
import java.util.*;

class Main{

  static class Pair{

      int s,e;
      Pair(int s,int e)
      {
        this.s=s;
        this.e=e;
      }
  }

  public static void main(String[] args) throws IOException
  {

    BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st= new StringTokenizer(br.readLine());
    List<Pair> arr= new ArrayList<>();
    int n=Integer.parseInt(st.nextToken());
    for(int i=0;i<n;i++)
    {
      st= new StringTokenizer(br.readLine());
      int s=Integer.parseInt(st.nextToken());
      int e=Integer.parseInt(st.nextToken());
      arr.add(new Pair(s,e));
    }
    arr.sort((e1,e2)-> (e1.e==e2.e) ?(e1.s-e2.s):(e1.e-e2.e));
    int len=arr.size();
    int ans=1;
    int time=arr.get(0).e;
    for(int i=1;i<len;i++)
    {
      Pair cur=arr.get(i);
      if(time<=cur.s) //되는경우
      {
        time=cur.e;
        ans++;
      }
    }
    System.out.println(ans);
    
  }

}