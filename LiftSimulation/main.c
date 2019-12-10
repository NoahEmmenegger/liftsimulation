/**
 * @file LiftSimulation.c
 * @brief Hauptprogramm und entry point der Liftsteuerung
 *
 * @date 20.11.2019 Erstellen des Templates
 * @author
 */ 

#include "LiftLibrary.h"
#include "LiftSimulationCommon.h"

void TestFunction(uint8_t* data, uint8_t nrOfBytes);

void WriteString(char* ch);

int FindBit(int num);


int main(void)
{
   InitializePorts();
   Usart_Init();
   RegisterTestHandler(TestFunction );
   InitializeStart();
   
  
}

void TestFunction(uint8_t* data, uint8_t nrOfBytes)
{
	if (data[0] == 1)
	{
		WriteString("Hello-World");
	}
	
	if (data[0] == 2)
	{
		WriteString(FindBit(3));
	}
}

int FindBit(int num)
{
	int counter = 0;
	
	//if number is uneven, then last bit is 1. Therefore return 0
	while(num % 2 == 0)
	{
		num = num >> 1;
		counter++;
	}
	return counter;
}

void WriteString(char* ch)
{
	 uint8_t nrOfBytes = strlen(ch);
	
	for (;nrOfBytes > 0; nrOfBytes--)
	{
		Usart_PutChar(*ch++);
	}
	
	Usart_PutChar('\n');
}

