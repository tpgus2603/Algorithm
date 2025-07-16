#include<bits/stdc++.h>

using namespace std;

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n;
  cin>>n;
  vector<int> arr;
  int t=0;
  for(int i=0;i<n;i++)
  {
    cin>>t;
    arr.push_back(t);
  }
  sort(arr.begin(),arr.end());
  int sum=arr[0];
  int ans=sum;
  for(int i=1;i<n;i++)
  {
    sum+=arr[i];
    ans+=sum;
  }
  cout<<ans;
}