/*ascii.c


*/

#include "syscall.h"
#include "copyright.h"

int main(){
    int i = 32;
    PrintString("ASCII Table from 32 to 126\n");
    for (; i < 127; i++){
        PrintInt(i);
        PrintChar(':');
        PrintChar((char)i);
        PrintChar('\n');
    }
    return 0;
}
