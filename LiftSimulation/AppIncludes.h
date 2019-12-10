/*
 * AppIncludes.h
 *
 * Created: 09.12.2019 09:52:06
 *  Author: rolfl
 */ 


#ifndef APPINCLUDES_H_
#define APPINCLUDES_H_
#include "LiftLibrary.h"

/** 
* Signature der  Test Function
*
* @param array mit den daten für den test, welcher ausgeführt werden soll
* @param lenght of data array
*
*/
void TestFunction(uint8_t* data, uint8_t nrOfBytes);

/** 
* Anwendungs-Meldungen: Der Bereich bis 0xC0 kann verwendet werden
*
*/
typedef enum 
{
	Message_MoveTo = 1,	
	Message_PosChanged = 2,
} AppMessages;

/** 
* @brief Zustände deer Motor-Überwachung
*/
void MotorCtrl_Initializing(Message* msg);
void MotorCtrl_Stopped(Message* msg);
void MotorCtrl_Moving(Message* msg);

/** 
* @brief Struktur für den Motor-Controller
*/

typedef struct MotorController_tag
{
	Fsm fsm;				//< Zustandsmaschine
	FloorType start;		//< start etage
	FloorType target;		//< ziel etage
} MotorController;


/** 
* @brief Ein einziger Zustand für den TestController
* 
*/
void TestController_HandleMessages(Message* msg);



/** 
* @brief Struktur für bahandeln von test Ereignissen
*/
typedef struct TestController_tag
{
	Fsm fsm;
	uint8_t CurrentTestCase;	
}TestController;

extern MotorController _motorCtrl;


#endif /* APPINCLUDES_H_ */