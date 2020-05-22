/*bubblesort.c


*/

#include "syscall.h"
#include "copyright.h"

int main(){
    int arr[100];
    int n, tmp;
    int isSwap = 0;
    int i, j;

    PrintString("\nInput an array under 100 elements: ");
    n = ReadInt();
    PrintChar('\n');
    for (i = 0; i < n; i++){
        arr[i] = ReadInt();
    }

	for (i = 0; i < n - 1; i++) {
		isSwap = 0;

		for (j = i; j < n-1; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;

				isSwap = 1;
			}
		}
		if (isSwap == 0)
			break;
	}

    PrintString("BubbleSort: \n");
    for (i = 0; i < n; i++){
        PrintInt(arr[i]);
        PrintChar(32);
    }

    return 0;
}
