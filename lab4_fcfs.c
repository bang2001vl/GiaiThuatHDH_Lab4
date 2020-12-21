#include<stdio.h> 

int pn[10]; 
int arr[10],bur[10],star[10],finish[10],tat[10],wt[10],i,n; 
int GetSmallestIndex(int* arr, int from, int to)
{
	int rs = from;
	for(int i = rs + 1; i<to; i++)
	{
		if(arr[i]<arr[rs]) {rs = i;}
		//if(arr[i]==arr[rs] && bur[i]<bur[rs]) {rs = i;}
	}
	return rs;
}
void Swap(int* arr1, int i1, int* arr2, int i2)
{
	int temp = arr1[i1];
	arr1[i1] = arr2[i2];
	arr2[i2] = temp;
}
void mSwap(int a, int b)
{
	if(a==b){return;}
	Swap(arr, a, arr, b);
	Swap(pn, a, pn, b);
	Swap(bur, a, bur, b);
}
void SortByArr()
{
	for(int i = 0; i< n; i++)
	{
		int index = GetSmallestIndex(arr, i, n);
		mSwap(i, index);
	}
}
void main() 
{ 
	int totwt=0,tottat=0;  
	printf("Enter the number of processes:"); 
	scanf("%d",&n); 
	for(i=0;i<n;i++) 
	{ 
		printf("Enter the Process Name, Arrival Time & Burst Time:"); 
		scanf("%d%d%d",&pn[i],&arr[i],&bur[i]); 
	} 
	SortByArr();
	for(i=0;i<n;i++) 
	{ 
		if(i==0) 
		{ 
			star[i]=arr[i]; 
			wt[i]=star[i]-arr[i]; 
			finish[i]=star[i]+bur[i]; 
			tat[i]=finish[i]-arr[i]; 
		} 
		else 
		{ 
			star[i]=finish[i-1]; 
			wt[i]=star[i]-arr[i]; 
			finish[i]=star[i]+bur[i]; 
			tat[i]=finish[i]-arr[i]; 
		} 
	} 
	printf("\nPName     Arrtime     Burtime    Start     TAT   Finish");
	int totalRes = 0;
	totwt = 0;
	tottat = 0;
	for(int i=0;i<n;i++) 
	{ 
		printf("\n%d\t%6d\t\t%6d\t%6d\t%6d\t%6d",pn[i],arr[i],bur[i],star[i],tat[i],finish[i]); 
		totwt+=wt[i]; 
		tottat+=tat[i]; 
		totalRes += (star[i] - arr[i]);
	} 
	
	printf("\nAvarage Waitting Time = %.2f", 1.0f*totwt/n);
	printf("\nAvarage Turnaround Time = %.2f", 1.0f*tottat/n);
	printf("\nAvarage Response Time = %.2f", 1.0f*totalRes/n);
	printf("\n");
}
