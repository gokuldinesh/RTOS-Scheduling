import java.util.*;

class RM
{
  public static void main(String args[])
  {
    Scanner sc=new Scanner(System.in);

    System.out.println("Enter number of processes");
    int n=sc.nextInt();

    int rel[]=new int[n];
    int exec[]=new int[n];
    int texec[]=new int[n];
    int dead[]=new int[n];
    ArrayList<Integer> ready = new ArrayList<Integer>();
    ArrayList<Integer> wait = new ArrayList<Integer>();

    for(int i=0;i<n;i++)
    {
      System.out.println("Enter release time, execution time and period for process "+(i+1));
      rel[i]=sc.nextInt();
      exec[i]=sc.nextInt();
      dead[i]=sc.nextInt();
      wait.add(i);
      texec[i]=exec[i];
    }

    quickSort(wait,rel);

    int time=0;
    boolean free=true;
    int current=0;
    int prev=-1;
    int prevt=0;
    int period=10000;
    
    while(((!(wait.isEmpty()))||(!(ready.isEmpty()))||!free)&&time<1000000)
    {
      if(((time-prevt)==period && time!=0) || prev!=-1)
      {
           ready.add(prev);
           quickSort(ready,dead);
           period=dead[ready.get(0)];
      }
      
      while((!(wait.isEmpty())) && rel[wait.get(0)]<=time)
      {
          int t=wait.get(0);
          wait.remove(0);
          ready.add(t);
          System.out.println(time+".\tTask "+(t+1)+" inserted into ready queue");
      }
      quickSort(wait,rel);
      quickSort(ready,dead);
      
      if(!free)
      {
          exec[current]--;
          if(exec[current]<=0)
          {
              System.out.println(time+".\tTask "+(current+1)+" has completed execution");
              free=true;
              exec=texec;
              prev=current;
              prevt=time;
          }
      }
      
      if(free)
      {
          if(!ready.isEmpty())
          {
              free=false;
              current=ready.get(0);
              ready.remove(0);
              System.out.println(time+".\tTask "+(current+1)+" has started execution");
              quickSort(ready,dead);
          }
      }
      else
      {
          if(!ready.isEmpty())
          {
              int t=ready.get(0);
              if(((time-prevt)==period && time!=0)&&dead[t]<dead[current])
              {
                System.out.println(time+".\tTask "+(current+1)+" has been preempted");
                ready.remove(0);
                ready.add(current);
                wait.add(t);
                current=t;
                System.out.println(time+".\tTask "+(current+1)+" has started execution");
                quickSort(ready,dead);
              }  
          }
      }
      time++;
      if(time>10)
      break;
    }

  }

  public static void quickSort(ArrayList<Integer> a, int b[])
  {
      for(int i=0;i<a.size()-1;i++) 
      {
          for(int j=i+1;j<a.size();j++) 
          {
              if(b[a.get(i)]>b[a.get(j)])
              {
                  int t1 = a.get(i);
                  int t2 = a.get(j);
                  a.set(i,t2);
                  a.set(j,t1);
              }
          }
      }
  }
 }
