import java.io.*;
import java.util.*;


class Main2{
    public static void main(String[] args) throws IOException{
      BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
      BufferedWriter bw =new BufferedWriter(new OutputStreamWriter(System.out));
      String line =br.readLine();
      StringTokenizer st= new StringTokenizer(line );
      int a =Integer.parseInt(st.nextToken());
      int b=Integer.parseInt(st.nextToken());
      bw.write(a+" "+b+"\n");
  

      bw.write("okok its test");
      bw.flush();

    
    
    
    
    
    }
}