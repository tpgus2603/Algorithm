#include<bits/stdc++.h>

using namespace std;

int N,M;

int sel[9];

//depth-1 값 보다 큰 거로 고르기  
void func(int depth)
{
  if(depth>M)
  {
    for(int i=1;i<=M;i++)cout<<sel[i]<<' ';
    cout<<'\n';
    return ;
  }
  for(int i=1;i<=N;i++)
  {
    if(sel[depth-1]>=i)continue;
    sel[depth]=i;
    func(depth+1);
  }
}


int main()
{
  cin>>N>>M;
  func(1);




}