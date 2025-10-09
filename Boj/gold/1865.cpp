#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define INF 1e9
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int T;
  cin>>T;
  while(T--)
  {
    int N,M,W;
    cin>>N>>M>>W;
    vector<tuple<int,int,int>> edge;
    vector<ll> d(N+1,0);
    //도로 정보가 주어짐
    int s,e,t; 
    for(int i=0;i<M;i++)
    {
      cin>>s>>e>>t;
      edge.push_back({s,e,t});
      edge.push_back({e,s,t});
    }
    for(int i=0;i<W;i++)
    {
      cin>>s>>e>>t;
      edge.push_back({s,e,t*-1});
    }
    int len=edge.size();
    bool cycle=false;
    for(int i=1;i<=N;i++)
    {
      for(int j=0;j<len;j++)
      {
        tie(s,e,t)=edge[j];
        if(d[e]>d[s]+t)
        {
          if(i==N){
            cycle=true;
            break;
          }
          d[e]=d[s]+t;
        }
      }
    }
    if(cycle)cout<<"YES";
    else cout<<"NO";
    cout<<'\n';
  }
}