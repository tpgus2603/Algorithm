#include<bits/stdc++.h>

#define D first 
using namespace std;

int parent[200000];

int find(int u)
{
  if(parent[u]==u)
    return u;
  return parent[u]=find(parent[u]);
}
void merge(int u, int v)
{

  u=find(u);
  v=find(v);
  if(u==v)
    return;
  parent[u]=v;
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  while(1)
  {
    int sum=0;
    int n,m;
    cin>>n>>m;
    if(n==0&&m==0)break;
    for(int i=0;i<n;i++)
      parent[i]=i;
    vector<tuple<int,int,int>> edge; //거리 u,v순 
    int u,v,c;
    for(int i=0;i<m;i++)
    {
      cin>>u>>v>>c;
      sum+=c;
      edge.push_back({c,u,v});
    }
    sort(edge.begin(),edge.end());
    int mtotal=0;
    int mcnt=0;
    for(int i=0;i<m;i++)
    {
      tie(c,u,v)=edge[i];
      if(find(u)==find(v))continue;
      merge(u,v);
      mtotal+=c;
      mcnt++;
      if(mcnt==n-1)break;
    }
    cout<<sum-mtotal<<'\n';
  }

}