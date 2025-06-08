#include<bits/stdc++.h>
#define X first 
#define Y second 
using namespace std;
bool vis[2001];
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int s;
  cin>>s;
  queue<pair<int,int>> q; //개수,초 
  q.push({1,0});
  vis[1]=true;
  int ans=1e9;
  while(!q.empty())
  {
    auto cur =q.front();
    q.pop();ㅊ
    if(cur.X==s)
    {
      ans=min(ans,cur.Y);
      continue;
    }
    //저장하고 붙여넣기 
    int next=cur.X*2;
    if(next<2*s&&!vis[next])
    {
      q.push({next,cur.Y+2});
      vis[next]=true;
    }
    next=cur.X-1;
    if(next>0&&!vis[next])
    {
      q.push({next,cur.Y+1});
      vis[next]=true;
    }

  }
}