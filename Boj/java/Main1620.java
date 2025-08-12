import java.util.*;
import java.io.*;

class Main1620{

    public static void main(String [] args) throws IOException
    {
      BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
      BufferedWriter bw= new BufferedWriter(new OutputStreamWriter(System.out));
      StringTokenizer st=new StringTokenizer(br.readLine());
      int n,m;
      n=Integer.parseInt(st.nextToken());
      m=Integer.parseInt(st.nextToken());
      HashMap<Integer,String> arr=new HashMap<>();
      HashMap<String,Integer> str= new HashMap<>();
      for(int i=1;i<=n;i++)
      {
        st=new StringTokenizer(br.readLine());
        String cur= st.nextToken();
        arr.put(i,cur);
        str.put(cur,i);
      }
      //문제
      for(int i=1;i<=m;i++)
      {
        st=new StringTokenizer(br.readLine());
        String cur= st.nextToken();
        if(cur.charAt(0)>='A') //포켓몬 질문 
        {
            bw.write(str.get(cur)+"\n");
        }
        else
        {
          bw.write(arr.get(Integer.parseInt(cur))+"\n");
        }
      }
      bw.flush();

    }
}