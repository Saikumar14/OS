#include<stdio.h>
struct process
{
	int arrival_t,burst_t,waiting_t,turn_t,dt,number;
	int flag;
}p[15];

int n;
int q[15];  
int front=-1,rear=-1;


int deq()
{
    if(front==-1)
        printf("Underflow Condition");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
        return true;
    }
    return false;
}


int main()
{
    int i,j,c,time=0,sum_burst_t=0,tq;
    float avgwt=0;
     printf("\nEnter Number of Processes:\n");
     scanf("%d",&n);
     for(i=0,c=1;i<n;i++,c++)
     {
         p[i].number=c;
         printf("\n Process %d",c);
         printf("\n Enter Arrival Time :");
         scanf(" %d",&p[i].arrival_t);
         printf(" Enter Burst Time :");
         scanf(" %d",&p[i].burst_t);
         p[i].dt=p[i].burst_t;
         p[i].flag=0;
         sum_burst_t+=p[i].burst_t;
    }
    printf("\nEnter the time quantum:");
    scanf("%d",&tq);
    
    
    struct process temp;
    for(i=1;i<n;i++)
    {
        for(j=i;j<n-1;j++)
        {
            if(p[i].arrival_t>p[j].arrival_t)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    
    if(rear==15)
        printf("Overflow Condition");
    rear++;
    q[rear]=0;
    if(front==-1)
        front=0;
    
    printf("Process execution order: ");
    for(time=p[0].arrival_t;time<sum_burst_t;)      
    {   
        i=deq();

        
        if(p[i].dt<=tq)
        {                          
            
			p[i].flag=1;                   
            time=time + p[i].dt;
            p[i].dt=0;         
            printf(" %d ",p[i].number);
            p[i].waiting_t=time-p[i].arrival_t-p[i].burst_t;
            p[i].turn_t=time-p[i].arrival_t;      
            for(j=0;j<n;j++)    
            {
                if(p[j].arrival_t<=time && p[j].flag!=1&& isInQueue(j)!=true)
                {
                    if(rear==15)
                    printf("Overflow Condition");
                    rear++;
                    q[rear]=j;
                    if(front==-1)
                    front=0;
                }
            }
        }
        else               
        {
            time+=tq;
            p[i].dt-=tq;
            printf(" %d ",p[i].number);
            for(j=0;j<n;j++)                                               
            {
                if(p[j].arrival_t<=time && p[j].flag!=1&&i!=j&& isInQueue(j)!=1)
                {
                    
                    if(rear==15)
                    printf("Overflow Condition");
                    rear++;
                    q[rear]=j;
                    if(front==-1)
                    front=0;
                }
            }
           
            if(rear==15)
            printf("Overflow Condition");
            rear++;
            q[rear]=i;
            if(front==-1)
            front=0;

        }
    }

    printf("\nNumber\tArrival Time\tBurst Time\tTurnAround Time\tWaiting Timee");
    for(i=0;i<n;i++)
    {
        avgwt+=p[i].waiting_t;
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].number,p[i].arrival_t,p[i].burst_t,p[i].turn_t,p[i].waiting_t);
    }
    printf("\nAverage waiting time:%f\n",avgwt/n);
}
