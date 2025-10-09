#include<bits/stdc++.h>

using namespace std;
int V,E;
int p[10001];
int find(int u)
{
  int t=p[u];
  if(t==u)return t;
  return p[u]=find(p[u]);
}
void merge(int u,int v)
{
  u=find(u);
  v=find(v);
  if(u==v)return;
  p[u]=v;

}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>V>>E;
  //거리,u,v순
  vector<tuple<int,int,int>> edge;
  int a,b,c;
  for(int i=0;i<E;i++)
  {
    cin>>a>>b>>c;
    edge.push_back({c,a,b});
  }
  for(int i=1;i<=V;i++)p[i]=i;
  sort(edge.begin(),edge.end());
  int total=0;
  int cnt=0;
  for(int i=0;i<E;i++)
  {
    tie(c,a,b)=edge[i];
    int u=find(a);
    int v=find(b);
    if(u==v)continue;
    merge(a,b);
    total+=c;
    cnt++;
    if(cnt==V-1)break;
  }
  cout<<total;

}