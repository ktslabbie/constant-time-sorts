/**

@author Kristian Slabbekoorn, 2011

Implementation of standard and constant-time versions of four different sorting algorithms:
Bubblesort, selection sort, insertion sort, and shellsort.

A constant execution-time guarantee can be useful in certain real-time systems.
These implementations are intended as experiments to see how different constant-time
sorting algorithms behave for different types of input in terms of execution time.

The paper on the results can be found here: http://ktslabbie.github.io/resources/papers/2011_Constant_Time_Algorithms.pdf

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Experiments performed on: Intel(R) Core(TM)2 Duo CPU E6850 @ 3.00GHz

void printlist(int list[] ,int n) {
    int i;
	
    for(i = 0; i < n; i++)
        printf("%d\t", list[i]);
}

void selectionsort(int list[], int n) {
    int i, j, min, t;
	
    for(i = 0; i < n; i++) {
        min = i;
        for(j = i; j < n; j++)
            if(list[min] > list[j])
                min = j;
        t = list[i];
        list[i] = list[min];
        list[min] = t;
    }
}

void selectionsort_const(int list[], int n) {
    int i, j, min, s, t, temp;
    i = 0;
	
    while(i < n) {
        min = i;
        j = i;
        while(j < n) {
            s = list[min];
            t = list[j];
            temp = ((s<=t) ? j : min);
            min = ((s>t) ? j : min);
            j++;
        }
        temp = list[i];
        list[i] = list[min];
        list[min] = temp;
        i++;
    }
}

void insertionsort(int list[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        int j, v = list[i];
        for (j = i-1; j >= 0; j--) {
            if (list[j] <= v) break;
            list[j+1] = list[j];
        }
        list[j+1] = v;
    }
}

void insertionsort_const(int list[], int n) {
    int i, j, k, v, bool, j1, j2, ljtemp, vtemp;
    int max = n;
	
    for (i = 0; i < n; i++) {
        j = i-1, v = list[i], bool = 1;
        k = 0;
		
        while(k < n) {
            int b1 = (j >= 0);
            int b2 = bool;
			
            if(b1 && b2) {
		        ljtemp = list[j];
		        vtemp = v;
		        if (ljtemp <= vtemp) bool = 0;
		        if (ljtemp > vtemp) bool = 1;
		        j1 = list[j + 1], j2 = list[j];
		        if (bool) list[j + 1] = j2;
		        if (!bool) list[j + 1] = j1;
		        j = j-1;
            }
			
            if(!(b1 && b2)) {
		        ljtemp = list[j];
                vtemp = v;
		        if (ljtemp <= vtemp) bool = 0;
		        if (ljtemp > vtemp) bool = 0;
		        j1 = list[j + 1], j2 = list[j];
		        if (bool) list[j + 1] = j2;
		        if (!bool) list[j + 1] = j1;
		        j = j-0;
            }
			
            k++;
        }
		
        list[j + 1] = v;
    }
}

void swap(int *a, int *b) {
    int t=*a; *a=*b; *b=t;
}

void quicksort(int arr[], int beg, int end) {
    if (end > beg + 1) {
        int piv = arr[beg], l = beg + 1, r = end;
		
        while (l < r)
            if (arr[l] <= piv)
                l++;
            else
                swap(&arr[l], &arr[--r]);
		
        swap(&arr[--l], &arr[beg]);
        quicksort(arr, beg, l);
        quicksort(arr, r, end);
    }
}

/* void quicksort_const(int arr[], int beg, int end) {
    int tbeg, tend, k, b1, b2, s, t, tl;
    tbeg = beg + 1;
    tend = end;

    if (tend > tbeg) {
        int piv = arr[beg], l = beg + 1, r = end;
        k = 0;
        
		while (k < (end-beg)) {
            b1 = (l < r); b2 = arr[l] <= piv;
            tl = l+1;
            if (b1 && b2)
                l = tl;
            if (!(b1 && b2))
                l = l;

            if (b1 && !b2) swap(&arr[l], &arr[--r]);
            if (!(b1 && !b2)) swap(&arr[l], &arr[l]);
            k++;
        }
		
        swap(&arr[--l], &arr[beg]);
        quicksort_const(arr, beg, l);
        quicksort_const(arr, r, end);
    }

    if (tend <= tbeg) {
        int piv = arr[beg], l = beg + 1, r = end;
        k = 0;
		
        while (k < (end-beg)) {
            b1 = (l < r); b2 = arr[l] <= piv;
            tl = l+1;
            if (b1 && b2)
                l = l;
            if (!(b1 && b2))
                l = l;

            if (b1 && !b2) swap(&arr[l], &arr[l]);
            if (!(b1 && !b2)) swap(&arr[l], &arr[l]);
            k++;
        }
		
        swap(&arr[beg], &arr[beg]);
    }
} */

void bubblesort(int list[], int n) {
    int i, j, t;
    for(i=n-1; i>0; i--)
        for(j=1; j<=i; j++)
            if (list[j-1] > list[j]) {
                t = list[j];
                list[j] = list[j-1];
                list[j-1] = t;
            }
}

void bubblesort_const(int list[], int n) {
    int i, j, s, t;
    for(i=n-1; i>0; i--)
        for(j=1; j<=i; j++) {
            s = list[j-1];
            t = list[j];
            list[j-1] = ((s<=t) ? s : t);
            list[j] = ((s>t) ? s : t);
        }
}

void shellsort(int a[], int length) {
    int i, j, k, temp, increment;
    static int incSequence[] = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    
	for (k = 0; k < sizeof(incSequence)/sizeof(int); k++) {
        if (incSequence[k]*2 > length) continue;
        increment = incSequence[k];
        for (i=increment; i < length; i++) {
            temp = a[i];
			
            for (j = i - increment; j >= 0; j -= increment) {
                if (a[j] <= temp) break;
                a[j + increment] = a[j];
            }
			
            a[j + increment] = temp;
        }
    }
}

void shellsort_const(int list[], int n) {
	int i, j, k, r, temp, increment, b1, b2, b3, b4, t1, t2, t3, t4;
	int fi, fj, fk, fr, ftemp, fincrement, fb1, fb2, fb3, fb4, ft1, ft2, ft3, ft4;
	int flist[10000];
	static int incSequence[] = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
	k = 0; fk = 0; b2 = 1; fb2 = 1;
  
	while(k < sizeof(incSequence)/sizeof(int)) {
		k++;
		if (incSequence[k]*2 > n) b2 = 0;
		if (!(incSequence[k]*2 > n)) b2 = 1;
		if (b2) {
			increment = incSequence[k];
			i = increment;
			
			while (i < n) {
				temp = list[i];
				j = i-increment;
				b1 = 1; r = 0;
				
				while(r < 16) {
					b3 = (j >= 0);
					b4 = (list[j] <= temp);
					t1 = 0;
					
					if(b3 && b1 && b4) b1 = t1;
					if(!(b3 && b1 && b4)) b1 = b1;
					
					t2 = list[j];
					t3 = j - increment;
					t4 = list[j+increment];
					
					if(b3 && b1) {
						list[j + increment] = t2;
						j = t3;
					}
					
					if(!(b3 && b1)) {
						list[j + increment] = t4;
						j = j;
					}
					
					r++;
				}
				
				list[j + increment] = temp;
				i++;
			}
		}
		
		if (!b2) {
			fincrement = incSequence[k];
			fi = fincrement;
			
			while (fi < n) {
				ftemp = list[fi];
				fj = fi-fincrement;
				fb1 = 1; fr = 0;
				
				while(fr < 16) {
					fb3 = (fj >= 0);
					fb4 = (list[fj] <= ftemp);
					ft1 = 0;
					
					if(fb3 && fb1 && fb4) fb1 = ft1;
					if(!(fb3 && fb1 && fb4)) fb1 = fb1;
					
					ft2 = list[fj];
					ft3 = fj - fincrement;
					ft4 = list[fj+fincrement];
					
					if(fb3 && fb1) {
						flist[fj + fincrement] = ft2;
						fj = ft3;
					}
					
					if(!(fb3 && fb1)) {
						flist[fj + fincrement] = ft4;
						fj = fj;
					}
					
					fr++;
				}
				
				flist[fj + fincrement] = ftemp;
				fi++;
			}
		}
	}
}

int main(int argc, char *argv[]) {
    struct timeval start, end;
    long mtime, seconds, useconds;
    const int MAX_ELEMENTS = 10000;
    int list[MAX_ELEMENTS];
    int i = 0, j = 0;

    for(j = 0; j < 20; j++) {
        if(*argv[3] == 'w') { // generate the worst case for the 4th run
            if(*argv[2] == 'v') printf("Generating worst case scenario (reversed order sorted list)...\n");
            for(i = 0; i < MAX_ELEMENTS; i++)
                list[i] = MAX_ELEMENTS - i;
        } else if (*argv[3] == 'b'){ // generate the best case for the 8th run
            if(*argv[2] == 'v') printf("Generating best case scenario (already sorted list)...\n");
            for(i = 0; i < MAX_ELEMENTS; i++)
                list[i] = i;
        } else { // generate random numbers and add them to the list
            if(*argv[2] == 'v') printf("Generating list of 10000 random numbers...\n");
            for(i = 0; i < MAX_ELEMENTS; i++)
                list[i] = rand() % 10000;
        }
		
		gettimeofday(&start, NULL); // get starting time

        if(*argv[1] == 'b') { // start normal bubblesort
            if(*argv[2] == 'v') printf("Starting normal bubble sort!\n");
            bubblesort(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 'c') { // start constant bubblesort
            if(*argv[2] == 'v') printf("Starting single-path bubble sort!\n");
            bubblesort_const(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 'i') { // start normal insertion sort
            if(*argv[2] == 'v') printf("Starting normal insertion sort!\n");
            insertionsort(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 'j') { // start constant insertion sort
            if(*argv[2] == 'v') printf("Starting single-path insertion sort!\n");
            insertionsort_const(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 'q') { // start normal quicksort
            if(*argv[2] == 'v') printf("Starting normal quick sort!\n");
            quicksort(list, 0, MAX_ELEMENTS-1);
			
        } /* else if (*argv[1] == 'r') { // start constant quicksort
            if(*argv[2] == 'v') printf("Starting single-path quick sort!\n");
            quicksort_const(list, 0, MAX_ELEMENTS-1);
			
        }*/ else if (*argv[1] == 's') { // start normal selection sort
            if(*argv[2] == 'v') printf("Starting normal selection sort!\n");
            selectionsort(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 't') { // start constant selection sort
            if(*argv[2] == 'v') printf("Starting single-path selection sort!\n");
            selectionsort_const(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 'y') { // start normal shellsort
            if(*argv[2] == 'v') printf("Starting normal shell sort!\n");
            shellsort(list, MAX_ELEMENTS);
			
        } else if (*argv[1] == 'z') { // start constant shellsort
            if(*argv[2] == 'v') printf("Starting single-path shell sort!\n");
            shellsort_const(list, MAX_ELEMENTS);
        }
		
		gettimeofday(&end, NULL);  // get ending time

        seconds  = end.tv_sec  - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        mtime = ((seconds) * 1000000 + useconds) + 0.5;
        if(*argv[2] == 'v') printf("Sorting finished! Elapsed time: %ld microseconds\n\n", mtime);
        else printf("%ld\n", mtime);
    }
	
    return 1;
}
