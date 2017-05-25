#include "Evaluation.h"

void vEvaluate(InputValues_t input, OutputValues_t* output)
{
		if (input.Button == 0)
		{
			output->LED2 = 1;
		} else {
			output->LED2 = 0;
		}
}