/*bubblesort.c


*/

#include "syscall.h"
#include "copyright.h"

void inc_sort(int arr[], int n){
	int i, j, tmp;
	int isSwap = 0;
	for (i = 0; i < n - 1; i++) {
		isSwap = 0;

		for (j = 0; j < n-1-i; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;

				isSwap = 1;
			}
		}
		if (isSwap == 0)
			break;
	}
}

void dec_sort(int arr[], int n){
	int i, j, tmp;
	int isSwap = 0;
	for (i = n - 1; i >=0 ; i--) {
		isSwap = 0;

		for (j = n - 1; j > 0; j--) {
			if (arr[j] > arr[j - 1]) {
				tmp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = tmp;

				isSwap = 1;
			}
		}
		if (isSwap == 0)
			break;
	}
}

int 
main(){
    int arr[100];
    int n, tmp;
    
    int i, j, choice = 1;

    PrintString("Input an array under 100 elements: \n");
    n = ReadInt();
    
    if(n == 0){
    	PrintString("Can not initialize array\n");
	return 0;
    }

    PrintString("Input number into array: \n");
    for (i = 0; i < n; i++){
	PrintString("Element ");
	PrintInt(i + 1);
	PrintString(": ");
        arr[i] = ReadInt();
    }

	
    PrintString("Do you want to sort the array INCREASE or DECREASE\n");
    PrintString("1: INCREASE\n");
    PrintString("2: DECREASE\n");
    

    do{
	PrintString("Your Choice --> ");
	choice = ReadInt();
    }while(choice != 1 && choice != 2);
    
	//PrintString("Out While");
    switch(choice){
    	case 1:
 		inc_sort(arr,n);
		break;
	case 2:
		dec_sort(arr,n);
		break;
	default: break;
    }

    PrintString("BubbleSort: \n");
    for (i = 0; i < n; i++){
        PrintInt(arr[i]);
        PrintChar(32);
    }

    return 0;
}
