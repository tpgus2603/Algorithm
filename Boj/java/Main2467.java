import java.io.*;
import java.util.*;

class Main
{
  static int n;
  static int [] arr;
  static int lowerBound(int key)
  {
    int left=0; int right=arr.length;
    while(left<right)
    {
      int mid=(left+right)/2;
      if(arr[mid]<key)
      {
        left=mid+1;
      }
      else{
        right=mid;
      }
    }
    return left;
  }
  //-99 -94 -3 5 97 103

  public static void main(String[] args) throws IOException
  {
    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st=new StringTokenizer(br.readLine());
    int n= Integer.parseInt(st.nextToken());
    arr=new int[n];
    int []ans=new int[2];
    st=new StringTokenizer(br.readLine());
    for(int i=0;i<n;i++)
    {
      arr[i]=Integer.parseInt(st.nextToken());
    }
    int minn=2_000_000_000;
    for(int i=0;i<n;i++)
    {
      int idx=lowerBound(-1*arr[i]);

      //idx-1
      if(idx-1>=0&&i!=idx-1)
      {
        int t=Math.abs(arr[i]+arr[idx-1]);
        if(t<minn)
        {
          ans[0]=arr[i];
          ans[1]=arr[idx-1];
          minn=t;
        }
      }
      //idx
      if(idx!=arr.length&&i!=idx)
      {
        int t=Math.abs(arr[i]+arr[idx]);
        if(t<minn)
        {
          ans[0]=arr[i];
          ans[1]=arr[idx];
          minn=t;
        }
      }
    }
    Arrays.sort(ans);
    System.out.println(ans[0]+" "+ans[1]);

  }

}