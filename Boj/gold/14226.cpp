#include<bits/stdc++.h>
#define X first 
#define Y second 
using namespace std;
//개수,클립보드개수  (클립보드 개수가 다른경우는 다른 케이스로 해당 개수를 채워도 추후에 갱신될수있음 )
bool vis[2001][2001]; 
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int s;
  cin>>s;
  queue<tuple<int,int,int>> q; //개수,초,클립보드개수  
  q.push({1,0,0});
  vis[1][0]=true;
  int ans=1e9;
  while(!q.empty())
  {
    int a,b,c;
    tie(a,b,c) =q.front();
    q.pop();
    if(a==s)
    {
      ans=b;
      break;
    }
    //클립보드에서 가져오기 
      int next=a+c;
      if(next<2*s&&!vis[next][c])
      {
        q.push({next,b+1,c});
        vis[next][c]=true;
      }
    // 클립보드에 붙여넣기
    if(2*a<2*s&&!vis[next][a])
      q.push({a,b+1,a});
    //한개 제거하기 
    next=a-1;
    if(next>0&&!vis[next][c])
    {
      q.push({next,b+1,c});
      vis[next][c]=true;
    }
  }
  cout<<ans;
}