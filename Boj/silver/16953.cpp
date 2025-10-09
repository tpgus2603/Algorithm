#include<bits/stdc++.h>

using namespace std;
#define X first 
#define Y second
#define ll long long 
int A,B;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>A>>B;
  queue<pair<ll,ll>> q;
  q.push({A,1});
  int ans=-1;
  while(!q.empty())
  {
    auto cur=q.front();
    q.pop();
    if(cur.X==B)
    {
      ans=cur.Y;
      break;
    }
    ll next=cur.X*2;
    if(next<=B)q.push({next,cur.Y+1});
    next=cur.X*10+1;
    if(next<=B)q.push({next,cur.Y+1});
  }
  cout<<ans;
}