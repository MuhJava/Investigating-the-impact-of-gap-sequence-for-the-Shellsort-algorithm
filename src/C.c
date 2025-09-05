#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mt19937ar.h"

int incrementList[40];
int numberOfSwaps = 0;
long long numberOfComparisons = 0;
double totalTime = 0;
long long totalComparisons = 0;
long long overallComparisons = 0;
long long overallSwaps = 0;
long long totalSwaps = 0;
unsigned int seeds[5];
int k;
int kPrinted = 0;
int iterationCounter = 0;
int bumpIncUpOrDown = 1;
int incrementBumper = 0;
double percentageChange = 0;
/*
ciura = np.array([1, 4, 10, 23, 57, 132, 301, 701])
tokuda = np.array([1, 4, 9, 20, 46, 103, 233, 525])
knuth = np.array([1, 4, 13, 40, 121, 364, 1093, 3280])
skean = np.array([1,4,10,27,72,187,488,1280])
*/

int initialiseK(int n) {
    k = 1;
    while ((((pow(3, k) - 1) / 2)) < n/3) {
        k++;
    }
    if (kPrinted == 0) {
    	printf("INITIAL K: %d", k-1);
    	kPrinted = 1;
    }
    return k - 1;
}

void printArray(unsigned int arr[], int size) {
    for (unsigned int i = 0; i < size; i++) {
        printf("%u\n", arr[i]);
    }
    printf("\n");
    fflush(stdout);
}

void shellSort(unsigned int arr[], int n) {

	//
	int increments[] = {1, 3, 9, 30, 101, 374, 1588, 5783, 11111, 2343, 7171, 13438, 90000};
	int incrementIndex;
	for (int inc = 0; inc < 13; inc++) {
		if (increments[inc] >= n) {
			incrementIndex = inc - 1;
			break;
		}
	}

	int increment = increments[incrementIndex];
	//

    // SHELL int increment = floor(n / 2);
	// KNUTH int increment = ((pow(3, k) - 1) / 2);
	// SEDGEWICK int increment = pow(4, k) + 3 * pow(2, k - 1) + 1;
	// TOKUDA int increment = ceil((9 * pow(9.0 / 4, k - 1) - 4) / 5);
	// LEE int increment = ceil((pow(2.243609061420001, k) - 1) / 1.243609061420001);
	// SKEAN int increment = floor(4.0816 * pow(8.5714, k / 2.2449));
	// XPSEDGE int increment = (pow(4, k) + 3 * pow(2, k - 1))*k + 1;
    int incrementCount = 0;

    int scaledIncrementBumper = 0;
/*
	if (iterationCounter == 100) {
		if ((incrementBumper + 1 > increment*0.9) && bumpIncUpOrDown == 1) {
			bumpIncUpOrDown = 0;
		}
	    if ((incrementBumper - 1 < increment*-0.9) && bumpIncUpOrDown == 0) {
				bumpIncUpOrDown = 1;
		}
	    if (bumpIncUpOrDown == 1) {
	    	incrementBumper = incrementBumper + 1;
	    	}
	    if (bumpIncUpOrDown == 0) {
	    		incrementBumper = incrementBumper - 1;
	    	}
	    iterationCounter = 0;
}
iterationCounter++;
percentageChange = (double) incrementBumper / increment;
increment = increment + incrementBumper;
*/


    while (increment > 0) {
        for (int i = increment; i < n; i++) {
        	unsigned int temp = arr[i];
        	unsigned int j = i;

            while (j >= increment && arr[j - increment] > temp) {
            	numberOfComparisons++;
                arr[j] = arr[j - increment];
                numberOfSwaps++;
                j -= increment;
            }
            numberOfComparisons++;
            arr[j] = temp;
        }
        // printf("Increment is: %d", increment);

        if (incrementCount < 40) {
            incrementList[incrementCount] = increment;
        }
            incrementCount++;
        if (increment == 2) {
            increment = 1;
        } else if (increment == 1) {
        	break;
        } else {
        	// CHECK K printf("K IS %d INCREMENT IS %d ", k, increment);
        	k--;
        	//
        	incrementIndex--;
        	increment = increments[incrementIndex];
        	//

        	// SHELL increment = floor(increment / 2);
        	// KNUTH increment = ((pow(3, k) - 1) / 2)*1.1;
        	// SEDGEWICK increment = pow(4, k) + 3 * pow(2, k - 1) + 1; if (k == 0) {increment = 1;}
        	// TOKUDA increment = ceil((9 * pow(9.0 / 4, k - 1) - 4) / 5);
        	// LEE increment = ceil((pow(2.243609061420001, k) - 1) / 1.243609061420001);
        	// SKEAN increment = floor(4.0816 * pow(8.5714, k / 2.2449));
        	// XPSEDGE increment = (pow(4, k) + 3 * pow(2, k - 1))*k + 1;

 /*
        	if (k > 3) {
        	scaledIncrementBumper = increment * percentageChange;
        	increment = increment + scaledIncrementBumper;
        	}
     */
        }
    }
}

int main() {
	clock_t sort_start, sort_end, start, end;
	double cpu_time_used;
	int arrayLengths[] = {30000,35000,40000,45000,50000,55000,60000,65000};

    // Initialize the generator with a seed
    init_genrand(5);

    // Generate seeds
    for (int i = 0; i < 5; i++) {
        seeds[i] = genrand_int32();
    }

    FILE *file = fopen("RETESTresultsSEDGEWICK_78N_281N_100runs5S_Cont.csv", "w");
    if (file == NULL) {
    	printf("Error opening file!\n");
    	return 1;
    }
    // WITH PERCENT fprintf(file, "Array length,Average Comparisons,Average Swaps,Percentage Change\n");
    //
    //
    fprintf(file, "Array length,Average Comparisons,Average Swaps\n");




    // Seed the random number generator with the value 2
    // Generate 10 random numbers and print them
    /*
    for (int i = 0; i < 10; i++) {
        printf("%d\n", rand());
    }
    */
    // USING FIXED ARRAY LENGTHS
//for (int a = 0; a<8; a++) {
//	int N = arrayLengths[a];
    // USING INCREMENTING ARRAY LENGTH
for (int N = 78; N<282; N++) {
    overallComparisons = 0;
    overallSwaps = 0;
    for (int b = 0; b<5; b++) {
        	init_genrand(seeds[b]);
        	unsigned int *V = (unsigned int *)malloc(N * sizeof(unsigned int));
    if (V == NULL) {
        printf("Memory allocation failed\n");
        //fprintf(file, "Memory allocation failed\n");
        //fclose(file);
        return 1;
    }

    totalComparisons = 0;
    totalSwaps = 0;
    totalTime = 0;

    for (int i = 0; i < N; i++) {
              V[i] = genrand_int32();
          }

    start = clock();
    // printArray(V, N);
    for (int i = 0; i<100; i++) {
      cpu_time_used = 0;
      numberOfSwaps = 0;
      numberOfComparisons = 0;
      sort_start = clock();
      k = initialiseK(N);
      shellSort(V, N);
      // printf("\nNEW ARRAY\n");
       // printArray(V, N);
      sort_end = clock();
      cpu_time_used = ((double) (sort_end - sort_start));
      totalComparisons = totalComparisons + numberOfComparisons;
      totalSwaps = totalSwaps + numberOfSwaps;
      totalTime = totalTime + cpu_time_used;

      free(V);
      V = (unsigned int *)malloc(N * sizeof(unsigned int));
          if (V == NULL) {
              printf("Memory allocation failed\n");
              return 1;
          }
      // Generate the random array
      for (int i = 0; i < N; i++) {
          V[i] = genrand_int32();
      }

    }

    overallComparisons = overallComparisons + totalComparisons;
    overallSwaps = overallSwaps + totalSwaps;

    end = clock();

    double runTime = (end - start) /CLOCKS_PER_SEC;
    totalTime = totalTime / CLOCKS_PER_SEC;
    printf("\n Time to execute: %f minutes.\n", totalTime/60);

    // printf("\nShell sort executed in %f seconds.\n", cpu_time_used);
    // FOR CHECKING SINGLE SEED ARRAYS printf("**************************SEED %d***************************", seeds[b]);
    // FOR CHECKING SINGLE SEED ARRAYS printf("\n Average time for 10,000 runs: %f seconds.\n", totalTime / 10000);
    // FOR CHECKING SINGLE SEED ARRAYS printf("\n Average comparisons for 10,000 runs: %lld comparisons.\n", totalComparisons / 10000);
    // FOR CHECKING SINGLE SEED ARRAYS printf("\n Average swaps for 10,000 runs: %lld swaps.\n", totalSwaps / 10000);
    // start = clock();
    // printf("Sorted array:\n");
    // printArray(V, N);
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("Print executed in %f seconds.\n", cpu_time_used);
    printf("Increments: ");
    for (int i = 0; i<40; i++) {
    	printf("%d ", incrementList[i]);
    }
    /*
    printf("\nShell sort executed in %f seconds.", cpu_time_used);
    printf("\nNumber of swaps performed: %d", numberOfSwaps);
    printf("\nNumber of comparisons performed: %lld", numberOfComparisons);
    */
    // WRITE TO FILE
    // Wrong one? for individual seeds not for overall per N fprintf(file, "Seed: %u, Comparisons: %lld, Shifts: %lld\n", seeds[b], (totalComparisons / 10), (totalSwaps / 10));

    free(V);
    }
    printf("\n\n****Array length: %d ***\n\n", N);

    // printf("\n Overall comparisons for 20 runs of 10,000 runs: %lld comparisons.****\n\n", overallComparisons / 50);

    // PRINT TO CONSOLE printf("N: %d, Comparisons: %lld, Shifts: %lld\n", N, (overallComparisons / 500), (overallSwaps / 500));
    // WRITE TO FILE
    // WITH PERCENT fprintf(file, "N: %d, Comparisons: %lld, Shifts: %lld, Percentage change: %lf%%\n", N, (overallComparisons / 500), (overallSwaps / 500), percentageChange);
    //
    //
    fprintf(file, "N: %d, Comparisons: %lld, Shifts: %lld\n", N, (overallComparisons / 500), (overallSwaps / 500));

    kPrinted = 0;
}
    // CLOSE FILE
    fclose(file);
    return 0;
}
