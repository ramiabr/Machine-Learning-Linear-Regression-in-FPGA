#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
//#include <ap_fixed.h>
#include <string.h>

#include "linear_regression.h"

//using namespace std;

#define bufSize 50

float min (float array_list[SAMPLES]) {
	float min = 0.0; 
	
	for (int i=0; i < SAMPLES; i++) {
		
		if(min == 0.0) min = array_list[i];
		
		if(array_list[i] < min) min = array_list[i];		
	}
	return min;
}

float max (float array_list[SAMPLES]) {
	float max = 0.0; 
	
	for (int i=0; i < SAMPLES; i++) {
		if(array_list[i] > max) max = array_list[i];				
		
		if(max == 0.0) max = array_list[i];
		
	}
	return max;
}

int main () {
	FILE *fp;
	FILE *out_file;
	char buf[bufSize];
	int rows, cols;
	int i,j;
	float house_size[SAMPLES];
	float house_price[SAMPLES];
	float weights[2];	

	
	weights[0] = 0.1270; 
	weights[1] = 0.9134;
	
	fp = fopen("dataset.csv","r");
	out_file = fopen("out.dat", "w");

	//Code to read the whole file and obtain the image
	for(i=0; i<SAMPLES; i++) {	
		int size; 
		float price; 
		// Read File contents	
		fgets(buf, sizeof(buf),fp);
		buf[strlen(buf)-1]='\0';	//removes the newline fgets stores
		sscanf(buf, "%f %f ", &house_size[i], &house_price[i]);	
		//sscanf(buf, "%lf %lf ", &house_size[i], &house_price[i]);	
		
	}
	
	float norm_x = max(house_size) - min(house_size);
	float norm_y = max(house_price)- min(house_price);
	
	for(i=0; i<SAMPLES; i++) {
		house_size[i] = house_size[i] / norm_x ;
		house_price[i] = house_price[i] / norm_y ;
		//printf("Hello = %f, %f ---- %f , %f, %f\n", house_size[i], house_price[i], max(house_size) , min(house_size), norm_x);
	}
	//return 0;
	
	
	// Linear regression subroutine
	linear_regression(house_size, house_price, weights);
	
	printf("Training completed and Final Weights :  \n");
	printf("----------------------------------------\n");
	//printf("W1 = %f \n", weights[0]);
	//printf("W2 = %f \n", weights[1]);
	printf("%f %f\n", weights[0], weights[1]);
	fprintf(out_file,"%f %f\n", weights[0], weights[1]);
		
	
	float predicted;
	// Testing Part 
	for(i=0; i<SAMPLES; i++) {
		predicted =  (house_size[i] * weights[1] ) + weights[0];
		//fprintf(out_file, "%f,%d, %f\n", predicted, house_price[i], ((predicted-house_price[i])/house_price[i])*100);
		float pre = predicted*norm_y; 
		float act = house_price[i]*norm_y;
		//if(i < 5) printf("%f,%f, %f, Err=%f\n", pre, house_size[i]*norm_x, house_price[i]*norm_y, ((pre-act)/pre)*100);
	}
	fclose(fp);
	fclose(out_file);
	

	printf ("Comparing against output data \n");
	if (system("diff -w out.dat out.gold.dat")) {

		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
		return 0;
  } else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
		return 0;
  }

	return 0;
}
