import java.io.*;
import java.util.*;


class car{
    int cost,dis;
    car(int cost, int dis)
    {
      this.cost=dis;
      this.cost=dis;
      System.out.println("super make");
    }
  }
  class avante extends car{

    String model;
    avante(int cost,int dis,String model)
    {
      super(cost,dis);
      System.out.println("low class make");
    }
  }

public class Main5 {

  public static void main(String[] args) {
    
    avante av= new avante(1000,500,"avante");
  }
  
}
