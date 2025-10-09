#include<bits/stdc++.h>

using namespace std;

//뒤집어져있는지 상태확인
//",기준으로 파싱"
vector<string> split(const string & token)
{
  vector<string>tokens;
  int st=0;
  int ed=token.find(",");
  while(ed!=-1)
  {
    if(st!=ed)
    {
      tokens.push_back(token.substr(st,ed-st));
    }
    st=ed+1;
    ed=token.find(",",st);
  }
  if(st!=token.length())tokens.push_back(token.substr(st));
  return tokens;
}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);

  int T;
  cin>>T;
  while(T--)
  {
    bool error=false;
    string func;
    cin>>func;
    int n;
    cin>>n;
    deque<int> dq;
    string temp;
    cin>>temp;
    if(temp.length()>2)
    {
      vector<string> tokens=split(temp.substr(1,temp.length()-2));
      for(auto cur:tokens)dq.push_back(stoi(cur));
    }
    //for(auto cur:dq)cout<<cur<<' ';
    //func실행
    int len=func.length();
    bool rever=false;//뒤집어진경우
    for(int i=0;i<len;i++)
    {
      if(func[i]=='R')
      {
        rever=!rever;
      }
      else
      {
        //뒤집어진경우 뒤에 원소제거
        if(dq.empty())
        {
          cout<<"error"<<'\n';
          error=true;
          break;
        }
        if(rever)
        {
          dq.pop_back();
        }
        else dq.pop_front();
      }
    }
    if(error)continue;
    if(rever)reverse(dq.begin(),dq.end());
    cout<<"[";
    len=dq.size();
    for(int i=0;i<len;i++)
    {
      cout<<dq[i];
      if(i!=len-1)cout<<",";
    }
    cout<<"]"<<'\n';
  }
}