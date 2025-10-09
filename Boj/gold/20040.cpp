#include<bits/stdc++.h>

using namespace std;

vector<int>p;
int n,m;
int find(int u)
{
  if(p[u]==u)return u;
  return p[u]=find(p[u]);
}
void merge(int u,int v)
{
  u=find(u);
  v=find(v);
  if(u==v)return ;
  p[u]=v;
}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m;
  p.assign(n,0);
  for(int i=0;i<n;i++)p[i]=i;
  int ans=0;
  int u,v;
  for(int i=1;i<=m;i++)
  {
    cin>>u>>v;
    if(find(u)==find(v))
    {
      ans=i;
      break;
    }
    merge(u,v);
  }
  cout<<ans;


}
