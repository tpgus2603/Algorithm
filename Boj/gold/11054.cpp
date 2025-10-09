#include<bits/stdc++.h>

using namespace std;

int N;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N;
  //끝이 i번쨰 수인 가장긴 증가하는 부분수열
  vector<int> ldp(N+1,1);
  vector<int> rdp(N+1,1);
  vector<int> arr(N+1,0);
  for(int i=1;i<=N;i++)
  {
    cin>>arr[i];
  }
  //ldp채우기 
  for(int i=2;i<=N;i++)
  {
    for(int j=1;j<i;j++)
    {
      if(arr[j]<arr[i])
      {
        ldp[i]=max(ldp[i],ldp[j]+1);
      }
    }
  }
  for(int i=N-1;i>=1;i--)
  {
    for(int j=N;j>i;j--)
    {
      if(arr[j]<arr[i])
      {
        rdp[i]=max(rdp[i],rdp[j]+1);
      }
    }
  }
  int ans=0;
  for(int i=1;i<=N;i++)
  {
    ans=max(ldp[i]+rdp[i]-1,ans);
  }
  cout<<ans;

  // for(int i=1;i<=N;i++)
  // {
  //   cout<<ldp[i]<<' '<<rdp[i]<<'\n';
  // }


}