#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, target;
  cin >> n;
  vector<int> arr(n + 1);
  arr[0] = 0;
  int temp;
  for (int i = 1; i <= n; i++)
  {
    cin >> temp;
    arr[i] = temp;
  }
  cin >> target;
  // dp[k] ->k를 완성가능한지 안하는지 판단하는 테이블,  pre[k] k를 완성하는데 이전에 더해진 원소
  vector<bool> dp(target + 1);
  vector<int> pre(target + 1);
  dp[0] = true;
  for (int i = 0; i <= target; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if (i - arr[j] >= 0 && dp[i - arr[j]] == true)
      {
        dp[i] = true;
        pre[i] = arr[j];
      }
    }
  }
  vector<int> path;
  if (dp[target] == false)
    cout << "Impossible";
  else
  {
    for (int cur = target; cur != 0; cur -= pre[cur]) // 원소 합 경로 추적(더해진 순서 그대로)
      path.push_back(pre[cur]);
    reverse(path.begin(), path.end());
    for (auto k : path)
      cout << k << ' ';
  }
  // //optional
  // auto k=max_element(arr.begin(),arr.end());
  // vector<int>arr2 (*k+1);
  // if (dp[target] == false)
  //   cout << "Impossible";
  // else
  // {
  //   for (int cur = target; cur != 0; cur -= pre[cur]) // 몇개씩 더해진지 카운트 출력
  //     { 
  //       arr2[pre[cur]]++;
  //     }
  //   for(int i=1;i<=*k;i++)
  //   {
  //     if(arr2[i]!=0)
  //       cout<<i<<'('<<arr2[i]<<") ";
  //   }
  // }
  return 0;
}