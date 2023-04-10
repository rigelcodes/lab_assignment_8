#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void heapify(int arr[], int n, int x)
{
	// initalize variables 
    int high = x;
 
    int l = 2 * x + 1;
    int r = 2 * x + 2; 
 
    // compare left child to root (1)
    if (l < n && arr[l] > arr[high])
	{
		// update left child IF greater than the current high val
        high = l;
	}

    // compare right child to root (2)
    if (r < n && arr[r] > arr[high])
	{
		// update right child IF greater than the current high val
        high = r;
	}

	// in place in the case the root is not the value of high
    if (high != x) 
	{
		int temp = arr[x];
		arr[x] = arr[high];
		arr[high] = temp;

        heapify(arr, n, high);
    }
}
 
void heapSort(int arr[], int n)
{
 
    // max heap implementation
    for (int x = n / 2 - 1; x >= 0; x--)
	{
        heapify(arr, n, x);
	}

    for (int x = n - 1; x >= 0; x--) 
	{
		
		int temp = arr[0];
		arr[0] = arr[x];
		arr[x] = temp;

        heapify(arr, x, 0);
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// allocate memory for the left and right side
	int *L = (int*) malloc(n1*sizeof(int));
	int *R = (int*) malloc(n2*sizeof(int));

	// traverse through n1 and n2
	for(i = 0; i < n1; i++)
	{
		L[i] = pData[l + i];
	}
	for(j = 0; j < n2; j++)
	{
		R[j] = pData[m + 1 + j];
	}

	// set variables equal to 0
	i = 0;
	j = 0;
	k = l;

	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			pData[k] = L[i];
			i++;
		}
		else
		{
			pData[k] = R[j];
			j++;
		}
		k++;
	}	
	while(i < n1)
	{
		pData[k] = L[i];
		i++;
		k++;
	}
	while(j < n2)
	{
		pData[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}
void mergeSort(int pData[], int l, int r)
{
    if (l < r)
	{
		int m  = (l + r) / 2;

		// send it through recursively
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);
		merge(pData, l, m, r);

        extraMemoryAllocated += (r - l + 1) * sizeof(int);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		if(i >= dataSz)
		{
			printf("\n\n");
			return;
		}
		
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}

