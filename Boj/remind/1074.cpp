#include<bits/stdc++.h>

using namespace std;

int n,r,c;
int ans;

void func(int num,int x,int y)
{
  if(num==0)
  {
    return ;
  } 
  int k=pow(2,num-1);
  int nx=x/k;
  int ny=y/k;
  if(nx==0&&ny==1)
     ans+=k*k;
  else if(nx==1&&ny==0)
    ans+=k*k*2;
  else if(nx==1&&ny==1)
    ans+=k*k*3;
  nx=x-nx*k;ny=y-ny*k;
  //cout<<ans<<' '<<nx<<' '<<ny<<'\n';
  func(num-1,nx,ny);
  return ;
}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>r>>c;
  func(n,r,c);
  cout<<ans;


}