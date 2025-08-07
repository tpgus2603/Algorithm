import java.util.*;
import java.io.*;

class Main7562{
  static int [][] dis;
  static int dx[]={-2,-2,-1,-1,1,1,2,2};
  static int dy[]={-1,1,-2,2,-2,2,-1,1};

  static class pair
  {
    int X,Y;
    pair(int X, int Y)
    {
      this.X=X;
      this.Y=Y;
    }
  }

  public static void main(String [] args) throws IOException
  {
    
    Scanner sc= new Scanner(System.in);
    int t= sc.nextInt();
    while((t--)>0)
    { 
      int n=sc.nextInt();
      int x=sc.nextInt();
      int y=sc.nextInt();
      pair st=new pair(x,y);
      x=sc.nextInt();
      y=sc.nextInt();
      pair ed= new pair(x,y);
      //System.out.println(st.X+" "+st.Y+" ed: "+ed.X+" "+ed.Y);
      dis=new int[n][n];
      Queue<pair> q=new LinkedList<>();
      dis[st.X][st.Y]=1;
      q.offer(st);
      while(!q.isEmpty())
      {
        pair cur=q.poll();
        if(cur.X==ed.X&&cur.Y==ed.Y)
        {
          System.out.println(dis[cur.X][cur.Y]-1);
          break;
        }
        for(int dir=0;dir<8;dir++)
        {
          int nx=cur.X+dx[dir];
          int ny=cur.Y+dy[dir];
          if(nx<0||nx>=n||ny<0||ny>=n)continue;
          if(dis[nx][ny]!=0)continue;
          dis[nx][ny]=dis[cur.X][cur.Y]+1;
          q.offer(new pair(nx,ny));
        }
      }
    }








  }




}