#include<bits/stdc++.h>

using namespace std;
int ldp[1002]; //ldp[k] , k번째 인덱스 값을 끝으로하는 부분수열중 가장 긴 
int rdp[1002];

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n;
  cin>>n;
  vector<int> arr(n+2);
  for(int i=1;i<=n;i++)
  {
    cin>>arr[i];
  }
  //좌측에서 증가하는 부분수열 
  for(int i=1;i<=n;i++)
  {
    for(int j=0;j<i;j++)
    {
      if(arr[j]<arr[i])
        ldp[i]=max(ldp[i],ldp[j]+1);
    }
  }
  //우측에서 증가하는 부분수열
  for(int i=n;i>=1;i--)
  {
    for(int j=n+1;j>i;j--)
    {
      if(arr[j]<arr[i])
        rdp[i]=max(rdp[i],rdp[j]+1);
    }
  } 
  int ans=0;
  for(int i=1;i<=n;i++)
  {
    ans=max(ans,ldp[i]+rdp[i]-1);
    //cout<<ldp[i]<<' '<<rdp[i]<<'\n';
  }
  cout<<ans;





}