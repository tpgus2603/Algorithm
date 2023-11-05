#include <iostream>
#include <string>

using namespace std;

//시간복잡도 개선을 위해 범위내에 +가없는게 확실하면 +찾기 넘어감
int calc(const string &str, int s, int e, bool isplus=true)  
{
  int result;
  if (e - s == 1)
    return str[s] - '0';
  else if (e - s > 1)
  {
    if (isplus) 
    {
      for (int i = s; i < e; i++) //+찾기
      {
        if (str[i] == '+')
        {
          result = calc(str, s, i,false) + calc(str, i + 1, e); //+앞부분은 +가없으니 false전달 
          break;
        }
        if(i==e-1) //끝까지 +못찾은경우 
          isplus=false;
      }
    }
    if (!isplus) //+가 없으면 *찾기 해당 함수 범위내엔 +가없는게 확실하니 false
    {
      for (int i = s; i < e; i++)
      {
        if (str[i] == '*')
        {
          result = calc(str, s, i,false) * calc(str, i + 1,e, false); 
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
  cin >> str;
  cout << calc(str, 0, str.size());
}