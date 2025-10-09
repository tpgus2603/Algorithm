#include<bits/stdc++.h>
using namespace std;
/*
1.진실을 말해야하는 사람이 속한 파티 구성원들 전부 진실 -> 해당 구성원이 속한 파티들 구성원들
-> 전부 진실을 말하기 -> 반복..(like dfs)

2.특정 구성원에 속한 파티들 다 찾고 파티속 구성원들에게 전파할 방법 찾기 
1.구성원-> 파티리스트 
2.파티-> 구성원리스트
dfs...
*/
bool truth[51];
vector<int> htop[51]; //구성원번호-> 파티리스트
vector<int> ptoh[51];//파티번호-> 구성원리스트 
int N,M;


void func(int cur)
{
  for(auto party: htop[cur])
  {
    if(!truth[party])
    {
      truth[party]=true;
      for(auto next:ptoh[party])
      {
        func(next);
      }
    } 
  }
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>M;
  int n;
  cin>>n;
  vector<int> tarr;
  for(int i=0;i<n;i++)
  {
    int temp;
    cin>>temp;
    tarr.push_back(temp);
  }
  for(int i=1;i<=M;i++)
  {
    int num;
    cin>>num;
    for(int j=0;j<num;j++)
    {
      int temp;
      cin>>temp;
      htop[temp].push_back(i);
      ptoh[i].push_back(temp);
    }
  }
  for(auto cur:tarr)
  {
    func(cur);
  }
  int ans=0;
  for(int i=1;i<=M;i++)
  {
    if(!truth[i])ans++;
  }
  cout<<ans;
}