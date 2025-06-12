#include<bits/stdc++.h>
using namespace std;
#define X first 
#define Y second
int dx[8]={-1,-1,-1,1,1,1,0,0};
int dy[8]={-1,0,1,-1,1,0,-1,1};
vector<int> tree[11][11]; //나무는 힙으로 관리 .. (나이)
int energy[11][11];
int arr[11][11]; //양분 공급값 저장소 
int n,m,k;
int t;
bool over(int x,int y)
{
  if(x<=0||x>n||y<=0||y>n)return true;
  return false;
}

void spsummer() //봄과 여름 로직 수행 
{
  vector<tuple<int,int,int>> death; //죽을 나무 목록 (x,y,나이)
  for(int i=1;i<=n;i++)
  {
    //자신의 나이만큼 양분먹기 
    for(int j=1;j<=n;j++)
    {
      vector<int> pq;
      sort(tree[i][j].begin(),tree[i][j].end());
      int len=tree[i][j].size();
      int idx=0;
      while(idx<len)
      {
        auto cur=tree[i][j][idx];
        if(energy[i][j]>=cur)
        {
          energy[i][j]-=cur;
          pq.push_back(cur+1);//나무나이+1
        }
        else
        {
          death.push_back({i,j,cur});
        }
        idx++;
      }
      tree[i][j]=pq; //갱신 
    }
  }
  //여름 죽은나무 양분 분배
  for(auto cur: death)
  {
    auto[x,y,z]=cur;
    //cout<<"t: "<<t<<' '<<x<<' '<<y<<' '<<z<<' '<<'\n';
    energy[x][y]+=z/2;
  }

}
void fall()
{
  //나무 분배
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      auto cur=tree[i][j];
      int idx=0;
      int len=tree[i][j].size();
      while(idx<len)
      {
        int age=tree[i][j][idx];
        if(age%5==0)
        {
          for(int dir=0;dir<8;dir++)
          {
            int nx=i+dx[dir];
            int ny=j+dy[dir];
            if(over(nx,ny))continue;
            tree[nx][ny].push_back(1);
          }
        }
        idx++;
      }
      //tree[i][j]=pq;
    }
  }
}
//양분 분배 
void winter()
{
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      energy[i][j]+=arr[i][j];
    }
  }
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  
  int ans=0;
  cin>>n>>m>>k;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      energy[i][j]=5;
    }
  }
  //겨울마다 각 칸에 추가되는 양분 배열
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      cin>>arr[i][j];
    }
  }
  for(int i=0;i<m;i++)
  {
    int x,y,z;
    cin>>x>>y>>z;
    tree[x][y].push_back(z);
  }
  while(k--)
  {
    t++;
    spsummer();
    fall();
    winter();
  }
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      ans+=tree[i][j].size();
    }
  }
  cout<<ans;





}