#include <stdio.h>
#include <stdlib.h>

int average_val (int *iArray[], int size)
{
    int max, min, sum=0, sum2=0, i, tmp;

    max = min = iArray[0];

    for (i=0; i<size; i++){
        if (iArray[i] > max){
            max = iArray[i];
        }

        if (iArray[i] < min){
            min = iArray[i];
        }
        tmp = iArray[i];
		sum2 += iArray[i];	//here is not right !! why???
		sum += tmp;
		//printf("i:%d, iArray[i]:%d, sum:%d \n", i, iArray[i], sum);
    }

    return (sum - max - min)/(size - 2);
}

int main (int argc, char *argv[])
{
	int i, *iArray;
	iArray = malloc (sizeof(int) * (argc-1));
	for (i=1; i<argc; i++){
		iArray[i-1] = atoi(argv[i]);	//ignore argv[0]
	}
	printf("ave:%d \n", average_val(iArray, argc-1));
	
	return 0;	
}