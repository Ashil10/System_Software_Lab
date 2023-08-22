#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct process
{
	char name[10];
	int at, bt, ct, wt, tat, prio;
};

void insertp(struct process p[],int n)
{
	for(int i=0;i<n;i++)
	{
		printf("\n%d.\nProcessID: ",i+1);
		scanf("%s",p[i].name);
		printf("Arrival Time: ");
		scanf("%d",&p[i].at);
		printf("Burst Time: ");
		scanf("%d",&p[i].bt);
	}
}

void table(struct process p[], int n)
{
	printf("\n\n***************************************************");
	printf("\n   Name      AT      BT      CT      TAT      WT    ");
	for(int i=0;i<n;i++)
	{
		printf("\n    %s       %d       %d       %d       %d       %d    ",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
		
	}
	printf("\n***************************************************\n");
}
void gchart(struct process p[], int n)
{

	int star=n*6+n;
	
	printf("\n\n");
	for(int i=0;i<=star;i++)
		printf("-");
	printf("\n");
	for(int i=0;i<n;i++)
		printf("|  %s  ",p[i].name);
	printf("|\n");
	for(int i=0;i<=star;i++)
		printf("-");
	printf("\n");
	
	int time=0;
	for(int i=0;i<n;i++)
	{
		if(time<10&&time>0)
			printf("0");
		printf("%d     ",time);
		time=time+p[i].bt;
	}
	printf("%d\n",time);
	
}
void calc(struct process p[], int n)
{
	float totalWT=0, totalTAT=0;
	for(int i=0;i<n;i++)
	{
		int time=0;
		for(int j=0;j<=i;j++)
			time=time+p[j].bt;
		p[i].ct=time;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		
		totalWT=totalWT+p[i].wt;
		totalTAT=totalTAT+p[i].tat;
	}
	float avgWT=totalWT/n;
	float avgTAT=totalTAT/n;
	
	printf("\nAverage Waiting time= %.2f",avgWT);
	printf("\nAverage TurnAround time= %.2f",avgTAT);
}

void fcfs_main()
{
	printf("Enter number of processes:");
	int n;
	scanf("%d",&n);
	
	struct process p[n];
	insertp(p,n);
	
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-1;j++)
			if(p[j].at>p[j+1].at)
			{
				struct process temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
			
	gchart(p,n);
	calc(p,n);
	table(p,n);

}
void sjf_main()
{
	printf("Enter number of processes:");
	int n;
	scanf("%d",&n);
	
	struct process p[n];
	insertp(p,n);
	
	int time=0;
	for(int i=0;i<n;i++)
		if(p[i].at==0)
		{
			struct process temp=p[i];
			p[i]=p[0];
			p[0]=temp;
			break;
		}
	
	for(int i=0;i<n-1;i++)
	{
		struct process small=p[i];
		int indx=i;
		
		for(int j=i+1;j<n;j++)
			if(p[j].bt<small.bt&&p[j].at<=time)
			{
				small=p[j];
				indx=j;
			}
		
		p[indx]=p[i];
		p[i]=small;
		time=time+p[i].bt;
	}
	gchart(p,n);
	calc(p,n);
	table(p,n);
}

void priority_main()
{
	printf("Enter number of processes:");
	int n;
	scanf("%d",&n);
	
	struct process p[n];
	for(int i=0;i<n;i++)
	{
		printf("\n%d.\nProcessID: ",i+1);
		scanf("%s",p[i].name);
		printf("Arrival Time: ");
		scanf("%d",&p[i].at);
		printf("Burst Time: ");
		scanf("%d",&p[i].bt);
		printf("Priority: ");
		scanf("%d",&p[i].prio);
	}
	int time=0;
	for(int i=0;i<n;i++)
		if(p[i].at==0)
		{
			struct process temp=p[i];
			p[i]=p[0];
			p[0]=temp;
			break;
		}
	
	for(int i=0;i<n-1;i++)
	{
		struct process small=p[i];
		int indx=i;
		
		for(int j=i+1;j<n;j++)
			if(p[j].prio>small.prio&&p[j].at<=time)
			{
				small=p[j];
				indx=j;
			}
		
		p[indx]=p[i];
		p[i]=small;
		time=time+p[i].bt;
	}
	gchart(p,n);
	calc(p,n);
	table(p,n);
	
}
struct process ready[50];
int front=0, rear=-1;

void push(struct process t)
{
	ready[++rear]=t;
}
struct process pop(int b)
{
	struct process t=ready[front];
	front++;
	t.bt=b;
	return t;
}
void rr_calc(struct process p[],int n, struct process q[], int m)
{
	for(int i=0;i<m;i++)
	{
		int time=0;
		for(int j=0;j<=i;j++)
			time=time+q[j].bt;
		q[i].ct=time;
		
		char qname[10];
		strncpy(qname,q[i].name,10);
		int index;
		for(int j=0;j<n;j++)
		{
			if(!strcmp(p[j].name,qname))
				index=j;
		}
		p[index].ct=time;
	}
	
	float totalWT=0, totalTAT=0;
	for(int i=0;i<n;i++)
	{
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		totalWT=totalWT+p[i].wt;
		totalTAT=totalTAT+p[i].tat;
	}
	float avgWT=totalWT/n;
	float avgTAT=totalTAT/n;
	printf("\nAverage Waiting time= %.2f",avgWT);
	printf("\nAverage TurnAround time= %.2f",avgTAT);
	
}
void rr_main()
{
	int n,slice;
	printf("Enter number of processes:");
	scanf("%d",&n);
	printf("Enter time slice: ");
	scanf("%d",&slice);
	
	struct process p[n];
	insertp(p,n);
	
	for(int i=0;i<n-1;i++)
		for(int j=0;j<n-1;j++)
			if(p[j].at>p[j+1].at)
			{
				struct process temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
			
	struct process exec[50];
	int x=-1;
	
	int totalBT=0;
	for(int i=0;i<n;i++)
		totalBT+=p[i].bt;
	
	int tim=0, iP=0;
	for(int i=0;i<totalBT;i++)
	{
		tim++;
		while((p[iP].at<=i)&&(iP<n))
		{
			push(p[iP]);
			++iP;
		}
		if(ready[front].bt==0)
		{
			exec[++x]=pop(tim-1);
			tim=1;
		}
		else if(tim>slice)
		{
			tim=1;
			push(ready[front]);
			exec[++x]=pop(slice);

		}
		ready[front].bt--;
		
		if(i==totalBT-1)
			exec[++x]=pop(tim);
	}
	gchart(exec,x+1);
	rr_calc(p,n,exec,x+1);
	table(p,n);
}


int main()
{
	while(1)
	{
		printf("1.FCFS\n");
		printf("2.SJF\n");
		printf("3.Priority\n");
		printf("4.Round Robin\n");
		printf("5.Exit\n");
		printf("Enter choice: ");
		int op;
		scanf("%d",&op);
		switch(op)
		{
		
		case 1:
			fcfs_main();
			break;
		case 2:
			sjf_main();
			break;
		case 3:
			priority_main();
			break;
		case 4:
			rr_main();
			break;
		case 5:
			printf("Exiting...\n");
			exit(0);
		default:
			printf("Invalid entry\n");
			break;
		
		}
		printf("\n\n");
	}
}
