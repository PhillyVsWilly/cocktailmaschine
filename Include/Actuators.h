#ifndef ACUATORS_H_
#define ACUATORS_H_

#include <stdint.h>

typedef unsigned char uint_8; 

//Define the Type where all output values will be stored later
typedef struct {
	uint_8 LED2;
} OutputValues_t;


void vInitActuatorValues(OutputValues_t*);
void vWriteActuatorValues(OutputValues_t);
#endif
