import java.util.*;
import java.io.*;

class Main{
  
  static class Pair{

    int x,y;
    Pair(int x, int y)
    {
      this.x=x;
      this.y=y;
    }
  }
  static boolean [][] vis;
  static int n,m,len,ans;
  static List<Pair> blank=new ArrayList<>();
  static List<Pair> virus=new ArrayList<>();
  static int [][] src;
  static int [][] dsc;
  static Pair[] sel = new Pair[3]; //벽으로 3개 택 
  static int [] dx={0,0,-1,1};
  static int [] dy={-1,1,0,0}; 

  static void func()
  {
    Queue<Pair> q=new LinkedList<>();
    vis=new boolean[n][m];
    for(Pair cur:virus)
    {
      q.offer(cur);
      vis[cur.x][cur.y]=true;
    }
    while(!q.isEmpty())
    {
      Pair cur= q.poll();
      for(int dir=0;dir<4;dir++)
      {
        int nx=cur.x+dx[dir];
        int ny=cur.y+dy[dir];
        if(nx<0||nx>=n||ny<0||ny>=m)continue;
        if(vis[nx][ny]||dsc[nx][ny]!=0)continue;
        vis[nx][ny]=true;
        dsc[nx][ny]=2; //바이러스 퍼짐 
        q.offer(new Pair(nx,ny));  
      }
    }  
    int cnt=0;
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
      {
        if(dsc[i][j]==0)cnt++;
      }
    }
    ans=Math.max(ans,cnt);  
    return;
  }

  static void combi(int start ,int depth)
  {
    if(depth==3)
    {
      for(int i=0;i<n;i++)
      {
        dsc[i]=Arrays.copyOf(src[i],m);
      }
      for(int i=0;i<3;i++)
      {
        dsc[sel[i].x][sel[i].y]=2; //벽세우기
      }
      func();//안전영역 계산
      return;
    }
    for(int i=start;i<len;i++)
    {
      sel[depth]=blank.get(i);
      combi(i+1,depth+1);
    }

  }


  public static void main(String[ ] args) throws IOException
  {
    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    n=Integer.parseInt(st.nextToken());
    m=Integer.parseInt(st.nextToken());
    src=new int[n][m];
    dsc=new int[n][m];
    for(int i=0;i<n;i++)
    {
      st = new StringTokenizer(br.readLine());
      for(int j=0;j<m;j++)
      {
        src[i][j]=Integer.parseInt(st.nextToken());
        if(src[i][j]==0)
        {
          blank.add(new Pair(i,j));
        }
        if(src[i][j]==2)
        {
          virus.add(new Pair(i,j));
        }
      }
    }
    len=blank.size();
    combi(0,0);
    System.out.println(ans);
    



  }




}