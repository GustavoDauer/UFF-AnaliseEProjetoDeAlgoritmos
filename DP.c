#include <stdio.h>
// see http://stackoverflow.com/a/7943955/7507
int main(int argc, char *argv[]) {
	int bestSoFar = 0;
	int bestNow = 0;
	int bestStartIndexSoFar = -1;
	int bestStopIndexSoFar = -1;
	int bestStartIndexNow = -1;
	int array[] = {3, -1, 5, -6, -9};
	int array_len = sizeof(array)/sizeof(int);
	int i;
	for(i = 0; i < array_len; i++) {
		
		int value = bestNow + array[i];
		
		if(value > 0) {
			if (bestNow == 0) {
				bestStartIndexNow = i;
			}
			
			bestNow = value;
		} else {
			bestNow = 0;
		}
		
		if(bestNow > bestSoFar) {
			bestSoFar = bestNow;
			bestStopIndexSoFar = i;
			bestStartIndexSoFar = bestStartIndexNow;
		}
	}
	
	printf("Best Sum = %d\n", bestSoFar);
	printf("Max Array = [");
	
	for(i = bestStartIndexSoFar; i < bestStopIndexSoFar + 1; i++) {
		printf(" %d", array[i]);
	}
	
	printf(" ]\n");
	
	return 0;
}
