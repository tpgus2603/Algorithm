#include<bits/stdc++.h>

using namespace std;
int lc[27];
int rc[27];
int N;

void preorder(int cur)
{
  if(cur==-1)return;
  cout<<char(cur+'A');
  preorder(lc[cur]);
  preorder(rc[cur]);
}
void inorder(int cur)
{
  if(cur==-1)return;
  inorder(lc[cur]);
  cout<<char(cur+'A');
  inorder(rc[cur]);
}
void postorder(int cur)
{
  if(cur==-1)return;
  postorder(lc[cur]);
  postorder(rc[cur]);
  cout<<char(cur+'A');
}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N;
  char p,l,r;
  fill(lc,lc+N+1,-1);
  fill(rc,rc+N+1,-1);
  for(int i=1;i<=N;i++)
  {
    cin>>p>>l>>r;
    if(l!='.')lc[p-'A']=l-'A';
    if(r!='.')rc[p-'A']=r-'A';
  }
  preorder(0);
  cout<<'\n';
  inorder(0);
  cout<<'\n';
  postorder(0);
}