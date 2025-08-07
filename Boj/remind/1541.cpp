#include<bits/stdc++.h>

using namespace std;

vector<string> split(const string & str, string deli)
{
  vector<string> token;
  int st=0;
  int ed=str.find(deli);
  while(ed!=-1)
  {
    if(st!=ed)
    {
      token.push_back(str.substr(st,ed-st));
    }
    st=ed+deli.length();
    ed=str.find(deli,st);
  }
  if(st!=str.length())
    token.push_back(str.substr(st));
  return token;
}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  string str;
  cin>>str;
  vector<string> tokens=split(str,"-");
  vector<int> arr; 
  for(auto cur: tokens)
  {
    vector<string> token=split(cur,"+");
    int sum=0;
    for(auto str: token)
    {
      sum+=stoi(str);
    }
    arr.push_back(sum);
  }
  int ans=arr[0];
  int len =arr.size();
  for(int i=1;i<len;i++)
    ans-=arr[i];
  cout<<ans;

}