#include <stdio.h>
#include <stdlib.h>

#define TOTAL_FRAMES 3
#define TOTAL_REQUESTS 10

int fcfs(int *requests);
int lru(int *requests);
int optimal(int *requests);

int main() {
    int requests[TOTAL_REQUESTS] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1};

    int ch ;
    printf("Enter your choice:\n1. For FCFS Algorithm.\n2. For LRU Algorithm.\n3. For Optimal Algorithm.\n") ;
    scanf("%d" , &ch) ;

    switch (ch)
    {
    case 1:
    printf("FCFS algorithm - Total page faults: %d\n", fcfs(requests));
    break;
    case 2:
    printf("LRU algorithm - Total page faults: %d\n", lru(requests));
    break;
    case 3:
    printf("Optimal algorithm - Total page faults: %d\n", optimal(requests));
    break;
    default:
    printf("Wrong Choice.\n") ;
    break;
    }

    return 0;
}

int fcfs(int *requests) {
    int frames[TOTAL_FRAMES] = {0};
    int page_faults = 0;
    int i, j, k;

    for (i = 0; i < TOTAL_REQUESTS; i++) {
        int found = 0;

        for (j = 0; j < TOTAL_FRAMES; j++) {
            if (frames[j] == requests[i]) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            frames[page_faults % TOTAL_FRAMES] = requests[i];
            page_faults++;
        }
    }

    return page_faults;
}

int lru(int *requests) {
    int frames[TOTAL_FRAMES] = {0};
    int page_faults = 0;
    int count[TOTAL_FRAMES] = {0};
    int i, j, k, l;
    int reference = 0;

    for (i = 0; i < TOTAL_REQUESTS; i++) {
        int found = 0;

        for (j = 0; j < TOTAL_FRAMES; j++) {
            if (frames[j] == requests[i]) {
                found = 1;
                count[j] = reference++;
                break;
            }
        }

        if (found == 0) {
            int min = 0;
            for (k = 1; k < TOTAL_FRAMES; k++) {
                if (count[k] < count[min]) {
                    min = j;
                }
            }
            frames[min] = requests[i];
            count[min] = reference++;
            page_faults++;
        }
    }

    return page_faults;
}

int optimal(int *requests) {
    int frames[TOTAL_FRAMES] = {0};
    int page_faults = 0;
    int i, j, k;

    for (i = 0; i < TOTAL_REQUESTS; i++) {
        int found = 0;
        for (j = 0; j < TOTAL_FRAMES; j++) {
            if (frames[j] == requests[i]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            int max = 0;
            int pos = 0;
            for (j = 0; j < TOTAL_FRAMES; j++) {
                int future = 0;
                for (k = i + 1; k < TOTAL_REQUESTS; k++) {
                    if (requests[k] == frames[j]) {
                        future = k - i;
                        break;
                    }
                }
                if (future == 0) {
                    pos = j;
                    break;
                }
                if (future > max) {
                    max = future;
                    pos = j;
                }
            }
            frames[pos] = requests[i];
            page_faults++;
        }
    }

    return page_faults;
}