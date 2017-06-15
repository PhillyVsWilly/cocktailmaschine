#include "Module_common.h"
#include "TEMPLATE_Module_x_Name.h"

#include "Sensors.h"
#include "Evaluation.h"
#include "Actuators.h"

#undef DEBUG_ENABLED
#define DEBUG_ENABLED 1
#include "Debug.h"

//Hier steht die Modulnummer. Sie wird im Code nicht hart gecodet, sondern nur hier eingetragen 
//Im Code wird sie dann mit dem Namen MODULE_NUMBER verwendet
#define MODULE_NUMBER 10


/** @brief Initialisierung des Teilmoduls 
 *
 * Hier werden die Anfangswerte der Zust�nde und der Variablen eingestellt. Die Funktion wird nur ein einziges
 * Mal beim Systemstart ausgef�hrt
**/
void vInit_Module_x_Name(Module_State_x_Name_t* state, State_General_t* ptrGeneralState)
{
	//Nicht �ndern, muss so sein!
	state->state = REFERENCE;
	state->ptrGeneralState = ptrGeneralState;
	
	// Hier k�nnen jetzt noch - falls n�tig - Startwerte f�r die anderen Zustandsvariablen gegeben werden
}

/** @brief Pr�fe nach allgmeinen Fehlern
 *Diese Funktion muss bei jedem Zyklus ausgef�hrt werden. In ihr werden Systemzust�nde �berpr�ft, die unabh�ngig vom 
 *Ablauf des Systems sind. 
 *Bsp: Beim Transportmodul: Keine Hand in der Maschine
 *Beim Eis: �berlaufbecken nicht voll
 *Deshalb wird ihr auch nicht der Systemzustand �bergeben
 **/
int vCheckForGeneralErrors(InputValues_t input)
{
	
	if(input.Module_x_Name.placeholder > 10.0)
	{
		//ThrowError ist die zentrale "Fehlerverwaltung". An sie werden alle Fehler �bergeben, die geworfen werden sollen 
		ThrowError(MODULE_NUMBER, MOTOR1_NOT_MOVING);
		
		//Gibt den aktuell geworfenen Fehler aus
		return MOTOR1_NOT_MOVING;
	}
	
	return -1;
}
	
/** @brief Zentrale Ablaufsteuerung des Moduls 
 * 
 * Dieses Modul wird in jedem Zyklus aufgerufen und steuert das Modul
 * In ihr wird zuerst vCheckForErrors aufgerufen um zuerst nach allgemeinen Fehlern zu suchen
 * Danach wird in Abh�ngigkeit des Modulzustands state->state und des Betriebszustands *(state->ptrGeneralState) eine 
 * oder mehrere bestimmte Aktionen ausgef�hrt und deren Verlauf �berwacht 
 * Hier k�nnen �ber ThrowError() auch weitere Fehler geworfen werden.
 * Soll der Modulzustand gewechselt werden, wird die vSwitchState() Funktion benutzt. Diese pr�ft die generelle Zul�ssigkeit
 * (falls n�tig) des Zustandswechsels und schreibt einen Debug-Print.
 **/
void vEvaluate_Module_x_Name(InputValues_t input, Module_State_x_Name_t* state, OutputValues_t* output)
{
	//�ndern des Status auf Basis des Gesamtmaschinenzustand
	if (state->ptrGeneralState->operation_mode == stop)
	{
		vSwitchState(state, STATE3);
	}
	
	//Ausf�hren von Funktionen basierend auf dem Zustand
	switch (state->state){
		case STATE1:
			//Do something
			DPRINT_MESSAGE("I'm in State %d\n", state->state);
			if(state->var_a == TRUE)
			{
				vSwitchState(state, STATE2);
			}
			break;
		case STATE2:
			//Do something
			DPRINT_MESSAGE("I'm in State %d\n", state->state);
			break;
		case STATE3:
			//Do something
			DPRINT_MESSAGE("I'm in State %d\n", state->state);
			break;
		default:
			break;
		}
	
		return;
		
}

void vSwitchState(Module_State_x_Name_t* state, int state_new)
{
	//Hier kommt alles rein, was bei jedem(!) Zustandswechsel passieren soll
	DPRINT_MESSAGE("Switching states from State %d to State %d\r\n", state->state, state_new);
	
	//Das hier sollte passieren, sonst wird der Zustand nicht gewechselt
	state->state = state_new;
	
	return;
}

/*****************************************************************/
/*****					HILFSFUNKTIONEN															******/
/* Hier komme alle Codeabschnitte hin, die mehr als 10-20 Zeilen */
/* besitzen, damit vEvaluate nicht zu aufgeblasen wird					 */
/*****************************************************************/

//vHilfsfuntion1() {  }
//vHilfsfuntion2() {  }

