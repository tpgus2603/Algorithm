#include<bits/stdc++.h>

using namespace std;

int N;
int main()
{
  vector<int> ans(2);
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N;
  vector<int> arr(N,0);
  for(int i=0;i<N;i++)cin>>arr[i];

  int temp=2e9;//임시 용액의합

  for(int i=0;i<N;i++)
  {
    int cur=arr[i];
    auto it=lower_bound(arr.begin()+i+1,arr.end(),-1*cur);
    if(it!=arr.end()&&*it!=cur)
    {
      int t=abs(cur+*it);
      if(t<temp)
      {
        ans[0]=cur;ans[1]=*it;
        temp=t;
      }
    }
    it--;
    int t=abs(cur+*it);
    if(t<temp&&*it!=cur)
    {
      ans[0]=cur;ans[1]=*it;
      temp=t;
    }
  }
  sort(ans.begin(),ans.end());
  cout<<ans[0]<<' '<<ans[1];

}