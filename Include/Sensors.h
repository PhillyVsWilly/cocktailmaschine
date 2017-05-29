#ifndef SENSORS_H_ 
#define SENSORS_H_ 

#include <stdint.h>

typedef unsigned char uint_8; 

//Define the Type where all input values will be stored later
typedef struct {
	uint_8 Button;
} InputValues_t;

void vReadSensorValues(InputValues_t*);

#endif 

