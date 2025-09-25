#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>
#include<tuple>
#include<cstring>
#define X first 
#define Y second 
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int arr[6][6]; //정사각형 보드 
int pt; //유물 포인터 (0~M-1);
int K,M,ans;
using namespace std;
vector<int> tarr; //유물조각  

bool cmp(pair<int,int> a,pair<int,int> b)
{
  if(a.Y==b.Y)return a.X>b.X; //행번호 큰순
  else return a.Y<b.Y; //열번호 작은순 
}


int bfs(bool apply) //apply인경우만 탐색하고 0으로 채움 //3개이상 연결되어야 
{
  int sum=0;
  bool vis[6][6]={0};
  vector<pair<int,int>> path;
  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
    {
      vector<pair<int,int>>temp;
      if(vis[i][j])continue;
      vis[i][j]=true;
      int cnt=0;
      int v=arr[i][j];
      queue<pair<int,int>> q;
      q.push({i,j});
      while(!q.empty())
      {
        auto cur=q.front();
        temp.push_back(cur);
        q.pop();
        cnt++;
        for(int dir=0;dir<4;dir++)
        {
          int nx=cur.X+dx[dir];
          int ny=cur.Y+dy[dir];
          if(nx<0||nx>=5||ny<0||ny>=5||arr[nx][ny]!=v||vis[nx][ny])continue;
          vis[nx][ny]=true;
          q.push({nx,ny});
        }
      }
      if(cnt>=3)sum+=cnt;
      else temp.clear();
      //temp에 있는 경로에 넣어주기
      for(auto c:temp) 
      {
        path.push_back(c);
      }
    }
  }
  if(apply)
    {
      sort(path.begin(),path.end(),cmp);
      for(auto cur:path)
      {
        arr[cur.X][cur.Y]=tarr[pt++];
        //cout<<cur.X<<' '<<cur.Y<<'\n';
      }
    }
  return sum;
}

//2*r칸 만큼 시계방향으로 회전 후 bfs시행 ,apply=false면 원래상태로 돌림  
int spin(int r,int x,int y,bool apply)
{
  int tarr[7][7];
  memcpy(tarr,arr,sizeof(tarr)); //이전 백업 
  vector<int> temp;
  int top=x-1;
  int bot=x+1;
  int left=y-1;
  int right=y+1;
  for(int i=left;i<right;i++)temp.push_back(arr[top][i]);
  for(int i=top;i<bot;i++)temp.push_back(arr[i][right]);
  for(int i=right;i>left;i--)temp.push_back(arr[bot][i]);
  for(int i=bot;i>top;i--)temp.push_back(arr[i][left]);
  rotate(temp.begin(),temp.end()-2*r,temp.end());
  int idx=0;
  for(int i=left;i<right;i++)arr[top][i]=temp[idx++];
  for(int i=top;i<bot;i++)arr[i][right]=temp[idx++];
  for(int i=right;i>left;i--)arr[bot][i]=temp[idx++];
  for(int i=bot;i>top;i--)arr[i][left]=temp[idx++];
  int v=bfs(apply);
  if(!apply)
  {
    //복구
    memcpy(arr,tarr,sizeof(arr));
  }
  return v;

}

//탐사진행 
void explore()
{

  //각도,열,행 
  int maxn=0;
  tuple<int,int,int> sel;
  vector<tuple<int,int,int>> sarr;
  for(int y=1;y<=3;y++)
  {
    for(int x=1;x<=3;x++)
    {
      for(int r=1;r<=3;r++)
      {
        int cnt=spin(r,x,y,false);
        if(maxn<=cnt)
        {
          if(maxn<cnt)
          {
            maxn=cnt;
            sarr.clear();
          }
          sarr.push_back({r,y,x});
        }
      }
    }
  }
  //실제로 다시 spin,bfs진행 후 채우기까지 수행 
  sort(sarr.begin(),sarr.end());
  sel=sarr[0];
  int r,x,y;
  tie(r,y,x)=sel;
  int t=spin(r,x,y,true);
  if(t>=3)ans+=t;

  //연쇄획득
  while(1)
  {
    t=bfs(true);
    if(t<3)break;
    ans+=t;
  }

}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>K>>M;
  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)cin>>arr[i][j];
  } 
  int temp;
  for(int i=0;i<M;i++)
  {
    cin>>temp;
    tarr.push_back(temp);
  }
  while(K--)
  {
    ans=0;
    explore();
    if(ans==0)break;
    cout<<ans<<' ';
  }

}