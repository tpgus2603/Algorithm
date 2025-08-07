#include<bits/stdc++.h>



vector<string> split(const string & str ,string deli )
{
  int st =0;
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
}



int main()
{





}