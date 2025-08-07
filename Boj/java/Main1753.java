import java.util.*;
import java.io.*;

class Main{

  static final int INF=1_000_000_000;
  static List<Pair>[] adj;
  static int [] dis;

  static class Pair{
    int w,v;
    Pair(int w, int v)
    {
      this.w=w;
      this.v=v;
    }
  }

  public static void main(String [] args) throws IOException
  {
    BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    st=new StringTokenizer(br.readLine());
    int V=Integer.parseInt(st.nextToken());
    int E=Integer.parseInt(st.nextToken());
    st=new StringTokenizer(br.readLine());
    int K=Integer.parseInt(st.nextToken());
    adj=new ArrayList[V+1];
    dis=new int[V+1];
    for(int i=1;i<=V;i++)
    {
      adj[i]=new ArrayList<>();
      dis[i]=INF;
    }
    dis[K]=0;
    for(int i=1;i<=E;i++)
    {
      st=new StringTokenizer(br.readLine());
      int u=Integer.parseInt(st.nextToken());
      int v=Integer.parseInt(st.nextToken());
      int w=Integer.parseInt(st.nextToken());
      adj[u].add(new Pair(w,v));
    }
    PriorityQueue<Pair> pq= new PriorityQueue<>((a,b)->Integer.compare(a.w,b.w));
    pq.offer(new Pair(0,K));
    while(!pq.isEmpty())
    {
      Pair cur = pq.poll();
      if(dis[cur.v]!=cur.w)continue;
      for(Pair next: adj[cur.v])
      {
        if(dis[next.v]>dis[cur.v]+next.w)
        {
          dis[next.v]=dis[cur.v]+next.w;
          pq.offer(new Pair(dis[next.v],next.v));
        }
      }
    }
    for(int i=1;i<=V;i++)
    {
      if(dis[i]==INF)
      {
        System.out.println("INF");
      }
      else
      {
        System.out.println(dis[i]);
      }

    }
  }
}