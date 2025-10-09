#include<bits/stdc++.h>

using namespace std;

int N,M;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>M;
  vector<vector<int>>adj(N+1);
  int a,b;
  vector<int> indegree(N+1,0);
  for(int i=0;i<M;i++)
  {
    cin>>a>>b;
    adj[a].push_back(b);  
    indegree[b]++;
  }
  queue<int> q;
  for(int i=1;i<=N;i++)
  {
    if(indegree[i]==0)q.push(i);
  }
  vector<int> toporder;
  while(!q.empty())
  {
    auto cur= q.front();
    q.pop();
    toporder.push_back(cur);
    for(auto next:adj[cur])
    {
      indegree[next]--;
      if(indegree[next]==0)q.push(next);
    }
  }
  for(auto cur: toporder)cout<<cur<<' ';
}