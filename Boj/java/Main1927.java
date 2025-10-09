import java.util.*;
import java.io.*;

class Main{

  public static void main(String[] args) throws IOException
  {
    BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
    StringBuilder sb= new StringBuilder();
    PriorityQueue<Integer> heap=new PriorityQueue<>();
    StringTokenizer st= new StringTokenizer(br.readLine());
    int n=Integer.parseInt(st.nextToken());
    for(int i=0;i<n;i++)
    {
      st= new StringTokenizer(br.readLine());
      int k=Integer.parseInt(st.nextToken());
      if(k==0)
      {
        if(heap.isEmpty())sb.append(0+"\n");
        else sb.append(heap.poll()+"\n");
      }
      else
      {
        heap.offer(k);
      }
    }
    System.out.println(sb);
  }
}