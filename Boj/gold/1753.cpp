#include<bits/stdc++.h>

using namespace std;

#define C first 
#define V second
#define INF 22222222
int V,E;
vector<pair<int,int>> adj[20001];
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>V>>E;
  int st;
  cin>>st;
  int u,v,w;
  for(int i=1;i<=E;i++)
  {
    cin>>u>>v>>w;
    adj[u].push_back({w,v});
  }
  vector<int> dist(V+1,INF);
  dist.erase(remove_if(dist.begin(),dist.end(),[ ] (int x){return x%2==0;}),dist.end());
  cout<<dist.at(0)<<'\n';
  cout<<dist.size()<<'\n';
  dist[st]=0;
  // priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
  // pq.push({0,st});
  // while(!pq.empty())
  // {
  //   auto cur=pq.top();
  //   pq.pop();
  //   if(dist[cur.V]!=cur.C)continue; //중복간선도 처리가능하게해줌
  //   for(auto next:adj[cur.V])
  //   {
  //     if(dist[next.V]>dist[cur.V]+next.C)
  //     {
  //       dist[next.V]=dist[cur.V]+next.C;
  //       pq.push({dist[next.V],next.V});
  //     }
  //   }
  // }
  // for(int i=1;i<=V;i++)
  // {
  //   if(dist[i]!=INF)cout<<dist[i]<<'\n';
  //   else cout<<"INF"<<'\n';
  // }

}