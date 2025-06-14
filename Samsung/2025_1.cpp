#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#define X first 
#define Y second 
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
using namespace std;
int arr[50][50]; //신앙심 배열 
int food[50][50]; //음식배열  민트=2,초코=3,우유=4 민트초코5,초코우유=7 민트우유=6 민트초코유유=9;
int n,t;
vector<pair<int,int>> reco; //대표자 
bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=n)return true;
  return false;
}
int change(char c)
{
  switch(c)
  {
    case 'T':return 2;
    case 'C':return 3;
    case 'M':return 4;
  }
  return 0;
}

void morning()
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
      arr[i][j]++;
  }
}
void lunch() //대표자 선출 
{
  vector<vector<bool>> vis(n,vector<bool>(n,0)); //방문 배열 
  //그룹 에서 대표자 선출(좌표값만)
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(vis[i][j])continue;
      //cout<<i<<' '<<j<<'\n';
      vis[i][j]=true;
      int k=food[i][j]; //음식값 
      queue<pair<int,int>>q;
      vector<pair<int,int>> group; 
      q.push({i,j});
      group.push_back({i,j});
      pair<int,int> pt={i,j};
      int maxn=arr[i][j]; 
      while(!q.empty())
      {
        auto cur=q.front();
        q.pop();
        for(int dir=0;dir<4;dir++)
        {
          int nx=cur.X+dx[dir];
          int ny=cur.Y+dy[dir];
          if(over(nx,ny)||vis[nx][ny])continue;
          if(food[nx][ny]!=k)continue;
          q.push({nx,ny});
          vis[nx][ny]=true;
          group.push_back({nx,ny});
          if(arr[nx][ny]>=maxn)
          {
            //cout<<nx<<' '<<ny<<'\n';
            if(arr[nx][ny]==maxn)
            {
              if(pt.X<nx||(pt.X==nx&&pt.Y<ny))continue;
            }
            pt={nx,ny};
            maxn=arr[nx][ny]; //신앙심 
          }
        }
      }
      reco.push_back(pt);
      for(auto cur:group)
      {
        if(cur.X==pt.X&&cur.Y==pt.Y)continue;
        arr[cur.X][cur.Y]--;
        arr[pt.X][pt.Y]++;
      }
    }
  }
}
bool cmp(pair<int,int> a,pair<int,int> b)
{
  int c=arr[a.X][a.Y]; //신앙심
  int d=arr[b.X][b.Y];
    return c>d; //신앙심 내림차순 
}

int func(int a, int b) //약한 전파 합쳐질떄 
{
  //2+2,혹은 3이 껴있는 구조 
  if((a>=5&&b>=5)||a==9||b==9)return 9;
  else if((a<=4&&b>4)||(a>4&&b<=4)) //1개+2개 혹은 2개+1개 구조 
  {
    if(a+b==9)return 9; //합이 9인경우만 3개가됨 
    else return max(a,b);
  }
  else //1+1구조 
  {
    return a+b;
  }

}
void dinner()
{

  //대표자 순서 결정 
  sort(reco.begin(),reco.end());
  vector<pair<int,int>> one; 
  vector<pair<int,int>> two;
  vector<pair<int,int>> three;
  for(auto cur: reco)
  {
    int k=food[cur.X][cur.Y];
    if(k>=2&&k<=4)one.push_back(cur);
    else if(k>=5&&k<=7)two.push_back(cur);
    else three.push_back(cur);
  }
  stable_sort(one.begin(),one.end(),cmp);
  stable_sort(two.begin(),two.end(),cmp);
  stable_sort(three.begin(),three.end(),cmp);
  reco.clear();
  for(auto cur: one)
  {
    reco.push_back(cur);
  }
  for(auto cur: two)
  {
    reco.push_back(cur);
  }
  for(auto cur: three)
  {
    reco.push_back(cur);
  }
  // cout<<"------------'\n";
  // for(auto t: reco)
  // {
  //   cout<<t.X<<' '<<t.Y<<'\n';
  // }
  vector<vector<bool>> vis(n,vector<bool>(n,0)); //전파당한 경우 마킹 
  for(auto cur: reco)
  {
    if(vis[cur.X][cur.Y])continue;
    int x=arr[cur.X][cur.Y]-1; //간절함
    int dir=arr[cur.X][cur.Y]%4;
    arr[cur.X][cur.Y]=1;
    //cout<<"dir: "<<dir<<" x: "<<x<<'\n';
    int nx=cur.X+dx[dir];
    int ny=cur.Y+dy[dir];
    while(!over(nx,ny)&&x>0)
    {
      int a=food[cur.X][cur.Y];
      int b=food[nx][ny];
      //cout<<"food: "<<a<<' '<<b<<'\n';
      if(a==b) //동일음식 
      {
        nx+=dx[dir];
        ny+=dy[dir];
      }
      else //다른음식 
      {
        if(x>arr[nx][ny]) //강한 전파
        {
          food[nx][ny]=a;
          x-=(arr[nx][ny]+1);
          arr[nx][ny]+=1;
        }
        else //약한 전파  
        {
          int k=func(a,b);
          arr[nx][ny]+=x;
          x=0;
          food[nx][ny]=k;
        }
        vis[nx][ny]=true;
        nx+=dx[dir];
        ny+=dy[dir];
      }
    }  
  }
}
//신앙심 종합 
void cal()
{
  int a=0,b=0,c=0,d=0,e=0,f=0,g=0;
  for(int i=0;i<n;i++) 
  {
    for(int j=0;j<n;j++)
    {
      if(food[i][j]==9) //민트초코우유
      {
        a+=arr[i][j];
      }
      else if(food[i][j]==5) //민트 초코 
      {
        b+=arr[i][j];
      }
      else if(food[i][j]==6) //민트 우유
      {
        c+=arr[i][j];
      }
      else if(food[i][j]==7) //초코우유
      {
        d+=arr[i][j];
      }
      else if(food[i][j]==4)
      {
        e+=arr[i][j];
      }
      else if(food[i][j]==3)
      {
        f+=arr[i][j];
      }
      else g+=arr[i][j];
    }
  }
  cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<' '<<g<<'\n';
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>t;
  string temp;
  for(int i=0;i<n;i++)
  {
    cin>>temp;
    for(int j=0;j<n;j++)
    {
      int k=change(temp[j]);
      food[i][j]=k;
    }
  }
  //신앙심 입력 
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      cin>>arr[i][j]; 
    }
  }
  for(int i=0;i<t;i++)
  {
    morning();
    lunch();
     dinner(); 
     cal();
     reco.clear();
  }

}
