#include<stdio.h>
#include<stdlib.h>
void main()
{
     int i,n,temp[10];
     float avwt=0,avgtat=0;
     printf("Enter no. of process : \n");
     scanf("%d",&n);
     int at[n],bt[n],wt[n],tat[n];
     printf("enter arrival time : \n");
     for (i=0;i<n;i++)
         scanf("%d",&at[i]);
     for (i=0;i<n-1;i++)
         for (int j=i+1;j<n;j++)
         {
             if (at[i]>at[j])
             {
                int t = at[i];
                at[i]= at[j];
                at[j] = t;
             }
         }
     for (i=0;i<n;i++)
          printf("%d\t",at[i]);        
     for (i=0;i<n;i++)
         bt[i]=rand()%10;
     temp[0]=0;       
     for (i=1;i<n;i++)
          temp[i]=temp[i-1]+bt[i-1];
     for (i=0;i<n;i++)
     {
         wt[i]=temp[i]-at[i];
         wt[0]=0;
         avwt+=wt[i];
         tat[i]=wt[i]+bt[i];
         avgtat+=tat[i];
     }      
     avwt/=n;
     avgtat/=n;
     printf("\nProcess At\tBt\twt\ttat\n");
     for (i=0;i<n;i++)
         printf("\nP%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tat[i]);
     printf("Avg waiting time : %f\nAvg TurnAround time : %f\n",avwt,avgtat);    
}
