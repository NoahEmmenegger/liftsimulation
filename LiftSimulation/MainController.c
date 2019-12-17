/**
 * @file MainController.c
 * @brief Zustandsmaschine für Haupt Steuerung
 *
 * @date  24.11.2019 - Erstellen des templates
 * @author  
 */

#include "LiftSimulationCommon.h" 
#include "AppIncludes.h"
#include "LiftLibrary.h"

void ButtonCtrl_Initializing(Message* msg);
void ButtonCtrl_Click(Message* msg);

ButtonController _buttonCtrl =
{
	.fsm  = { .Next = 0, .CurrentState = ButtonCtrl_Initializing, .RxMask = 0xFF },
};

void ButtonCtrl_Initializing(Message* msg)
{
	SetState(&_buttonCtrl.fsm, ButtonCtrl_Click );
	
	if( msg->Id == ButtonEvent)
	{
		ButtonCtrl_Click(msg->Id);
		return;
	}
}

void ButtonCtrl_Click(Message* msg)
{
	Usart_PutChar(msg->Id);
	//ToDo FindBit Methode gebrauchen, um herauszufinden, in welche Etage man möchte. Makros verwenden aus LiftLibrary.h, um herauszufinden ob es eine Reservation oder eine Etagenwahl ist.
	SendEvent(SignalSourceApp, Message_MoveTo, //target mitgeben, 0);
}