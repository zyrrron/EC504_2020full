#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
 
#define NoOfKeys 10
#define MAX 1000000
static int OpCount = 0;

int findBisection(int key, int *a, int n, int start=0);
int findDictionary(int key, int *a, int n, int start=0);

int main()
{
	char buf[20];
 	FILE *fp;
 	int i=0, n;
 	int a[MAX], keytable[NoOfKeys];
 	if((fp = fopen("Sorted100K.txt","r")) == NULL)
 	{
 		perror("fail to read");
 		exit (1);
 	}
	while(fgets(buf,20,fp) != NULL)
 	{
 		if (i==0) 
		 {
		 	n=atoi(buf);
 			printf("%d \n",n);
		 }
 		else a[i-1]=atoi(buf);
	 	i++; 
 	}

 	for(int k = 0; k < NoOfKeys; k++)
    {
      int key = a[rand()%n];
      OpCount = 0;
      int find_index_bisection = findBisection(key, a, n);
      int  OpCountBisection = OpCount;
      
      OpCount = 0;
      int find_index_dictionary = findDictionary(key, a, n);
      int  OpCountDictionary = OpCount;
      
      printf("%d \n", key);
      printf("bisection: %d vs dictionary: %d", find_index_bisection, find_index_dictionary);
      printf("\n");
      printf("operations: bisection: %d vs dictionary: %d", OpCountBisection, OpCountDictionary);
      printf("\n");
    }
   
 //	findBisection(key, a, n);
 //	findDictionary(key, a, n);
	
	 
  	return 0;
}

int findBisection(int key, int a[], int N, int start)
{
	int index = -1;
	
 	OpCount++;  // counts the number of call to routine
  	if (N==0) return index;
  	else
	{
 		if (a[start+N/2]!=key)
 		{
		 	if (a[start+N/2]>key) 
		 		index = findBisection(key, a, N/2, start);
		 	else 
		 		index = findBisection(key, a, N-N/2-1, start+N/2+1);
 		}
 		else return start+N/2;
  	} 
  	return index;
}

int findDictionary(int key, int *a, int N, int start)
{
  	int index = -1;
   	OpCount++;  // counts the number of call to routine
   	if (N==0) return index;
  	else
	{
		double x = double(key - a[start])/double(a[start+N-1]-a[start]);
		int m = int(start + x * N);
 		if (a[m]!=key)
 		{
		 	if (a[m]>key) 
		 		index = findBisection(key, a, m, start);
		 	else 
		 		index = findBisection(key, a, N-m-1, start+N/2+1);
 		}
 		else return m;
  	}
  	return index;
}