#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool dp[10001][10001]; 
int arr[10001];
int pre[10001];
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n,target;
  cin>>n;
  arr[0]=0;
  int temp;
  for(int i=1;i<=n;i++)
  {
    cin>>temp;
    arr[i]=temp;
  }
  cin>>target;
  // dp[i][j]= 배열의 i번째 까지원소를 고려해서 j를  완성이 가능한지 아닌지
  dp[0][0]=true;
  for(int i=1;i<=target;i++)
    dp[0][i]=false;
  for(int i=1;i<=n;i++)
  {
    for(int j=0;j<=target;j++)
    {
      if(dp[i-1][j]==true)
      {  
        dp[i][j]=true;
      }
      if(dp[i-1][j-arr[i]]==true||dp[i][j-arr[i]]==true)
      {
        dp[i][j]=true;
        pre[j]=arr[i];
      }
    }
  }
  if(dp[n][target]==false)
    cout<<"Impossible";
  else
  {
    for(int cur=target;cur!=0;cur-=pre[cur])
      cout<<pre[cur]<<' ';
  }

}