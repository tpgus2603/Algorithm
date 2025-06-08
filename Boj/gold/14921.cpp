#include<bits/stdc++.h>

using namespace std;

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n;
  cin>>n;
  vector<int> arr;
  int temp;
  for(int i=0;i<n;i++)
  {
    cin>>temp;
    arr.push_back(temp);
  }
  int ans=2e9;
  int lt,st;
  for(int i=0;i<n;i++)
  {
    int cur=arr[i];
    //현재위치기준 오른쪽
    auto it= lower_bound(arr.begin()+i+1,arr.end(),-cur);
    int idx=it-arr.begin();
    if(it!=arr.end()&&abs(cur+arr[i])<abs(ans))
    {
      ans=cur+arr[idx];
      lt=cur;
      st=arr[idx];
    }
    if(idx!=i+1)
    {
      if(abs(cur+arr[idx-1])<abs(ans))
      {
        ans=cur+arr[i-1];
        lt=cur;
        st=arr[i-1];
      }
    }
  }
  cout<<lt<<' '<<st;

}