#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<utility>
#define X first 
#define Y second 
using namespace std;


//0~3까진 상하좌우 4~7까진 대각선 
int dx[8]={-1,0,1,0,-1,1,1,-1};
int dy[8]={0,1,0,-1,1,1,-1,-1};
int arr[21][21]; //-1 벽 0 빈칸 1이상 나무개수 
int rarr[21][21]; //제초제 남은 횟수
int n,m,k,c,ans;

bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=n)return true;
  return false;
}
void grow()
{
  for(int x=0;x<n;x++)
  {
    for(int y=0;y<n;y++)
    {
      int cnt=0;
      if(arr[x][y]<=0)continue;
      for(int dir=0;dir<4;dir++)
      {
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(over(nx,ny)||arr[nx][ny]<=0)continue;
        cnt++;
      }
      arr[x][y]+=cnt;
    }
  }
}
void spread()
{
  int tarr[21][21];
  memcpy(tarr,arr,sizeof(tarr));
  for(int x=0;x<n;x++)
  {
    for(int y=0;y<n;y++)
    {
      int cnt=0;
      if(arr[x][y]<=0)continue;
      for(int dir=0;dir<4;dir++)
      {
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(over(nx,ny)||rarr[nx][ny]||arr[nx][ny]!=0)continue;
        cnt++;
      }
      int temp=0;
      if(cnt>0)temp=arr[x][y]/cnt;
      for(int dir=0;dir<4;dir++)
      {
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(over(nx,ny)||rarr[nx][ny]||arr[nx][ny]!=0)continue;
        tarr[nx][ny]+=temp;
      }
    }
  }
  memcpy(arr,tarr,sizeof(arr));


}

int func(pair<int,int> cur,int depth,int cnt,int dir,bool flag)
{
  if(depth==k)return cnt;
  //
  int nx=cur.X+dx[dir];
  int ny=cur.Y+dy[dir];
  if(over(nx,ny))
  {
    return cnt;
  }
  else if(arr[nx][ny]<=0)
  {
    if(flag) //제초제 뿌림 
    {
      rarr[nx][ny]=c+1;
    }
    return cnt;
  }
  if(flag) //제초제 뿌림 
  {
    arr[nx][ny]=0;
    rarr[nx][ny]=c+1;
  }
  int temp=func(pair<int,int>{nx,ny},depth+1,cnt+arr[nx][ny],dir,flag);
  return temp; 
}


//제초제 뿌리기 
void rid() //대각선 4방향으로 k칸 만큼 제초할때 
{

  int maxn=0;
  int carr[21][21]; //각칸에 놓일때 제초되는 나무수 
  memset(carr,0,sizeof(carr));
  for(int x=0;x<n;x++)
  {
    for(int y=0;y<n;y++)  
    {
      if(arr[x][y]<=0)continue;
      int temp=arr[x][y];
      pair<int,int>cur={x,y};
      for(int dir=4;dir<8;dir++)
      {
        temp+=func(cur,0,0,dir,false);
      }
      carr[x][y]=temp;
      maxn=max(maxn,temp);
    }
  }
    // for(int i=0;i<n;i++)
    // {
    //   for(int j=0;j<n;j++)cout<<carr[i][j]<<' ';
    //   cout<<'\n';
    // }

  pair<int,int> candi;
  bool found=false;
  for(int i=0;i<n&&!found;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(carr[i][j]==maxn)
      {
        candi={i,j};
        found=true;
        break;
      }
    }
  }
  //실제 제거 수행 
  ans+=maxn;
  arr[candi.X][candi.Y]=0;
  rarr[candi.X][candi.Y]=c+1;
  for(int dir=4;dir<8;dir++)
  {
    func(candi,0,0,dir,true);
  }

}




int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m>>k>>c;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)cin>>arr[i][j];
  }
  
  while(m--)
  {
    grow();
    spread();
    // for(int i=0;i<n;i++)
    // {
    //   for(int j=0;j<n;j++)cout<<arr[i][j]<<' ';
    //   cout<<'\n';
    // }
    rid();
    //제초제 제거 
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {
        if(rarr[i][j]>0)rarr[i][j]--;
      }
    }
  }
  cout<<ans;





}

