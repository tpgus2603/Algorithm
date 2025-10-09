#include<bits/stdc++.h>
using namespace std;
/*
다익스트라 두번 수행
1번 정점-> v1
v1-> N번정점 +v1-v2크기 
*/
#define C first
#define V second
#define INF 1e8
int N,E;
vector<pair<int,int>> adj[801];

int djk(int st,int ed)
{
  vector<int> d(N+1,INF);
  d[st]=0;
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
  pq.push({d[st],st});
  while(!pq.empty())
  {
    auto cur=pq.top();
    pq.pop();
    if(d[cur.V]!=cur.C)continue;
    for(auto next:adj[cur.V])
    {
      if(d[next.V]>d[cur.V]+next.C)
      {
        d[next.V]=d[cur.V]+next.C;
        pq.push({d[next.V],next.V});
      }
    }
  }
  return d[ed];
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>E;
  int a,b,c;
  for(int i=1;i<=E;i++)
  {
    cin>>a>>b>>c;
    adj[a].push_back({c,b});
    adj[b].push_back({c,a});
  }
  int u1,u2;
  cin>>u1>>u2;
  int ans=0;
  int d1=djk(1,u1)+djk(u1,u2)+djk(u2,N);
  int d2=djk(1,u2)+djk(u2,u1)+djk(u1,N);
  ans= d1<d2?d1:d2;
  if(ans>=INF)
  {
    cout<<-1;
    return 0;
  }
  cout<<ans;

}