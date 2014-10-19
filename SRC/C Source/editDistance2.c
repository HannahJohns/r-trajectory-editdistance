
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(A,B) A < B ? A : B
#define DEBUG 0

float** distanceMatrix;
float* mass_center_shift_x_str1;
float* mass_center_shift_y_str1;
float* mass_center_shift_x_str2;
float* mass_center_shift_y_str2;
int* time_spacing_str1;
int* time_spacing_str2;
int uniform_r;

double calcDist(int a, int b, int rowSize) {
	
	int xDist, yDist;
	double dist;
		
	xDist = abs(a%rowSize - b%rowSize);
	yDist = ((a-a%rowSize)/rowSize - (b-b%rowSize)/rowSize);
	dist = sqrt((xDist*xDist + yDist*yDist));
				
	return dist;
	
	/* this was another replacement mode called non-uniform replacement where the unit distance between tiles are defined by defined by a function which has a range of three values only namely 1.0, 1.4 and 2.0
	else {
		int strDist;
		if(a == b) return 0;

		strDist = abs(a-b);

		if(strDist == 1 || strDist == rowSize) return 1;
		else if(strDist == rowSize-1 || strDist == rowSize+1) return 1.4;
		else return 2;
	}*/
}

int calcSpacing(int* str, int* len, int** spacing_vector) {
	int spacing_len = 1;
	int ctr, time_elapsed = 1, prev = str[0], prev_t = -1;
	
	for(ctr = 1; ctr < *len; ctr++) {
		if(prev != str[ctr]) {
			spacing_len++;
		}
		prev = str[ctr];
	}
	
	*spacing_vector = malloc((spacing_len+1)*sizeof(int));
	prev = -1;
	
	ctr = 0;
	for(time_elapsed = 0; time_elapsed < *len; time_elapsed++) {
		if(prev != str[time_elapsed]) {
			(*spacing_vector)[ctr] = time_elapsed - prev_t;
			str[ctr] = str[time_elapsed];
			prev_t = time_elapsed;
			ctr++;
		}
		prev = str[time_elapsed];
	}
	
	return spacing_len;
}

void editDistance(int* str1, int* str1len, int* str2, int* str2len, int* rowSize, double* time_spacing, double* result) {
	
	int ctr, ctr2;
	double cur_distance;
	float cur_avg_mass_center_x, cur_avg_mass_center_y;
	int row_size = *rowSize;
	double time_spacing_coeff = (*time_spacing)*(*time_spacing);
	
	
	*str1len = calcSpacing(str1, str1len, &time_spacing_str1);
	*str2len = calcSpacing(str2, str2len, &time_spacing_str2);
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str1len; ctr++) {
			printf("%d ", time_spacing_str1[ctr]);
		}
		printf("\n");	
	}
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str2len; ctr++) {
			printf("%d ", time_spacing_str2[ctr]);
		}
		printf("\n");	
	}
	
	distanceMatrix = malloc(((*str1len)+1)*sizeof(float*));
    mass_center_shift_x_str1 = malloc(((*str1len)+1)*sizeof(float));
    mass_center_shift_y_str1 = malloc(((*str1len)+1)*sizeof(float));
    mass_center_shift_x_str2 = malloc(((*str2len)+1)*sizeof(float));
    mass_center_shift_y_str2 = malloc(((*str2len)+1)*sizeof(float));

   	for(ctr = 0; ctr < (*str1len)+1; ctr++) {
		distanceMatrix[ctr] = malloc(((*str2len)+1)*sizeof(float));
	}
	
	mass_center_shift_x_str1[0] = 0;
	mass_center_shift_y_str1[0] = 0;
	mass_center_shift_x_str2[0] = 0;
	mass_center_shift_y_str2[0] = 0;

	cur_avg_mass_center_x = 0;
	cur_avg_mass_center_y = 0;

	for(ctr = 1; ctr <= *str1len; ctr++) {
		float cur_x = str1[ctr-1]%row_size;
		float cur_y = (str1[ctr-1]-cur_x)/row_size;
		
		mass_center_shift_x_str1[ctr] = (cur_avg_mass_center_x + cur_x)/ctr;
		cur_avg_mass_center_x += cur_x;
		
		mass_center_shift_y_str1[ctr] = (cur_avg_mass_center_y + cur_y)/ctr;
		cur_avg_mass_center_y += cur_y;
	}
	
	cur_avg_mass_center_x = 0;
	cur_avg_mass_center_y = 0;
	
	for(ctr = 1; ctr <= *str2len; ctr++) {
		float cur_x = str2[ctr-1]%row_size;
		float cur_y = (str2[ctr-1]-cur_x)/row_size;
		
		mass_center_shift_x_str2[ctr] = (cur_avg_mass_center_x + cur_x)/ctr;
		cur_avg_mass_center_x += cur_x;
		
		mass_center_shift_y_str2[ctr] = (cur_avg_mass_center_y + cur_y)/ctr;
		cur_avg_mass_center_y += cur_y;
	}
	
	/*
	for(ctr = 1; ctr <= *str1len; ctr++) {
		for(ctr2 = 1; ctr2 <= *str2len; ctr2++) {
			float cur_x_1 = str1[ctr-1]%row_size;
			float cur_y_1 = (str1[ctr-1]-cur_x_1)/row_size;
			
			float cur_x_2 = str2[ctr2-1]%row_size;
			float cur_y_2 = (str2[ctr2-1]-cur_x_2)/row_size;
			
			mass_center_x[ctr][ctr2] = ((mass_center_x[ctr-1][ctr2-1]*(ctr+ctr2-2) + cur_x_1 + cur_x_2)/(ctr + ctr2));
			mass_center_y[ctr][ctr2] = ((mass_center_y[ctr-1][ctr2-1]*(ctr+ctr2-2) + cur_y_1 + cur_y_2)/(ctr + ctr2));
		}
	}*/
	
	distanceMatrix[0][0] = 0;

	

	for(ctr = 0; ctr < *str1len; ctr++) {
		float time_dif = time_spacing_str1[ctr];
		distanceMatrix[ctr+1][0] = distanceMatrix[ctr][0] + sqrt(mass_center_shift_x_str1[ctr+1]*mass_center_shift_x_str1[ctr+1] + mass_center_shift_y_str1[ctr+1]*mass_center_shift_y_str1[ctr+1] + time_dif*time_dif*time_spacing_coeff);
	}
	
	for(ctr = 0; ctr < *str2len; ctr++) {
		float time_dif = time_spacing_str2[ctr];
		distanceMatrix[0][ctr+1] = distanceMatrix[0][ctr] + sqrt(mass_center_shift_x_str2[ctr+1]*mass_center_shift_x_str2[ctr+1] + mass_center_shift_y_str2[ctr+1]*mass_center_shift_y_str2[ctr+1] + time_dif*time_dif*time_spacing_coeff);
	}
	
	for(ctr = 1; ctr <= *str1len; ctr++) {
		for(ctr2 = 1; ctr2 <= *str2len; ctr2++) {
			//printf("%d--%d\n",str1[ctr-1],str2[ctr2-1]);
			
			float diagonal = distanceMatrix[ctr-1][ctr2-1] + calcDist(str1[ctr-1], str2[ctr2-1], row_size);
			float left = distanceMatrix[ctr][ctr2-1] + sqrt(mass_center_shift_x_str1[ctr]*mass_center_shift_x_str1[ctr] + mass_center_shift_y_str1[ctr]*mass_center_shift_y_str1[ctr] + time_spacing_str1[ctr-1]*time_spacing_str1[ctr-1]*time_spacing_coeff);
			float above = distanceMatrix[ctr-1][ctr2] + sqrt(mass_center_shift_x_str2[ctr2]*mass_center_shift_x_str2[ctr2] + mass_center_shift_y_str2[ctr2]*mass_center_shift_y_str2[ctr2] + time_spacing_str2[ctr2-1]*time_spacing_str2[ctr2-1]*time_spacing_coeff);
			
			cur_distance = MIN(MIN(diagonal,left),above);
			distanceMatrix[ctr][ctr2] = cur_distance;
		}
	}
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str1len+1; ctr++) {
			printf("%.1f ", mass_center_shift_x_str1[ctr]);
		}
		printf("\n");	
	}
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str1len+1; ctr++) {
			printf("%.1f ", mass_center_shift_y_str1[ctr]);
		}
		printf("\n");	
	}
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str2len+1; ctr++) {
			printf("%.1f ", mass_center_shift_x_str2[ctr]);
		}
		printf("\n");	
	}
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str2len+1; ctr++) {
			printf("%.1f ", mass_center_shift_y_str2[ctr]);
		}
		printf("\n");	
	}
	
	if(DEBUG) {
		for(ctr = 0; ctr < *str1len+1; ctr++) {
			for(ctr2 = 0; ctr2 < *str2len+1; ctr2++) {
				printf("%.1f ", distanceMatrix[ctr][ctr2]);
			}
		printf("\n");
		}	
	}
	
	*result = distanceMatrix[*str1len][*str2len];
	
	for(ctr = 0; ctr < (*str1len)+1; ctr++) {
		free(distanceMatrix[ctr]);
	}
	
	free(distanceMatrix);
	
	free(mass_center_shift_x_str1);
	free(mass_center_shift_y_str1);
	free(mass_center_shift_x_str2);
	free(mass_center_shift_y_str2);
	
	free(time_spacing_str1);
	free(time_spacing_str2);
	
	
	
}


void main() {
	
	// a small test
	int a[4] = {1,1,1,63};
	int b[28] = {52,53,52,51,50,150,149,48,148,48,148,147,247,347,447,448,447,448,447,547,447,446,346,246,247,146,46,47};
	int row_size = 10;
	int len_a = 4;
	int len_b = 28;
	double time_spacing_unit_size = 17.5;
	double result;
	editDistance(a,&len_a,b,&len_b,&row_size,&time_spacing_unit_size,&result);
	
	
}
