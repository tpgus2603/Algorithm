-Dp(다이나믹 프로그래밍):  여러개의 하위 문제를 먼저 푼 후 그 결과를 쌓아올려 주어진 문제를 해결하는 알고리즘 -> 정해진 범위내에서 최대 최소를 찾을때 많이 사용됨

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
  
