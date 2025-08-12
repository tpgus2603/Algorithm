import java.util.*;
import java.io.*;


class Main{

    static int [] parent;
    static class Edge
    {
      int c,u,v;
      Edge(int c,int u,int v)
      {
        this.c=c;
        this.u=u;
        this.v=v;
      }
    }
    static int find(int u)
    {
      if(parent[u]==u)
      {
        return u;
      }
      return parent[u]=find(parent[u]);
    }
    static void merge(int u, int v)
    {
      u=find(u);
      v=find(v);
      if(u==v)return;
      parent[u]=v;
    }


    public static void main(String[] args) throws IOException
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int v,e;
        v=Integer.parseInt(st.nextToken());
        e=Integer.parseInt(st.nextToken());
        List<Edge> edges=new ArrayList<>();
        parent=new int[v+1];
        for(int i=1;i<=v;i++)
        {
          parent[i]=i;
        }
        int a,b,c;
        for(int i=0;i<e;i++)
        { 
          st = new StringTokenizer(br.readLine());
          a=Integer.parseInt(st.nextToken());
          b=Integer.parseInt(st.nextToken());
          c=Integer.parseInt(st.nextToken());
          edges.add(new Edge(c,a,b));
        }
        edges.sort((e1,e2)-> e1.c-e2.c);
        int mTotal=0;
        int cnt=0;
        for(Edge cur : edges)
        {
          if(find(cur.u)==find(cur.v))continue;
          merge(cur.u,cur.v);
          cnt++;
          mTotal+=cur.c;
          if(cnt==v-1)break;
        }
        System.out.println(mTotal);
    }






}