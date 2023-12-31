#include<iostream>
#include<stack>
#include<queue>
#include<vector>

using namespace std;

vector<int>adj[10];
int p[10];
int depth[10];
void bfs(int root)
{
  queue<int>q;
  q.push(root);
  while(!q.empty())
  {
    int cur=q.front();
    q.pop();
    cout<<cur<<"->";
    for(auto nxt:adj[cur])
    {
      if(p[cur]==nxt)continue;
      q.push(nxt);
      p[nxt]=cur;
      depth[nxt]=depth[cur]+1;
    }
  }
}

void dfs(int root)
{
  stack<int>s;
  s.push(root);
  while(!s.empty())
  {
    int cur=s.top();
    s.pop();
    cout<<cur<<"->";
    for(auto nxt:adj[cur])
    {
      if(p[cur]==nxt)continue;
      s.push(nxt);
      p[nxt]=cur;
      depth[nxt]=depth[cur]+1;
    }
  }
}
int lc[9]={0,2,4,6,0,0,0,0,0};  //인덱스(노드번호)
int rc[9]={0,3,5,7,0,8,0,0,0};
void preorder(int cur){
  cout<<cur<<"->";
  if(lc[cur]!=0)preorder(lc[cur]); //왼쪽트리탐색
  if(rc[cur]!=0)preorder(rc[cur]); //오른쪽 트리 탐색
}
void inorder(int cur)
{
  if(lc[cur]!=0)inorder(lc[cur]);
  cout<<cur<<"->";
  if(rc[cur]!=0)inorder(rc[cur]);
}
void postorder(int cur)
{
  if(lc[cur]!=0)postorder(lc[cur]);
  if(rc[cur]!=0)postorder(rc[cur]);
  cout<<cur<<"->";
}

