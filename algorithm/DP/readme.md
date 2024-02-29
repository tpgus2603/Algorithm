-Dp(다이나믹 프로그래밍):  여러개의 하위 문제를 먼저 푼 후 그 결과를 쌓아올려 주어진 문제를 해결하는 알고리즘 -> 정해진 범위내에서 최대 최소를 찾을때 많이 사용됨
-
일반적인 dp는 보통 바텀업 방식 즉 밑에서 부터 아래로 누적하면서 계산을한다.

  ex)평범한 배낭문제,피보나치수열
  
  DP를 푸는 과정 (쌓아올릴 메모리의 한계가 있기에 범위에 따라 dp사용 가능한지 아닌지 확인... )
  
  1.테이블 정의하기 
  
  2.점화식찾기
  
  3.초기값 정하기 

  -2차원 dp: 한 행씩 채워가면서 dp를 적용한다.

  -Dp에서 경로 추적하기: 단순 값만 출력하는것이 아닌 거쳐온 과정을 알기위해 값을 위한 테이블 뿐만 아니라 추가적인 정보가 들어갈 경로 복원용테이블 필요.

  -평범한 배낭문제 
  ```
int dp[101][100001]={0}; //dp[i][j]= i번째 물건 까지 확인했을때 capacity가 j인 배낭의 최대가치
int dpk[101];
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<pair<int, int>>arr;
	pair<int, int>temp;
	arr.push_back({ 0, 0 });
	for (int i = 0; i < n; i++)
	{
		cin >> temp.W >> temp.V; 
		arr.push_back(temp);
	}
	sort(arr.begin(), arr.end());
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{ 
			if (j >= arr[i].W) 
				dp[i][j] = max(dp[i - 1][j - arr[i].W] + arr[i].V, dp[i - 1][j]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}
	cout << dp[n][k];
}
  ```
-계단오르기
```
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<int> stair;
	stair.push_back(0);
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		stair.push_back(temp);
	}
	int dp[301][3];  //dp[i][1]=i번째 계단을 밟는데 1계단째 밟은경우 dp[i][2]= 2계단째 밟는경우
	dp[1][1] = stair[1]; dp[1][2] = 0; //dp[i][1]은 2번째 전 계단에서 한칸 점프한것임 
	dp[2][1] = stair[2];
	dp[2][2] = stair[1] + stair[2];
	for (int i = 3; i <= n; i++)
	{
		dp[i][1] = max(dp[i - 2][1], dp[i - 2][2]) + stair[i];
		dp[i][2] = dp[i - 1][1] + stair[i];
	}
	cout << max(dp[n][1], dp[n][2]);
}

```

메모리 공간이 한정된 경우 1차원 dp테이블을 2중 반복문에서 반복하면서 갱신하는 문제역시 존재한다.

ex) 동전 2

문제
n가지 종류의 동전이 있다. 이 동전들을 적당히 사용해서, 그 가치의 합이 k원이 되도록 하고 싶다. 그러면서 동전의 개수가 최소가 되도록 하려고 한다. 각각의 동전은 몇 개라도 사용할 수 있다.

입력
첫째 줄에 n, k가 주어진다. (1 ≤ n ≤ 100, 1 ≤ k ≤ 10,000) 다음 n개의 줄에는 각각의 동전의 가치가 주어진다. 동전의 가치는 100,000보다 작거나 같은 자연수이다. 가치가 같은 동전이 여러 번 주어질 수도 있다.

출력
첫째 줄에 사용한 동전의 최소 개수를 출력한다. 불가능한 경우에는 -1을 출력한다.

```
풀이 2
using namespace std;
int n, k;
int a[10005], d[10005];
int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  fill(d, d + 10005, 100005);
  d[0] = 0; // 0원: 0개
  for (int i = 0; i < n; i++) {
    for (int j = a[i]; j <= k; j++)
      // 동전 하나 추가한 값과 기존 값 중 작은값
      d[j] = min(d[j], d[j - a[i]] + 1);
  }

  cout << (d[k] == 100005 ? -1 : d[k]) << '\n';
}

```

탑다운 dp: 메모제이션으로도 불리는 방식으로 재귀 호출을 하여 범위를 줄여나간다. 또한 맵을 이용하여 이미 계산된 경우는 중복하여 계산하지 않는다.

ex) 피보나치

```
#include<iostream>
#include<algorithm>
#include<map>
#include<unordered_map>
#define ll long long
#define X  1000000007
using namespace std;

map<ll,ll> fibo;


ll n;

ll cal( ll n)
{
  if(n==1)
    return 1;
  else if(n==0)
    return 0;
  if(fibo.count(n)>0)
    return fibo[n];

  if(n%2==0)
  {
    ll a=n/2;
    ll b= cal(a);
    ll c=cal(a-1);
    fibo[n]=(b+2*c)*b%X;
    return fibo[n];

  }
  else
  {
    ll a=(n+1)/2;
    ll b= cal(a);
    ll c= cal(a-1);
    fibo[n]=(b*b+c*c)%X;
    return fibo[n];
  }
  
} 

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n;
  ll t=cal(n);
  cout<<t;
}
```


