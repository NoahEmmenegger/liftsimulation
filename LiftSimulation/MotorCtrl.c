/*
 * MotorCtrl.c
 *
 * Created: 09.12.2019 09:52:43
 *  Author: xxx
 */ 

#include "AppIncludes.h"
#include "LiftLibrary.h"

void MotorCtrl_AwaitClosed(Message* msg);


MotorController _motorCtrl =
{
	.start = Floor2,
	.target = Floor0,
	.fsm  = { .Next = 0, .CurrentState = MotorCtrl_Initializing, .RxMask = 0xFF },
};

void NotifyCalibrationDone(uint8_t currentPos, uint8_t targetPostion)
{
	FloorType floor = (FloorType)currentPos/POS_STEPS_PER_FLOOR;
	SetDisplay(floor);
	if( ((currentPos %floor) == 0 ) && floor == Floor0 )
	{
		SendEvent(SignalSourceEnvironment, LiftCalibrated, currentPos, targetPostion);
	}
}

void MotorCtrl_Initializing(Message* msg)
{
	if( msg->Id == LiftStarted)
	{
		CalibrateElevatorPosition(NotifyCalibrationDone);
		return;
	}
	if( msg->Id == LiftCalibrated )
	{
		SetDisplay(Floor0);
		SendEvent(SignalSourceApp, Message_ElevatorReady, Floor0, 0);
		SetState(&_motorCtrl.fsm, MotorCtrl_Stopped);
		_motorCtrl.start = Floor0;
	}
}

void OnElevatorPositionChanged(uint8_t currentPos, uint8_t targetPos)
{
	SendEvent(SignalSourceElevator, Message_PosChanged, currentPos, targetPos);
}


void MotorCtrl_Stopped(Message* msg)
{
	if( msg->Id == Message_MoveTo && msg->MsgParamLow < 4)
	{
		_motorCtrl.target = (FloorType)msg->MsgParamLow;
		SetState(&_motorCtrl.fsm, MotorCtrl_AwaitClosed);
		SetDoorState(DoorClosed, _motorCtrl.start);		
	}
}


void MotorCtrl_AwaitOpen(Message* msg)
{
	Usart_PutChar(0x70);
	Usart_PutChar(msg->Id);
	if( msg->Id == LiftDoorEvent && msg->MsgParamLow == DoorOpen)
	{
		_motorCtrl.start = msg->MsgParamHigh;
		SendEvent(SignalSourceApp, Message_ElevatorReady, _motorCtrl.start, 0);
				
		SetState(&_motorCtrl.fsm, MotorCtrl_Stopped);
			
	}
	//SendEvent(SignalSourceElevator, Message_ElevatorHasStartedToMove, false, 0);
}

void MotorCtrl_AwaitClosed(Message* msg)
{
		Usart_PutChar(0x60);
		Usart_PutChar(msg->Id);
	if(msg->Id == LiftDoorEvent && msg->MsgParamLow == DoorClosed)
	{
		if(_motorCtrl.start == _motorCtrl.target )
		{
			SetState(&_motorCtrl.fsm, MotorCtrl_Stopped);
			//SendEvent(SignalSourceElevator, Message_ElevatorHasStartedToMove, true, 0);
			SendEvent(SignalSourceElevator, Message_ElevatorHasStartedToMove, 0, 0);
		}
		else{
			
			SetState(&_motorCtrl.fsm, MotorCtrl_Moving);
			MoveElevator(_motorCtrl.target * POS_STEPS_PER_FLOOR, OnElevatorPositionChanged );
			SendEvent(SignalSourceElevator, Message_ElevatorHasStartedToMove, true, 0);
		}
	}
	
}
	

void MotorCtrl_Moving(Message* msg)
{
	Usart_PutChar(msg->Id);
	// ist angekommen
	SetDisplay(msg->MsgParamLow/POS_STEPS_PER_FLOOR);
	if( msg->Id == Message_PosChanged && msg->MsgParamLow == msg->MsgParamHigh)
	{
		
		_motorCtrl.target = (FloorType)msg->MsgParamLow/POS_STEPS_PER_FLOOR;
		SetState(&_motorCtrl.fsm, MotorCtrl_AwaitOpen);
		SetDoorState(DoorOpen, _motorCtrl.target);
		
	}	
}



