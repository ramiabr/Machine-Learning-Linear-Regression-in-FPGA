#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <string.h>
//#include <ap_fixed.h>
#include "linear_regression.h"

//using namespace std;


int linear_regression(float house_size[SAMPLES], float house_price[SAMPLES], float weights[2]) {	
	float fx;
	float learning_rate = LEARNING_RATE;
	float samples = SAMPLES;
	
	ONE_ITERATION: for (int y=0; y < ITERATIONS; y++) {
		float jw0 = 0.0;
		float jw1 = 0.0;
		float sq = 0.0;
		
		ACCELERATION: for (int i=0; i < SAMPLES; i++) {
			
				fx = weights[0] + (house_size[i] * weights[1]); // 5 DSP slices
				jw0 += (fx - house_price[i]); // 5 DSP slices
				jw1 += (fx - house_price[i]) * house_size[i]; // 7 slice
		}
		jw0 = jw0 / samples;
		jw1 = jw1 / samples; // 7 DSP slices
		
		weights[0] = weights[0] - (learning_rate * jw0);
		weights[1] = weights[1] - (learning_rate * jw1);

	}
	
	return 0;
}
