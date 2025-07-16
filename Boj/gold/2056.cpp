#include<bits/stdc++.h>

using namespace std;

vector<int>adj[10001]; //선행관계 기록노드 
int tarr[10001];//남은 작업 실행 시간 
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n;
  cin>>n;
  vector<int> indegree(n+1);
  for(int i=1;i<=n;i++)
  {
    int t,k;
    cin>>t>>k;
    tarr[i]=t;
    int temp; //
    for(int j=0;j<k;j++)
    {
      cin>>temp;
      adj[temp].push_back(i);
      indegree[i]++;
    }
  }
  queue<int> q;
  vector<int> st(n+1,0);
  vector<int> ed(n+1,0);
  for(int i=1;i<=n;i++)
  {
    if(indegree[i]==0)q.push(i);
    ed[i]=tarr[i];
  }
  while(!q.empty())
  {
    int u=q.front();
    q.pop();
    for(int v: adj[u])
    {
      st[v]=max(st[v],ed[u]); //작업 시작시간 결정 
      indegree[v]--;
      if(indegree[v]==0) //다음에 실행될 작업으로 결정 
      {
        q.push(v);
        ed[v]=st[v]+tarr[v];
      }
    }
  }
  int ans=*max_element(ed.begin(),ed.end());
  cout<<ans;

}