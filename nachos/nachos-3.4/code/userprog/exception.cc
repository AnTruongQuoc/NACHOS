// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void Inc_Program_Counter(){
      machine->Registers[PrevPCReg] = machine->Registers[PCReg];
	machine->Registers[PCReg] = machine->Registers[NextPCReg];
	machine->Registers[NextPCReg] += 4;
}

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch(which){
        case NoException:
            printf("Everything OK");
            interrupt->Halt();
            break;           
		
		case PageFaultException:   
            printf("No valid translation found");
            interrupt->Halt();
            break; 
		case ReadOnlyException:    
            printf("Write attempted to page marked read-only");
            interrupt->Halt();
            break; 
		case BusErrorException:    
            printf("Translation resulted in an invalid physical address");
            interrupt->Halt();
            break; 
		case AddressErrorException: 
            printf("Unaligned reference or one that was beyond the end of the address space");
            interrupt->Halt();
            break; 
		case OverflowException:     
            printf("Integer overflow in add or sub.");
            interrupt->Halt();
            break; 
		case IllegalInstrException: 
            printf(" Unimplemented or reserved instr.");
            interrupt->Halt();
            break; 
		case NumExceptionTypes:
            break;

        case SyscallException:     
            printf("A program executed a system call.");
            switch(type){
                  case SC_Halt:
                        DEBUG('a', "Shutdown, initiated by user program. \n");
                        interrupt->Halt();
                        break;
                  case SC_ReadInt:
                        DEBUG('a', "Read integer number from console.\n");
                        int num = 0;
                        int digit = 0;
                        int i = 0;
                        bool isNum = true;

                        char* buffer = new char[INT_MAX_LENGTH];
                        digit = gSynchConsole->Read(buffer, INT_MAX_LENGTH);
                        
                        //Empty number
                        if (digit < 1){
                              machine->WriteRegister(2, 0);
                              isNum = false;
                              break;
                        }
                        //i = buffer[0] == '-' ? 1:0;
                        //Check first digit is '-' ?
                        if (buffer[0] == '-'){
                              //Check case: User only type '-' character
                              if (digit == 1){
                                    machine->WriteRegister(2, 0);
                                    isNum = false;
                                    break;
                              }
                              i = 1;
                        }
                        else if (buffer[0] >= '0' && buffer[0] <= '9'){ //Case: positive number
                              i = 0;
                        }
                        else {      //Case: It is not a number
                              machine->WriteRegister(2, 0);
                              isNum = false;
                              break;
                        }
                        
                        //Check another digit isNumber ?
                        for (int k = 1; k < digit; k++){
                              if (buffer[k] < '0' || buffer[k] > '9'){
                                    machine->WriteRegister(2, 0);
                                    isNum = false;
                                    break;
                              }
                        }

                        //Convert string into INT
                        for(; i < digit; i++){
                              num = num*10 + (int)(buffer[i] & MASK_GET_NUM);
                        }
                        num = buffer[0] == '-' ? -1*num : num;

                        if (isNum){
                              machine->WriteRegister(2, num);
                        }
                       
                        delete buffer;
                        
                        Inc_Program_Counter();
                        break;
                  case SC_PrintInt:
                        //Put number into reg(4)
                        int num = 0, len = 0, k = 0;
                        num = machine->ReadRegister(4);
                        
                        if (num < 0){
                              char c = '-';
                              gSynchConsole->Write(&c, 1);
                              num = num * -1;
                        }

                        if (num = 0){
                              char c = '0';
                              gSynchConsole->Write(&c, 1);
                              break;
                        }
                        
                        char* s = new char[INT_MAX_LENGTH]
                        if (num > 0){
                              s[len++] = num % 10 + '0';
                              num /= 10;
                        }
                        
                        //Reverse string above
                        char tmp = '0';
                        for (int i = 0; i < len/2; i++){
                              tmp = s[i];
                              s[i] = s[len - i -1];
                              s[len -i - 1] = tmp;
                        }

                        Inc_Program_Counter();
                        break;
                  case SC_ReadChar:
                        Inc_Program_Counter();
                        break;
                  case Sc_PrintChar:
                        Inc_Program_Counter();
                        break;
                  case SC_ReadString:
                        Inc_Program_Counter();
                        break;
                  case SC_PrintString:
                        Inc_Program_Counter();
                        break;     
            }
            break; 

    }

    /* OLD CODE EXAMPLE
    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
    */
}
