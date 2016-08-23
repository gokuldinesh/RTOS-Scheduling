import java.util.*;

class LSF
{
  public static void main(String args[])
  {
    Scanner sc=new Scanner(System.in);

    System.out.println("Enter number of processes");
    int n=sc.nextInt();

    int rel[]=new int[n];
    int exec[]=new int[n];
    int dead[]=new int[n];
    int fin[]=new int[n];
    int slack[]=new int[n];
    ArrayList<Integer> ready = new ArrayList<Integer>();
    ArrayList<Integer> wait = new ArrayList<Integer>();

    for(int i=0;i<n;i++)
    {
      System.out.println("Enter release time, execution time and deadline for process "+(i+1));
      rel[i]=sc.nextInt();
      exec[i]=sc.nextInt();
      dead[i]=sc.nextInt();
      wait.add(i);
    }

    quickSort(wait,rel);

    int time=0;
    boolean free=true;
    int current=0;
    slack=calcSlack(slack,dead,exec,time);
    
    while(((!(wait.isEmpty()))||(!(ready.isEmpty()))||!free)&&time<1000000)
    {
      while((!(wait.isEmpty())) && rel[wait.get(0)]<=time)
      {
        int t=wait.get(0);
        wait.remove(0);
        ready.add(t);
        
        System.out.println(time+".\tTask "+t+" inserted into ready queue");
      }
      slack=calcSlack(slack,dead,exec,time);
      
      for(int i=0;i<n;i++)
       System.out.println("Slack "+(i+1)+" = "+slack[i]);
      
      quickSort(ready,slack);
      for(int i=0;i<ready.size();i++)
       System.out.println("Ready "+(i+1)+" = "+ready.get(i));
      
      if(!free)
      {
          exec[current]--;
          if(exec[current]<=0)
          {
              System.out.println(time+".\tTask "+(current+1)+" has completed execution");
              dead[current]=1000000;
              free=true;
              fin[current]=time;
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
              
              slack=calcSlack(slack,dead,exec,time);
              
              for(int i=0;i<n;i++)
              System.out.println("Slack "+(i+1)+" = "+slack[i]);
              
              quickSort(ready,slack);
              for(int i=0;i<ready.size();i++)
              System.out.println("Ready "+(i+1)+" = "+ready.get(i));
          }
      }
      else
      {
          if(!ready.isEmpty())
          {
              int t=ready.get(0);
              if(slack[t]<slack[current])
              {
                System.out.println(time+".\tTask "+(current+1)+" has been preempted");
                ready.remove(0);
                ready.add(current);
                current=t;
                System.out.println(time+".\tTask "+(current+1)+" has started execution");
                slack=calcSlack(slack,dead,exec,time);
                
                for(int i=0;i<n;i++)
       System.out.println("Slack "+(i+1)+" = "+slack[i]);
                
                quickSort(ready,slack);
                for(int i=0;i<ready.size();i++)
       System.out.println("Ready "+(i+1)+" = "+ready.get(i));
              }  
          }
      }
      time++;
    }

    for(int i=0;i<n;i++)
    System.out.println("Task "+(i+1)+" has completed execution at "+fin[i]);
  }
  
  public static int[] calcSlack(int s[],int d[],int e[],int t)
  {
      for(int i=0;i<d.length;i++)
      {
        s[i]=(d[i]-e[i]-t);
      }  
      return s;
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