import java.io.*;
import java.util.*;


class Main3{

    static int [] dx={1,0,-1,0};
    static int [] dy={0,1,0,-1};
    static int [][]arr;
    static boolean [][] vis;
    
    static class Pair{
      int x,y;
      Pair(int x, int y)
      {
        this.x=x;
        this.y=y;
      }
    }
    public static void main(String [] args) throws IOException
    {
        BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter wr=new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        st=new StringTokenizer(br.readLine());
        int t=Integer.parseInt(st.nextToken());
        while(t-->0)
        {
          st=new StringTokenizer(br.readLine());
          int m=Integer.parseInt(st.nextToken());
          int n=Integer.parseInt(st.nextToken());
          int k=Integer.parseInt(st.nextToken());
          arr =new int[n][m];
          vis=new boolean[n][m];
          int ans=0;
          for(int i=0;i<k;i++)
          {
            st=new StringTokenizer(br.readLine());
            int x=Integer.parseInt(st.nextToken());
            int y=Integer.parseInt(st.nextToken());
            arr[y][x]=1;
          }
          for(int x=0;x<n;x++)
          {
            for(int y=0;y<m;y++)
            {
              if(arr[x][y]!=1||vis[x][y])continue;
              vis[x][y]=true;
              ans++;
              Queue<Pair> q=new LinkedList<>();
              q.offer(new Pair(x,y)); //시작점
              while(!q.isEmpty())
              {
                Pair cur=q.poll();
                for(int dir=0;dir<4;dir++)
                {
                  int nx=cur.x+dx[dir];
                  int ny=cur.y+dy[dir];
                  if(nx<0||nx>=n||ny<0||ny>=m)continue;
                  if(vis[nx][ny]||arr[nx][ny]!=1)continue;
                  vis[nx][ny]=true;
                  q.offer(new Pair(nx,ny));
                }
              }
            }
          }
          wr.write(ans+"\n");
        }
      wr.flush();
    }

}