//compile using mpicc SearchTechniquesUsingMPI.c -o SearchTechniquesUsingMPI
//run using mpirun -np 8 hello
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "mpi.h"
#ifdef RAND_MAX 
#undef RAND_MAX
#endif
#ifndef RAND_MAX
#define RAND_MAX 11
#endif

int searchforvalueinmatrixLefttoRight(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixToptoBottom(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixdiagonally(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixcounterdiagonally(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixRighttoLeft(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixBottomtoTop(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixdiagonallybottomtotopleft(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int searchforvalueinmatrixdiagonallybottomtotopright(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns);
int main(int argc, char** argv)
{

	//srand(time(0));

	int searchkey, tensdigit = 0, onesdigit = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, tid;
	int count5 = 0, count6 = 0, count7 = 0, count8 = 0;
	double start, end;
	int ierr;
	int rows, columns;
	printf("Enter the number of rows :");
	scanf("%d", &rows);
	printf("Enter the number of columns :");
	scanf("%d", &columns);

	int arr[1000][1000];
	///////////////////////////////
	//Filling the rows * columns matrix 
	//////////////////////////////
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			arr[i][j] = rand() % 10;
			printf("%d \t", arr[i][j]);
		}
		printf("\n");
	}

	// Search the 2 digit number you need to search in the matrix 
	printf("Enter Value to be searched :");
	scanf("%d", &searchkey);

	onesdigit = searchkey % 10;
	tensdigit = searchkey / 10;
	if ((searchkey / 100) > 0)
	{
		printf("Please Enter proper value to be searched ");
		return 0;
	}
	int count = 0;
	double t1, t2;
	start = MPI_Wtime();
	ierr = MPI_Init(&argc, &argv);
	//Parallel code starts from here
		ierr = MPI_Comm_rank(MPI_COMM_WORLD, &tid);
		if (tid == 0) //1st thread will be executing the below method
		{
			count1 = searchforvalueinmatrixdiagonally(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 1)//2nd thread will be executing the below method
		{
			count2 = searchforvalueinmatrixLefttoRight(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 2)//3rd thread will be executing the below method
		{
			count3 = searchforvalueinmatrixToptoBottom(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 3)////4th thread will be executing the below method
		{
			count4 = searchforvalueinmatrixcounterdiagonally(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 4) //5th thread will be executing the below method
		{
			count5 = searchforvalueinmatrixdiagonally(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 5)//6th thread will be executing the below method
		{
			count6 = searchforvalueinmatrixLefttoRight(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 6)//7th thread will be executing the below method
		{
			count7 = searchforvalueinmatrixToptoBottom(arr, tensdigit, onesdigit, rows, columns);
		}
		else if (tid == 7)//8th thread will be executing the below method
		{
			count8 = searchforvalueinmatrixcounterdiagonally(arr, tensdigit, onesdigit, rows, columns);
		}
		ierr = MPI_Finalize();
	end = MPI_Wtime();  //Get current time after execution 

	printf("%d * %d matrix ", rows, columns);
	count = count1 + count2 + count3 + count4 + count5 + count6 + count7 + count8;// adding the total number of counts we got after implementing searching agorithms 
	printf("Number to find : %d \n", searchkey);
	printf("Work took : %f seconds \n", end - start);
	printf("The count of number found : %d", count);

}



/****************************************************************
Search for 2 digit number in a matrix using diagonal approach

Description : The algo checks if the current number is the tens place digit number
from left to right starting from the very first row and then going up and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/

int searchforvalueinmatrixdiagonallybottomtotopright(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	int i = 0, j = 0;
	while (i < rows && j < rows)
	{
		for (int m = i, n = j; (m - 1) >= 0 && (n + 1) <= columns - 1; m--, n++)
		{
			if (arr[m][n] == tensdigit && arr[m - 1][n + 1] == onesdigit)
			{
				searchcount++;
			}
		}
		if (i <= rows - 2)
			i++;
		else
			j++;
	}

	return searchcount;
}
/****************************************************************
Search for 2 digit number in a matrix using diagonally left to top right approach

Description : The algo checks if the current number is the tens place digit number
from left to right starting from the very first row and then going up and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixdiagonallybottomtotopleft(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	int i = rows - 1, j = 0;
	while (i > 0 || j <= (columns - 2))
	{
		for (int m = i, n = j; (m - 1) >= 0 && (n - 1) >= 0; m--, n--)
		{
			if (arr[m][n] == tensdigit && arr[m - 1][n - 1] == onesdigit)
			{
				searchcount++;
			}
		}
		if (j <= (columns - 2))
			j++;
		else
			i--;
	}

	return searchcount;
}

/****************************************************************
Search for 2 digit number in a matrix using buttom to top approach

Description : The algo checks if the current number is the tens place digit number
from bottom to top starting from the very first row and then going down and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixBottomtoTop(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = columns - 1; (j - 1) > 0; j--)
		{
			if (arr[j][i] == tensdigit && arr[j - 1][i] == onesdigit)
			{
				searchcount++;
			}
		}
	}
	return searchcount;
}
/****************************************************************
Search for 2 digit number in a matrix using right to left approach

Description : The algo checks if the current number is the tens place digit number
from right to left starting from the very first row and then going down and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixRighttoLeft(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = columns - 1; (j - 1) > 0; j--)
		{
			if (arr[i][j] == tensdigit && arr[i][j - 1] == onesdigit)
			{
				searchcount++;
			}
		}
	}
	return searchcount;
}

/****************************************************************
Search for 2 digit number in a matrix using left to right approach

Description : The algo checks if the current number is the tens place digit number
from left to right starting from the very first row and then going down and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixLefttoRight(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j + 1 < columns; j++)
		{
			if (arr[i][j] == tensdigit && arr[i][j + 1] == onesdigit)
			{
				searchcount++;
			}
		}
	}
	return searchcount;
}

/****************************************************************
Search for 2 digit number in a matrix using counter diagonal approach

Description : The algo first sets the primary columns which can be used as a rference for starting the search
EG : if I want to search cell (7,8).  the first cell we will need here is (1,2) adding +1 to both rows and columns
will help us the column for searching
if the current number is the tens place digit number and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixcounterdiagonally(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	int i = 0, j = 0;
	while (j <= 8 || i < 10)
	{
		for (int m = i, n = j; (m + 1) <= 9 && (n - 1) >= 0; m++, n--)
		{
			if (arr[m][n] == tensdigit && arr[m + 1][n - 1] == onesdigit)
			{
				searchcount++;
			}
		}
		if (j <= 8)
			j++;
		else
			i++;
	}
	return searchcount;
}
/****************************************************************
Search for 2 digit number in a matrix using  diagonal approach

Description : The algo first sets the primary columns which can be used as a rference for starting the search
EG : if I want to search cell (2,3).  the first cell we will need here is (0,5) adding +1 to  rows and -1 to columns
will help us the column for searching
if the current number is the tens place digit number and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixdiagonally(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	int i = rows - 1, j = 0;
	while (i >= 1 || j < columns)
	{
		for (int m = i, n = j; (m + 1) <= (rows - 1) && (n + 1) <= (columns - 1); m++, n++)
		{
			if (arr[m][n] == tensdigit && arr[m + 1][n + 1] == onesdigit)
			{
				searchcount++;
			}
		}
		if (i >= 1)
			i--;
		else
			j++;

	}

	return searchcount;
}

/****************************************************************
Search for 2 digit number in a matrix using top to bottom approach

Description : The algo checks if the current number is the tens place digit number
from top to bottom starting from the very first row and then going down and if yes,
it goes on for checking if the next number is the ones digit , If yes then the search count is incremented by 1

****************************************************************/
int searchforvalueinmatrixToptoBottom(int arr[][1000], int tensdigit, int onesdigit, int rows, int columns)
{
	int searchcount = 0;
	for (int i = 0; (i) < 10; i++)
	{
		for (int j = 0; (j + 1) < 10; j++)
		{
			if (arr[j][i] == tensdigit && arr[j + 1][i] == onesdigit)
			{
				searchcount++;
			}
		}
	}
	return searchcount;
}

