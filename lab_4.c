 
#include<stdio.h>
#include <stdlib.h>

int checkfault(int fsize,int need,int f[100])
{
for (int i=0;i<fsize;i++)
{
if(f[i]==-1){
	f[i]=need;
	return 2;
	}
if(need==f[i])
	return 0;

}
return 1;
}
void fifo(int n,int ref[100]){
int framesize,frames[100];
printf("enter the frame size:");
scanf("%d",&framesize);
for(int i=0;i<framesize;i++)
{
frames[i]=-1;
}
printf("\n\nFIFO PAGEREPLACEMENT \n");
printf("\tpage\t\tframes");
int outend=0,fault,nofault=0;
for(int i=0;i<n;i++){
fault=checkfault(framesize,ref[i],frames);
if(fault==1){
frames[outend]=ref[i];
outend=(outend+1)%framesize;
}
printf("\n\t%d\t\t",ref[i]);
for(int j=0;j<framesize;j++){
if(frames[j]!=-1);
printf("%d",frames[j]);
printf("\t");
}
if(fault){
nofault++;
printf("PF");
}
}
printf("\nNO OF PAGE FAULTS = %d \n",nofault);
}
void opt(int n,int ref[100]){
int framesize,frames[100],used[100];
printf("enter the framedize: ");
scanf("%d",&framesize);
for(int i=0;i<framesize;i++){
frames[i]=-1;
used[i]=-1;
}
printf("\n\nOPT PAGE REPLACEMENT \n");
printf("\t PAGE \t\tFRAMES");
int fault,nofault=0;
for(int i=0;i<n;i++){
fault =checkfault(framesize,ref[i],frames);
if(fault==1){
	for(int j=0;j<framesize;j++)
	for(int k=i;k<n;k++){
		used[j]=100;
		if(frames[j]==ref[k]){
			used[j]=k-i;
			break;
}
}
int max=0,optind;
for(int j=0;j<framesize;j++){
if(used[j]>max){
max=used[j];
optind=j;
}
}
frames[optind]=ref[i];
}
printf("\n\t %d \t \t",ref[i]);
for(int j=0;j<framesize;j++){
if(frames[j]!=-1);
printf("%d",frames[j]);
printf("\t");
}
if(fault){
nofault++;
printf("PF");
}
}
printf("\n NO OF PAGE FAULTS = %d \n",nofault);
}
void lru(int n,int ref[100]){
int framesize,frames[100],used[100];
printf("enter the frame size :");
scanf("%d",&framesize);
for(int i=0;i<framesize;i++){
frames[i]=-1;
used[i]=-1;
}
printf("\n\nLRU PAGE REPLACEMENT \n");
printf("\t PAGE \t\tFRAMES");
int fault,nofault=0;
for(int i=0;i<n;i++){
fault =checkfault(framesize,ref[i],frames);
if(fault==1){
	for(int j=0;j<framesize;j++)
	for(int k=i;k>=0;k--){
		if(frames[j]==ref[k]){
			used[j]=i-k;
			break;
}
}
int max=0,lruind;
for(int j=0;j<framesize;j++){
if(used[j]>max){
max=used[j];
lruind=j;
}
}
frames[lruind]=ref[i];
}
printf("\n\t %d \t \t",ref[i]);
for(int j=0;j<framesize;j++){
if(frames[j]!=-1);
printf("%d",frames[j]);
printf("\t");
}
if(fault){
nofault++;
printf("PF");
}
}
printf("\n NO OF PAGE FAULTS = %d \n",nofault);
}

void main(){
int n,refstr[100],temp[100];
printf("enter the no of terms in reference string :");
scanf("%d",&n);
printf("enter the reference string :");
for(int i=0;i<n;i++){
scanf("%d",&refstr[i]);
}
int choice;
do{
for(int i=0;i<n;i++){
temp[i]=refstr[i];
}
printf("\nMENU \n1.FIFO\n2.OPT\n3.LRU\n4.EXIT\n");
printf("\nenter the choice\n");
scanf("%d",&choice);
switch(choice){
case 1:fifo(n,temp);
		break;
case 2:opt(n,temp);
		break;
case 3:lru(n,temp);
		break;
case 4:exit(0);
}
}
while(choice!=4);
}
