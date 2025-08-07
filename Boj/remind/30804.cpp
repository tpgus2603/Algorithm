#include<bits/stdc++.h>

using namespace std;

int cnt[10]; 
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n;
  cin>>n;
  int temp;
  vector<int>arr(n+1,0);
  for(int i=1;i<=n;i++)
  {
    cin>>arr[i];
  }
  int sum=1;
  int kind=1;
  int ans=1;
  int left=1; //맨 왼쪽에서 포인터 시작
  cnt[arr[1]]++; 
  for(int cur=2;cur<=n;cur++)
  {

    if(cnt[arr[cur]]==0)kind++;
    cnt[arr[cur]]++;
    sum++;
    while(kind>2) //left이동시키면서 줄임 
    {
      cnt[arr[left]]--;
      if(cnt[arr[left]]==0)kind--;
      left++;
      sum--;
    }
    ans=max(ans,sum);
    //cout<<sum<<' '<<ans<<'\n';
  }
  cout<<ans;



}