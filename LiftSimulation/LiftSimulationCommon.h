  /** 
* @file Definiert gemeinsame Datentypen im Projekt
* @author:
*
*/

#ifndef __LIFT_SIMULATION_COMMON__
#define __LIFT_SIMULATION_COMMON__

typedef struct MainCtrl_tag
{
	Fsm fsm;							// Zustandsmaschine
	FloorType currentFloor;				// aktuelle Position
	FloorType nextFloor;				// nächste Zielposition
	uint8_t timer;						// erlaubt den Timer index zu speichern
	uint8_t pendingRequests;			// Bitmaske um mehrfach einträge in die Q zu vermeiden
	FloorType ElevatorNextPosQ[4];		// q für reservationen
	uint8_t qIn;						// position für nächsten put
	uint8_t qOut;                       // position für nächsten get
}MainCtrl;

extern MainCtrl _mainCtrl;


uint8_t FindBit(uint8_t value);

#endif