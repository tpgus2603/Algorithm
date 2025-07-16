#include<bits/stdc++.h>

using namespace std;
int zero[41];
int one[41];
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int t;
  cin>>t;
  zero[0]=1;one[0]=0;
  zero[1]=0;one[1]=1;
  for(int i=2;i<=40;i++)
  {
    zero[i]=zero[i-1]+zero[i-2];
    one[i]=one[i-1]+one[i-2];
  }


  while(t--)
  { 
    int n;
    cin>>n;
    cout<<zero[n]<<' '<<one[n]<<'\n';
  }


}