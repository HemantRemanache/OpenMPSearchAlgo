#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#ifdef RAND_MAX 
#undef RAND_MAX
#endif
#ifndef RAND_MAX
#define RAND_MAX 11
#endif

int searchforvalueinmatrixLefttoRight(int arr[][10], int tensdigit, int onesdigit);
int searchforvalueinmatrixToptoBottom(int arr[][10], int tensdigit, int onesdigit);
int searchforvalueinmatrixdiagonally(int arr[][10], int tensdigit, int onesdigit);
int searchforvalueinmatrixcounterdiagonally(int arr[][10], int tensdigit, int onesdigit);

int main()
{
    
    //srand(time(0));
    int arr[10][10];
    int searchkey, tensdigit = 0, onesdigit = 0,count1=0,count2=0,count3=0,count4=0,tid;
    double start , end;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arr[i][j] = rand() % 10;
            printf("%d \t", arr[i][j]);
        }
        printf("\n");
    }
    printf("Enter Value to be searched :");
    //std::cin >> searchkey;
    scanf("%d", &searchkey);

    onesdigit = searchkey % 10;
    tensdigit = searchkey / 10;
    int count = 0;
    double t1,t2;
    //t1=omp_get_wtime();
    start = omp_get_wtime(); 
     
#pragma omp parallel private(tid)
{
	int from,to;
tid=omp_get_thread_num();
int numt=omp_get_num_threads();

    	for (int i = 1; i <= 4 ; i++) {
        if (tid == 0)
        {
          count1=  searchforvalueinmatrixdiagonally(arr, tensdigit, onesdigit);
       }
        else if (tid == 1)
        {
          count2=  searchforvalueinmatrixLefttoRight(arr, tensdigit, onesdigit);
        }
        else if (tid == 2)
        {
           count3= searchforvalueinmatrixToptoBottom(arr, tensdigit, onesdigit);
        }
        else
        {
            count4 = searchforvalueinmatrixcounterdiagonally(arr, tensdigit, onesdigit);
        }        
    }
}
    end = omp_get_wtime();
    count=count1+count2+count3+count4;
    printf("count %d",count);  
    printf("Time Taken for execution : %f seconds ",end-start);
    return 0;
}

int searchforvalueinmatrixLefttoRight(int arr[][10], int tensdigit, int onesdigit)
{
    int searchedLine = 1000;
    int searchcount = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j + 1 < 10; j++)
        {
            if (arr[i][j] == tensdigit && arr[i][j + 1] == onesdigit)
            {
                searchcount++;
            }
        }
    }
    return searchcount;
}

int searchforvalueinmatrixcounterdiagonally(int arr[][10], int tensdigit, int onesdigit)
{
    int searchcount = 0;
    int count = 0;
    
        int i = 0;
        int j = 9;
        while (i < 10)
        {
            int l = i;
            int k = j;
            if (j >= 0)
            {
                for (; (k + 1) < 10 && (l + 1) < 10; k++, l++)
                {
                    if (arr[l][k] == tensdigit && arr[l + 1][k + 1] == onesdigit)
                    {
                        searchcount++;
                    }
                }
            }
            if (j <= 0)
            {
                for (; (k + 1) < 10 && (l + 1) < 10; k++, l++)
                {
                    if (arr[l][k] == tensdigit && arr[l + 1][k + 1] == onesdigit)
                    {
                        searchcount++;
                    }
                }

                i++;
            }
            if (j > 0)
                j--;       
        }
    return searchcount;
}

int searchforvalueinmatrixdiagonally(int arr[][10], int tensdigit, int onesdigit)
{
    int searchedLine = 10000;
    int count = 0;
    int searchcount = 0;
    while (count < 20)
    {
        int i = 0;
        int j = 0;
        while ((i + j) != count)
        {
            if (j < 9)
                j++;
            else if (i < 9)
                i++;
            else
                break;

        }
        if ((i + j) == count)
        {
            for (; (j - 1) > 0 && (i + 1) < 10; i++, j--)
            {
                if (arr[i][j] == tensdigit && arr[i + 1][j - 1] == onesdigit)
                {
                    searchcount++;
                }
            }
        }
        count++;
    }
   
    return searchcount;
}

int searchforvalueinmatrixToptoBottom(int arr[][10], int tensdigit, int onesdigit)
{
    int searchedLine = 1000;
    int searchcount = 0;
    for (int i = 0; i + 1 < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (arr[j][i] == tensdigit && arr[j + 1][i] == onesdigit)
            {
                searchcount++;
            }
        }
    }
    return searchcount;
}


