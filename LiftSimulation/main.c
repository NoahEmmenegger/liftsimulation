/*
 * GccApplication1.c
 *
 * Created: 26.11.2019 16:29:04
 * Author : rolfl
 */ 

#include <avr/io.h>

#include "LiftLibrary.h"
#include "LiftSimulationCommon.h"
#include "AppIncludes.h"

//void TestFunction(uint8_t* data, uint8_t nrOfBytes);
//
//void WriteString(char* ch);
//
//int FindBit(int num);

//struct Lift(){
	//FloorType etage;
	//SignalSourceType ereignisquelle;
	//SpeedType geschwindigkeit;
	//DoorStateType tuerZustand;
//}






int main(void)
{
    InitializePorts();
	Usart_Init();
	RegisterTestHandler( TestFunction );
	RegisterFsm(&_motorCtrl.fsm);
	// letzte Funktion die aufgerufen wird!
	InitializeStart();
	
	
}

//void TestFunction(uint8_t* data, uint8_t nrOfBytes)
//{
	//if (data[0] == 1)
	//{
		//WriteString("Hello-World");
	//}
	//
	//if (data[0] == 2)
	//{
		//WriteString(FindBit(3));
	//}
//}
//
//int FindBit(int num)
//{
	//int counter = 0;
	//
	////if number is uneven, then last bit is 1. Therefore return 0
	//while(num % 2 == 0)
	//{
		//num = num >> 1;
		//counter++;
	//}
	//return counter;
//}
//
//void WriteString(char* ch)
//{
	//uint8_t nrOfBytes = strlen(ch);
	//
	//for (;nrOfBytes > 0; nrOfBytes--)
	//{
		//Usart_PutChar(*ch++);
	//}
	//
	//Usart_PutChar('\n');
//}





