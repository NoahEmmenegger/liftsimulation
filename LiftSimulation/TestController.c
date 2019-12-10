/*
 * TestController.c
 *
 * Created: 10.12.2019 11:59:02
 *  Author: xxx
 */ 


#include "AppIncludes.h"


TestController _testCtrl =
{
	.fsm  = { .Next = 0, .CurrentState = TestController_HandleMessages, .RxMask = 0xFF },
	.CurrentTestCase = 0
};

void TestController_HandleMessages(Message* msg)
{
	
}

void TestFunction(uint8_t* data, uint8_t nrOfBytes)
{
	if( data[0] == 1 )
	{
		char *ch = "Hello-World\n";
		while( *ch != 0 )
		{
			Usart_PutChar(*ch++);
		}
	}
	else if( data[0] == 2 )
	{
		SendEvent(SignalSourceApp, Message_MoveTo, data[1], 0);
	}
}
