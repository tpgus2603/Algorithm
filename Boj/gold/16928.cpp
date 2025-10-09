#include<bits/stdc++.h>

using namespace std;

int n,m;
int arr[101];//0이면 빈칸 , 0이 아니면 이동해야할 칸이 적혀있음
bool vis[101];
int cnt[101];
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m;
  for(int i=0;i<n;i++)
  {
    int x,y;
    cin>>x>>y;
    arr[x]=y;
  }
  for(int j=0;j<m;j++)
  {
    int u,v;
    cin>>u>>v;
    arr[u]=v;
  }
  // func(1,0);
  // cout<<ans;
  //bfs풀이
  queue<int> q;
  q.push(1);
  cnt[1]=1;
  while(!q.empty())
  {
    int cur=q.front();
    q.pop();
    int next;
    if(arr[cur]!=0)
    {
      cnt[arr[cur]]=cnt[cur];
      cur=arr[cur];
    }
    if(cur==100)break;
    for(int i=1;i<=6;i++)
    {
      next=cur+i;
      if(next>100||cnt[next]!=0)continue;
      q.push(next);
      cnt[next]=cnt[cur]+1;
    }
  }
  cout<<cnt[100]-1;


}