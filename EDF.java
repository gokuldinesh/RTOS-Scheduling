import java.util.*;

class EDF
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
    
    while(((!(wait.isEmpty()))||(!(ready.isEmpty()))||!free)&&time<1000000)
    {
      while((!(wait.isEmpty())) && rel[wait.get(0)]<=time)
      {
        int t=wait.get(0);
        wait.remove(0);
        ready.add(t);
        
        System.out.println(time+".\tTask "+t+" inserted into ready queue");
      }
      quickSort(ready,dead);
      
      if(!free)
      {
          exec[current]--;
          if(exec[current]<=0)
          {
              System.out.println(time+".\tTask "+(current+1)+" has completed execution");
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
              
              quickSort(ready,dead);
          }
      }
      else
      {
          if(!ready.isEmpty())
          {
              int t=ready.get(0);
              if(dead[t]<dead[current])
              {
                System.out.println(time+".\tTask "+(current+1)+" has been preempted");
                ready.remove(0);
                ready.add(current);
                current=t;
                System.out.println(time+".\tTask "+(current+1)+" has started execution");
                
                quickSort(ready,dead);
              }  
          }
      }
      time++;
    }

    for(int i=0;i<n;i++)
    System.out.println("Task "+(i+1)+" has completed execution at "+fin[i]);
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
  /*public static void exchangeNumbers(ArrayList<Integer> a,int i, int j  )
  {
      int t=a.get(i);
      a.set(i,a.get(j));
      a.set(j,t);
  }
  
  public static void quickSort(ArrayList<Integer> a,int b[],int l,int h)
  {
      int i=l;
      int j=h;

      int pivot=b[(l+h)/2];
      if(pivot==0)
		  pivot=b[(l+h)/2+1];
      // Divide into two arrays
      while (i<=j)
      {
        while (b[i]<pivot)
        {
          i++;
        }
        //System.out.println("pivot="+pivot+"\n");
        while (b[j]>pivot)
        {
          
          //System.out.println(j+"\t"+l+"\t"+h+"\t"+pivot+"\t"+b[j]);
          j--;
        }
        //System.out.println("BOLOLO");

        if (i<=j)
        {
          exchangeNumbers(a,i,j);
          //move index to next position on both sides
          i++;
          j--;
        }
      }

      // call quickSort() method recursively
      if (l<j)
        quickSort(a,b,l,j);
      if (i<h)
        quickSort(a,b,i,h);
    }*/
 }
