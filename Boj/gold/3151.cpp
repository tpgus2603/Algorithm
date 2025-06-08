#include<bits/stdc++.h>

using namespace std;


// 2 7 6
// 3 7 6
// 6 7 2
// 1 8 6
// 2 8 5
// 3 8 5
// 5 8 2
// 6 8 1
// 7 8 1

//6 7 2
//5 8 2
//6 8 1
//7 8 1
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
  sort(arr.begin(),arr.end());
  int ans=0;
  for(int i=0;i<n-1;i++) //오른쪽 끝 
  {
    for(int j=i+1;j<n;j++)
    {
      int cur=arr[i]+arr[j];
      int idx1=lower_bound(arr.begin()+j+1,arr.end(),-cur)-arr.begin();
      int idx2=upper_bound(arr.begin()+j+1,arr.end(),-cur)-arr.begin();
      if(arr[idx1]==-cur)
        ans+=idx2-idx1;
    }
  } 
  cout<<ans;



}