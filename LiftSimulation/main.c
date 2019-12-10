/*
 * GccApplication1.c
 *
 * Created: 26.11.2019 16:29:04
 * Author : rolfl
 */ 

#include <avr/io.h>

#include "LiftLibrary.h"
#include "AppIncludes.h"







int main(void)
{
    InitializePorts();
	Usart_Init();
	RegisterTestHandler( TestFunction );
	RegisterFsm(&_motorCtrl.fsm);
	// letzte Funktion die aufgerufen wird!
	InitializeStart();
}





