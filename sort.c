#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define TOTALELEMENTS (8*4)
#define HALF (8*2)
#define CHUNKSIZE 8
#define THREAD_COUNT 4

unsigned long long *NumbersO, *NumbersQ, *NumbersA, *NumbersB;

pthread_mutex_t NextChunkToSortMutex = PTHREAD_MUTEX_INITIALIZER;
int NextChunkToSort = 0;

pthread_mutex_t NextChunkToMergeMutex = PTHREAD_MUTEX_INITIALIZER;
int NextChunkToMerge = 0;
int CurrentChunkSize = CHUNKSIZE;

void arycpy(unsigned long long *array1, const unsigned long long *array2, int size) {
    memcpy(array1, array2, size * sizeof(unsigned long long));
}

void create(unsigned long long *NumbersO) {
    FILE *file = fopen("P1random.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TOTALELEMENTS; ++i) {
    
        if (fscanf(file, "%d", &NumbersO[i]) != 1) {
            fprintf(stderr, "Error reading from file\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}


int compare(const void *a, const void *b) {
    if (*(unsigned long long *)a < *(unsigned long long *)b) return -1;
    if (*(unsigned long long *)a > *(unsigned long long *)b) return 1;
    return 0;
}


int arycmp(const unsigned long long *array1, const unsigned long long *array2, int size) {
    for (int i = 0; i < size; i++) {
        if (array1[i] != array2[i]) {
            printf("Arrays do not match. Entry %d mismatch:\n", i);
            printf("Ary1[%d] = %llu\n", i, array1[i]);
            printf("Ary2[%d] = %llu\n", i, array2[i]);
            return 0;  // Arrays do not match
        }
    }
    printf("Arrays match!!!\n");
    return 1;  // Arrays match
}

void bsort(unsigned long long *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                unsigned long long temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(const char *label, unsigned long long *arr, int n) {
    printf("%s: ", label);
    for (int i = 0; i < n; ++i) {
        printf("%llu ", arr[i]);
    }
    printf("\n");
}

// Function to merge two chunks into a destination chunk
void merge(const unsigned long long *source1, const unsigned long long *source2, int size, unsigned long long *destination) {
    int i = 0, j = 0, k = 0;

    // Merge elements from source1 and source2 into the destination
    while (i < size && j < size) {
        if (source1[i] < source2[j]) {
            destination[k] = source1[i];
            i++;
        } else {
            destination[k] = source2[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements from source1, if any
    while (i < size) {
        destination[k] = source1[i];
        i++;
        k++;
    }

    // Copy remaining elements from source2, if any
    while (j < size) {
        destination[k] = source2[j];
        j++;
        k++;
    }
}

// Function to merge chunks in increasing sizes using multi-threading
// Function to merge chunks in increasing sizes using multi-threading
void *mergeChunks(void *arg) {
    int threadId = *((int *)arg);

    while (1) {
        // Lock mutex to safely access NextChunkToMerge and CurrentChunkSize
        pthread_mutex_lock(&NextChunkToMergeMutex);
        int chunkToMerge1 = NextChunkToMerge;
        NextChunkToMerge++;
        int chunkToMerge2 = NextChunkToMerge;
        NextChunkToMerge++;
        int currentSize = CurrentChunkSize;
        //pthread_mutex_unlock(&NextChunkToMergeMutex);

        // Calculate the start indices for the chunks to be merged
        int startIdx1 = chunkToMerge1 * currentSize;
        int startIdx2 = chunkToMerge2 * currentSize;

        // Calculate the last chunk to merge
        int lastChunk = TOTALELEMENTS / (2 * CurrentChunkSize);

        // Check if NextChunkToMerge has reached the last chunk to merge
        if (chunkToMerge1 >= lastChunk) {
            pthread_mutex_unlock(&NextChunkToMergeMutex);
            break;
        }

        // Update NextChunkToMerge for the next thread
        NextChunkToMerge++;

        // Unlock mutex before performing the merge
        pthread_mutex_unlock(&NextChunkToMergeMutex);

        // Perform merge on the chunks assigned to this thread
        merge(
            NumbersA + startIdx1,
            NumbersA + startIdx2,
            currentSize,
            NumbersB + chunkToMerge1 * (2 * currentSize)
        );

        // Print the chunk numbers, thread ID, and size to indicate progress
        printf("Thread %d merged chunk %d and %d (size %d)\n", threadId, chunkToMerge1, chunkToMerge2, 2 * CurrentChunkSize);

        if (NextChunkToMerge == lastChunk && TOTALELEMENTS % (2 * CurrentChunkSize) != 0) {
            // Copy the remaining chunk to NumbersB
            int remainingStartIdx = lastChunk * 2 * CurrentChunkSize;
            int remainingSize = TOTALELEMENTS - remainingStartIdx;
            arycpy(NumbersB + remainingStartIdx, NumbersA + remainingStartIdx, remainingSize);
            printf("Thread %d copied remaining chunk (size %d) to NumbersB\n", threadId, remainingSize);
        }
    }
    pthread_exit(NULL);
}


// Function to sort 1K chunks using multiple threads
void *sort1kChunks(void *arg) {
    int threadId = *((int *)arg);


    while (1) {
        // Lock mutex to safely access NextChunkToSort
        pthread_mutex_lock(&NextChunkToSortMutex);
        int chunkToSort = NextChunkToSort;
         if (chunkToSort >= TOTALELEMENTS / CHUNKSIZE) {
            pthread_mutex_unlock(&NextChunkToSortMutex);
            break;
        }

        NextChunkToSort++;
        
    
        pthread_mutex_unlock(&NextChunkToSortMutex);

        int startIdx = chunkToSort * CHUNKSIZE;

        bsort(NumbersA + startIdx, CHUNKSIZE);

        // Perform bsort on the 1K chunk assigned to this thread
       // bsort(NumbersA + chunkToSort * CHUNKSIZE, CHUNKSIZE);
       // bsort(NumbersA + chunkToSort * HALF, HALF);

        // Print the chunk number and thread ID to indicate progress
        printf("Thread %d sorted chunk %d\n", threadId, chunkToSort);
    }

    pthread_exit(NULL);

}


int main() {
    // Allocate memory for arrays
    NumbersO = (unsigned long long *)malloc(TOTALELEMENTS * sizeof(unsigned long long));
    NumbersQ = (unsigned long long *)malloc(TOTALELEMENTS * sizeof(unsigned long long));
    NumbersA = (unsigned long long *)malloc(TOTALELEMENTS * sizeof(unsigned long long));
    NumbersB = (unsigned long long *)malloc(TOTALELEMENTS * sizeof(unsigned long long));

    create(NumbersO);

    arycpy(NumbersQ, NumbersO, TOTALELEMENTS); // copying from NumbersO to Q

    qsort(NumbersQ, TOTALELEMENTS, sizeof(unsigned long long), compare);  // Sorting using qsort

// Copy NumbersO into NumbersA
    arycpy(NumbersA, NumbersO, TOTALELEMENTS);
   
   clock_t start_time = clock();
// Sort each 1K chunk separately using bsort() in multi-threading
  //  NextChunkToSort = 0;
    
    pthread_t sortThreads[THREAD_COUNT];
    int sortThreadIds[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        sortThreadIds[i] = i;
        pthread_create(&sortThreads[i], NULL, sort1kChunks, &sortThreadIds[i]);
    }

    // Join sorting threads after sorting is complete
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(sortThreads[i], NULL);
    }

    // Reset NextChunkToSort for the merging phase
    NextChunkToSort = 0;

    // Double the CurrentChunkSize for the first iteration of merging
   CurrentChunkSize = CHUNKSIZE;
   // int CurrentChunkSize *= 2;

    while (CurrentChunkSize < TOTALELEMENTS) {
        // Create pthreads and merge chunks
        pthread_t mergeThreads[THREAD_COUNT];
        int mergeThreadIds[THREAD_COUNT];

        for (int i = 0; i < THREAD_COUNT; i++) {
            mergeThreadIds[i] = i;
            pthread_create(&mergeThreads[i], NULL, mergeChunks, &mergeThreadIds[i]);
        }

        // Join merging threads after merging is complete
        for (int i = 0; i < THREAD_COUNT; i++) {
            pthread_join(mergeThreads[i], NULL);
        }


        // Swap NumbersA and NumbersB for the next iteration
        unsigned long long *temp = NumbersA;
        NumbersA = NumbersB;
        NumbersB = temp;

        // Double the CurrentChunkSize for the next iteration
        CurrentChunkSize *= 2;
    } 

    clock_t end_time = clock();
    double runtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the total runtime
    printf("Total Runtime: %9.4f seconds\n", runtime);

    // arycpy(NumbersA, NumbersO, TOTALELEMENTS); // copying from NumbersO to A

    // Bubble sort
    // clock_t start_time_bsort = clock();
    // bsort(NumbersA, HALF);
    // bsort(NumbersA+HALF, HALF);
    // merge(NumbersA, NumbersA+HALF, HALF, NumbersB);
    // clock_t end_time_bsort = clock();
    // double runtime_bsort = ((double)(end_time_bsort - start_time_bsort)) / CLOCKS_PER_SEC;
    //  printf("Bubble Sort Runtime: %9.4f seconds\n", runtime_bsort);

    // Sort and merge using the specified approach
    // clock_t start_time = clock();
    // sortandmerge();
    // clock_t end_time = clock();
    // double runtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    // printf("Total Runtime: %f seconds\n", runtime);
    // arycpy(NumbersA, NumbersO, TOTALELEMENTS); // copying from NumbersO to A


    // clock_t start_time_merge = clock();
    // merge(&NumbersA[0], &NumbersA[HALF], HALF, NumbersB);
    // printf("Merged Array (NumbersB): ");

    // for (int i = 0; i < TOTALELEMENTS; i++) {
    //     printf("%llu ", NumbersB[i]);
    // }
    // printf("\n");
    // clock_t end_time_merge = clock();
    // double runtime_merge = ((double)(end_time_merge - start_time_merge)) / CLOCKS_PER_SEC;
    // printf("Merge Sort Runtime: %9.4f seconds\n", runtime_merge);

    // Compare sorted arrays
    arycmp(NumbersB, NumbersQ, TOTALELEMENTS);

    // Check the first 10 entries to validate sorting
    printf("First 10 sorted entries: ");
    for (int i = 0; i < 20; i++) {
       printf("\n %llu \t %llu \t %llu", NumbersQ[i], NumbersA[i], NumbersB[i]);
    }
    printf("\n");

   pthread_mutex_destroy(&NextChunkToSortMutex);
    pthread_mutex_destroy(&NextChunkToMergeMutex);

    // Free allocated memory
    free(NumbersO);
    free(NumbersQ);
    free(NumbersA);
    free(NumbersB);

    return 0;
}

