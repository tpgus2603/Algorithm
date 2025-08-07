
import java.util.*;
import java.io.*;

class Main {

    static List<Integer>[] adj;
    static boolean[] vis;

    static BufferedReader br;
    static BufferedWriter wr;
    static void dfs(int cur) throws IOException
    {

        wr.write(cur+" ");
        for(int next: adj[cur])
        {
            if(vis[next])continue;
            vis[next]=true;
            dfs(next);
        }
    }

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        wr = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        int n, m, v;
        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        v = Integer.parseInt(st.nextToken());
        adj = new ArrayList[n+1];
        for(int i=1;i<=n;i++)
        {
            adj[i]=new ArrayList<>();
        }
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            adj[a].add(b);
            adj[b].add(a);
        }
        for(int i=1;i<=n;i++)
        {
            Collections.sort(adj[i]);
        }
        //1.dfs구현
        vis=new boolean[n+1];
        vis[v]=true;
        dfs(v);
        wr.write("\n");
    
        //2.bfs구현
        vis =new boolean[n+1];
        Queue<Integer> q=new LinkedList<>();
        q.offer(v);
        vis[v]=true;
        while(!q.isEmpty())
        {
            int cur= q.poll();
            wr.write(cur+" ");
            for(int next: adj[cur])
            {
                if(vis[next])continue;
                vis[next]=true;
                q.add(next);
            }
        }
        wr.flush();


    }

}
