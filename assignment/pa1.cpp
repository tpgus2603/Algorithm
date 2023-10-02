#include<iostream>
#include<string>

using namespace std;

int calc(const string &str,int s,int e)
{
  int result;
  bool isplus=false;
  if(e-s==1)
    return str[s]-'0';
  else if(e-s>1)
    {
      for(int i=s;i<e;i++) //+찾기 
      {
        if(str[i]=='+')
        {
          result=calc(str,s,i)+calc(str,i+1,e);
          isplus=true;
          break;
        }
      }
      if(!isplus) //+가 없으면 -찾기 
      {
        for(int i=s;i<e;i++) 
        {
          if(str[i]=='*')
          {
            result=calc(str,s,i)*calc(str,i+1,e);
            break;
          }
        }
      }
    }
  return result;
  
}
int main()
{
  string str;
  cin>>str;
  cout<<calc(str,0,str.size());



}