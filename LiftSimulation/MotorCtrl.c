/*
 * MotorCtrl.c
 *
 * Created: 09.12.2019 09:52:43
 *  Author: xxx
 */ 

#include "AppIncludes.h"
#include "LiftLibrary.h"


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
		SetState(&_motorCtrl.fsm, MotorCtrl_Stopped);
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
		SetState(&_motorCtrl.fsm, MotorCtrl_Moving);
		MoveElevator(_motorCtrl.target * POS_STEPS_PER_FLOOR, OnElevatorPositionChanged );
	}
}


void MotorCtrl_AwaitOpen(Message* msg)
{
	SetDoorState(DoorClosed, _motorCtrl.target);
	SetState(&_motorCtrl.fsm, MotorCtrl_Stopped);
}



void MotorCtrl_Moving(Message* msg)
{
	Usart_PutChar(msg->Id);
	// ist angekommen
	if( msg->Id == Message_PosChanged && msg->MsgParamLow == msg->MsgParamHigh)
	{
		_motorCtrl.target = (FloorType)msg->MsgParamLow/POS_STEPS_PER_FLOOR;
		SetState(&_motorCtrl.fsm, MotorCtrl_AwaitOpen);
		SetDoorState(DoorOpen, _motorCtrl.target);
		
	}	
}



