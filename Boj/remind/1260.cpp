#include<bits/stdc++.h>

using namespace std;

vector<int> adj[1001];
bool vis[1001];

void dfs(int cur)
{
  cout<<cur<<' ';
  vis[cur]=true;
  for(auto next :adj[cur])
  {
    if(vis[next])continue;
    dfs(next);
  }
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n,m,v;
  cin>>n>>m>>v;
  int u,c;
  for(int i=0;i<m;i++)
  {
    cin>>u>>c;
    adj[u].push_back(c);
    adj[c].push_back(u);
  }

  for(int i=1;i<=n;i++)
  {
    sort(adj[i].begin(),adj[i].end());
  }

  //1.dfs
  dfs(v);
  cout<<'\n';
  fill(vis,vis+n+1,false);

  //2.bfs
  vis[v]=true;
  queue<int> q;
  q.push(v);
  while(!q.empty())
  {
    auto cur=q.front();
    q.pop();
    cout<<cur<<' ';
    for(auto next:adj[cur])
    {
      if(vis[next])continue;
      vis[next]=true;
      q.push(next);
    }
  }

}