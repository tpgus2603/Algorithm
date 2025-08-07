#include<bits/stdc++.h>

using namespace std;

int n,s,ans;
int arr[20];
bool vis[20];
// void func(int k,int cur,int sum)
// {

//   if(cur==k)
//   { 
//     if(sum==s)ans++;
//     return;
//   }
//   for(int i=0;i<n;i++)
//   {
//     if(vis[i])continue;
//     vis[i]=true;
//     func(k,cur+1,sum+arr[i]);
//     vis[i]=false;
//   }
//   return;
// }

// int main()
// {
//   ios::sync_with_stdio(0);cin.tie(0);
//   cin>>n>>s;
//   for(int i=0;i<n;i++)
//     cin>>arr[i];
//   for(int k=1;k<=n;k++)
//   {
//     func(k,0,0);
//   }
//   cout<<ans;

// }



// int arr[20];
// int n, m;
// int cnt = 0;
// void select(int i, int sum) //a=현재 진행중인 배열 인덱스 
// {
// 	if (i == n)
// 	{
// 		if (sum == m)
// 			cnt++;
// 		return;
// 	}
// 	select(i + 1, sum + arr[i]);
// 	select(i + 1, sum);
// }

// int main()
// {
// 	ios::sync_with_stdio(0); cin.tie(0);
// 	cin >> n >> m;
// 	int temp;
// 	for (int i = 0; i < n; i++)
// 	{
// 		cin >> temp;
// 		arr[i] = temp;
// 	}
// 	select(0, 0);
// 	if (m == 0) cnt--;
// 	cout << cnt;


// }


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>s;
  for(int i=0;i<n;i++)
    cin>>arr[i];
  for(int k=1;k<=n;k++)
  {
    vector<int> mask;
    for(int i=0;i<k;i++)
      mask.push_back(0);
    for(int i=k;i<n;i++)
      mask.push_back(1);
    do
    {

      int sum=0;
      for(int i=0;i<n;i++)
      {
        if(mask[i]==0)
        {
          sum+=arr[i];
        }
      }
      if(sum==s)ans++;
    }while(next_permutation(mask.begin(),mask.end()));
  }
  cout<<ans;



}