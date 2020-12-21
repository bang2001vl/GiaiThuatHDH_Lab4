#include<stdio.h> 
int pn[10]; 
int arr[10],bur[10],star[10],finish[10],tat[10],wt[10],n; 
int list[10], wList[10], mArr[10], mBur[10], mStart[10], l, wl;

void print(int* A, int length)
{
	printf("\n");
	for(int i = 0; i<length; i++)
	{
		printf("%d || ", A[i]);
	}
}
int GetSmallestIndex(int* arr, int from, int to)
{
	int rs = from;
	for(int i = rs + 1; i<to; i++)
	{
		if(arr[i]<arr[rs]) {rs = i;}
	}
	return rs;
}
void RemoveAt(int* A, int* length, int index)
{
	for(int i = index + 1; i< *length; i++)
	{
		A[i-1] = A[i];
	}
	*length = *length -1;
}
void InsertAt(int* A, int* length, int index, int val)
{
	for(int i = *length; i > index; i--)
	{
		A[i] = A[i-1];
	}
	A[index] = val;
	*length = *length +1;
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
int AddToList(int time)
{
	//printf("\nAdd process up to time = %d", time);
	while(wl > 0 &&(arr[wList[0]] <= time))
	{
		InsertAt(list, &l, l, wList[0]);
		RemoveAt(wList, &wl, 0);
	}
	if(wl == 0) {return -1;}
	int next_add = arr[wList[0]];
	return next_add;
}
int ChooseProcces_RR()
{
	int rs = 0;
	for(int i = 1; i<l; i++)
	{
		if( (mArr[list[i]] < mArr[list[rs]]) )
		{
			rs = i;
		}
	}
	return rs;
}
int Work(int t_from, int t_to)
{
	if(l==0){return (t_to - t_from);}
	int t_Prog;
	int index = ChooseProcces_RR();
	int p = list[index];
	//printf("\nDoing on process : %d", pn[p]);
	
	//if(t_from < mArr[p]){t_from = mArr[p]; printf("Na~~ni ????");}
	
	mStart[p] = t_from;
	if(star[p] == -1) 
	{
		star[p] = mStart[p];
	}
	wt[p] += (mStart[p] - mArr[p]);
	
	
	if(t_to == -1 || (t_to - t_from) >= mBur[p])
	{
		//printf("\nUnlimited Time");
		t_Prog = mBur[p];
		finish[p] = mStart[p] + t_Prog;
		tat[p] = finish[p] - arr[p]; 
		//printf("\nBefore delete: length = %d;", l);
		RemoveAt(list, &l, index);
		//printf("\nAfter delete: length = %d;", l);
		return t_Prog;
	}
	
	t_Prog = t_to - t_from;
	
	mBur[p] -= t_Prog;
	mArr[p] = t_to;
	/*
	RemoveAt(list, &l, index);
	list[l] = p;
	l++;
	*/
	return t_Prog;
}
int interval = 10;
void main() 
{ 
	int totwt=0,tottat=0;  
	printf("Enter the number of processes:"); 
	scanf("%d",&n); 
	
	for(int i=0;i<n;i++) 
	{ 
		printf("Enter the Process Name, Arrival Time & Burst Time:"); 
		scanf("%d%d%d",&pn[i],&arr[i],&bur[i]);
	} 
	SortByArr();
	for(int i=0;i<n;i++) 
	{ 
		mArr[i] = arr[i]; 
		mBur[i] = bur[i];
		star[i] = -1;
		wt[i] = 0;
		wList[i] = i;
	}
	l = 0;
	wl = n;
	mStart[0] = mArr[list[0]];
	star[list[0]] = mStart[0];
	
	int t_from = 0;
	int t_to;
	int nxtAdd;
	int t_add = arr[wList[0]];
	nxtAdd = AddToList(t_add);
	
	t_from = t_add;
	t_to = t_from + interval;
	while(l > 0)
	{ 
	/*
	printf("\n Wait List: ");
	print(wList, wl);
	printf("\n List: ");
	print(list, l);
	
	printf("\nFrom time: %d", t_from);
	printf("\nTo time: %d", t_to);
	*/
		int tmp = Work(t_from, t_to);
		
		t_from += tmp;
		t_to  = t_from + interval;
		if(t_from >= nxtAdd && t_to != -1)
		{
			if(wl > 0)
			{ 
				t_add = t_from;
				nxtAdd = AddToList(t_add);
			}
			else{}
		}
		/*
		char cc = 'f';
		scanf("%c", &cc);
		if(cc == 'q'){return;}
		*/
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
// 4 1 0 7 2 2 4 3 4 1 4 5 4
// 5 1 0 10 2 2 29 3 4 3 4 5 7 5 7 12
// 6 0 0 250 1 50 170 2 130 75 3 190 100 4 210 130 5 350 50

