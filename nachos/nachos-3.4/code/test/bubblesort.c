/*bubblesort.c


*/

#include "syscall.h"

int main(){
    int arr[100];
    int n, tmp;
    bool isSwap = false;

    PrintString("\nInput an array under 100 elements: ");
    n = ReadInt();
    PrintChar('\n');
    for (int i = 0; i < n; i++){
        arr[i] = ReadInt();
    }

	for (int i = 0; i < n - 1; i++) {
		isSwap = false;

		for (int j = i; j < n-1; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp

				isSwap = true;
			}
		}
		if (isSwap == false)
			break;
	}

    PrintString("BubbleSort: \n");
    PrintChar();
    for (int i = 0; i < n; i++){
        PrintInt(arr[i]);
        PrintChar(32);
    }

    return 0;
}