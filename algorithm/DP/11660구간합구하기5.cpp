//#include<iostream>
//
//using namespace std;
//
//int arr[1025][1025];
//int dp[1025][1025];
//
//int main()
//{
//	ios::sync_with_stdio(0); cin.tie(0);
//	int n, m;
//	cin >> n >> m;
//	for (int i = 1; i <= n; i++)
//	{
//		int temp;
//		for (int j = 1; j <= n; j++)
//		{
//			cin >> temp;
//			arr[i][j] = temp;
//			dp[i][j] = dp[i][j - 1] + temp; //행별sn구하기 
//		}
//	}
//	int x1, y1, x2, y2;
//	for (int i = 0; i < m; i++)
//	{
//		int sum = 0;
//		cin >> x1 >> y1 >> x2 >> y2;
//		for (int i = x1; i <= x2; i++)
//		{
//			sum += dp[i][y2] - dp[i][y1 - 1];
//		}
//		cout << sum<<'\n';
//	}
//
//
//}