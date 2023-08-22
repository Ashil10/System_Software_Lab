#include <stdio.h>
#include <stdbool.h>
int safeseq[100],seqinx;
bool flag,change;
bool bankers(int m,int n,int allocation[n][m],int need[n][m],int work[m],bool array[n]){
    int copyofwork[m]; for(int i=0;i<m;i++) { copyofwork[i]=work[i]; } //creating a copy of the work to preserve the original content of work
    change=true;
    while(change){
        change=false;
        for(int i=0;i<n;i++){
            if(array[i]!=true){
                flag=true;
                for(int j=0;j<m;j++){
                    if(need[i][j]>work[j]){
                        flag=false;
                        break;
                    }
                }
                if(flag==true){
                    printf("\n\tSuccessfully executed P%d",i);
                    change=true;
                    seqinx++;
                    safeseq[seqinx]=i;
                    array[i]=true;
                    for(int j=0;j<m;j++)
                        work[j]+=allocation[i][j];
                }
                else
                    printf("\n\tProcess P%d has to wait...",i);
            }
        }
    }
    flag=true;
    for(int i=0;i<n;i++){
        if(array[i]==false){
            flag=false;
            break;
        }
    }
    for(int i=0;i<m;i++) { work[i]=copyofwork[i]; } //storing back the original values into work array
    return flag;
}
void main(){
    while(true){
        int choice;
        printf("\n\t0.EXIT  1.BANKERS SAFETY ALGO   2.BANKERS RESOURCE REQUEST ALGO\nEnter your choice: ");
        scanf("%d",&choice);
        if(choice==0)
            break;
        int m,n;
        seqinx=-1;
        printf("Enter the number of processes: ");
        scanf("%d",&n);
        printf("\nEnter the number of resource types: ");
        scanf("%d",&m);
        int max[n][m],allocation[n][m],need[n][m],available[m],work[m];
        bool array[n];
        printf("\nEnter the MAX matrix: ");
        for(int i=0;i<n;i++){
            array[i]=false;
            for (int j=0;j<m;j++)
                scanf("%d",&max[i][j]);
        }
        printf("\nEnter the ALLOCATION matrix: ");
        for(int i=0;i<n;i++){
            for (int j=0;j<m;j++){
                scanf("%d",&allocation[i][j]);
                need[i][j]=max[i][j]-allocation[i][j];
            }
        }
        printf("\nEnter the AVAILABLE vector: ");
        for(int i=0;i<m;i++){
            scanf("%d",&available[i]);
            work[i]=available[i];       //available array redundant
        }
        if(choice==1){
            if(bankers(m,n,allocation,need,work,array)){
                printf("\nThe system is in SAFE STATE..\nThe SAFE SEQUENCE is: ");
                for(int i=0;i<=seqinx;i++)
                    printf(" P%d",safeseq[i]);
            }
            else
                printf("\nThe system is in UNSAFE STATE");
        }
        else if(choice==2){
            int pid,request[m];
            printf("\nEnter the process id which is requesting the resource: ");
            scanf("%d",&pid);
            printf("\nEnter the request vector: ");
            for(int i=0;i<m;i++)
                scanf("%d",&request[i]);
            flag=true;
            for(int j=0;j<m;j++){
                if(request[j]>need[pid][j]){
                    flag=false;
                    printf("\nThe request made is INVALID !");
                    break;
                }
            }
            if(flag==true){
                for(int j=0;j<m;j++){
                    if(request[j]>work[j]){
                        flag=false;
                        printf("\nThe requested number of resources aren't avalable! The request has to wait");
                        break;
                    }
                }
                if(flag==true){
                    for(int i=0;i<m;i++){
                        work[i]-=request[i];
                        allocation[pid][i]+=request[i];
                        need[pid][i]-=request[i];
                    }
                    if(bankers(m,n,allocation,need,work,array))
                        printf("\nRequest is immediately GRANTED");
                    else{
                        printf("\nRequest CANNOT be granted immediately according to resource request algorithm..");
                        for(int i=0;i<m;i++){
                            work[i]+=request[i];
                            allocation[pid][i]-=request[i];
                            need[pid][i]+=request[i];
                        }
                    }
                }
            }
        }
    }
}
