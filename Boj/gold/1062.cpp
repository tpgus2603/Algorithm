#include<bits/stdc++.h>

using namespace std;

char arr[21];
int n,k;

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int idx=0;
  for(char t='a';t<='z';t++)
  {
    if(t=='a'||t=='c'||t=='i'||t=='n'||t=='t')continue;
    arr[idx++]=t;
  }
  cin>>n>>k;
  vector<string> str;
  string temp;
  for(int i=0;i<n;i++)
  {
    cin>>temp;
    str.push_back(temp);
  }
  int t=k-5;
  int ans=0;
  vector<int> mask;
  if(t<0)
  {
    cout<<0;
    return 0;
  }
  for(int i=0;i<21;i++)
  {
    if(i<t)
    {
      mask.push_back(0);
    }
    else mask.push_back(1);
  }
  int z=0;
  do
  {
    z++;
    bool mapp[26]={ 0 };//선택한 문자 저장소 
    mapp['a'-'a']=true;mapp['c'-'a']=true;mapp['i'-'a']=true;
    mapp['n'-'a']=true;mapp['t'-'a']=true;
    for(int i=0;i<21;i++)
    {
      if(mask[i]==0)
      {
        char t=arr[i];
        mapp[t-'a'] =true;
      }
    }
    int cnt=0;
    for(auto cur: str)
    {
      bool flag=true;
      for(auto c :cur)
      {
        //if(c=='a'||c=='c'||c=='i'||c=='n'||c=='t')continue;
        if(!mapp[c-'a'])
        {
          flag=false;
          break;
        }
      }
      if(flag)cnt++;
    }
    ans=max(ans,cnt);
  }while(next_permutation(mask.begin(),mask.end()));
  
  cout<<ans;
}