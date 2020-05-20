#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void dht11_dat(double *temp, double *humid);
int digitornot(const char *s);
int request(char *strings[], int stringi);
int cmpfunc(const void * a, const void * b);
double numbers(double temp[], double humid[], int tempi, int humi);

int main()
{
	double temperature;
	double humidity;
	dht11_dat(&temperature, &humidity);

	double temp[7] = {1,2,3,4,5,6,7};
	double humi[5] = {0,1,2,5,6};

	numbers(temp,humi,7,5);
	// char *testarray[5] = {"abc","hehe","ree","meeow", "test"};
	// printf("\n%d",request(testarray,5));
	return 0;
}

void dht11_dat(double *temp, double *humid)
{
	// simulated measurements from a DHT11 sensor
	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	timeinfo = localtime( &rawtime );
	double t = timeinfo->tm_hour + timeinfo->tm_min/60.0;

	srand(time(NULL));
	int r = rand();
	double noise = (double) r / RAND_MAX - 0.5; // noise is [-0.5, 0.5]

	*temp = 60 - 20*cos(3.14*t/12) + 2*noise;
	*humid = 70 + 20*cos(3.14*t/12) + 5*noise;
}

int digitornot(const char *s)
{
	while (*s) {
		if (isdigit(*s++) == 0) return 0;
	}
	return 1;
}

int request(char *strings[], int stringi){
	int i;
	char input[10] = {};
	for (i = 0; i < stringi; i++){
		printf("%d. %s\n", i+1, strings[i]);
	}
	fgets(input,10,stdin);
	strtok(input, "\n");

	while (!(digitornot(input)) || (atoi(input) > stringi) || (atoi(input) < 1)){
		for (i = 0; i < stringi; i++){
			printf("%d. %s\n", i+1, strings[i]);
		}
		printf("Please enter a valid number\n");
		fgets(input,10,stdin);
		strtok(input, "\n");
		printf("%s",input);
	}
	return atoi(input);
}

int cmpfunc (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}

double numbers(double temp[], double humi[], int tempi, int humii){
	double tempvar[3] = {}; //for interm calcs
	int i;
	// double values[] = { 88.0001, 56.23, 100.1234, 2, 25 };
	// qsort(values, 5, sizeof(double), cmpfunc);
	qsort(temp,tempi,sizeof(double),cmpfunc);
	qsort(humi,humii,sizeof(double),cmpfunc);
	int selector[3] = {}; //selector with depth up to 3
	char *depth1[] = {"Mean","Five-Number Summary","Mode","Standard Deviation","Skewness","Kurtosis","r","R^2","Least-Squares Regression Line","Quadratic Regression","Sinusoidal Regression"};
	selector[0] = request(depth1,11);
	switch (selector[0])
	{
	case 1:{
		tempvar[0] = 0;
		for (i=0;i<tempi;i++){
			tempvar[0] += temp[i];
		}
		tempvar[0] = tempvar[0]/tempi;
		printf("The mean temperature is %lf.\n",tempvar[0]);
		tempvar[0] = 0;
		for (i=0;i<humii;i++){
			tempvar[0] += humi[i];
		}
		tempvar[0] = tempvar[0]/humii;
		printf("The mean humidity is %lf.\n",tempvar[0]);
		}
		break;
	case 2: {
		tempvar[0] = 0;
		//five-number summary
		double fivenum[5] = {}; 
		//Median
		tempvar[0] = ceil((double)tempi/2);  //the "middle" (btw double forces decimal calculation)
		tempvar[1] = ceil((double)(tempi+1)/2); //one above the middle for even-number sized arrays
		fivenum[2] = (temp[(int) tempvar[0]-1]+temp[(int) tempvar[1]-1])/2; //subtract one for 0 indexing
		//Q1
		tempvar[0] = ceil((double)(ceil((double)(tempi+1)/2)-1)/2); //basically the same logic
		tempvar[1] = ceil((double) ceil((double)(tempi+1)/2)/2); //the left middle of the middle 
		fivenum[1] = (temp[(int) tempvar[0]-1]+temp[(int) tempvar[1]-1])/2; //again subtract 1 for index
		//Q3
		tempvar[0] = ceil((double)(ceil((double)(tempi+1)/2)-1)/2) + ceil((double)tempi/2);
		tempvar[1] = ceil((double)ceil((double)(tempi+1)/2)/2) + ceil((double)tempi/2);
		fivenum[3] = (temp[(int) tempvar[0]-1]+temp[(int) tempvar[1]-1])/2;
		//Min
		fivenum[0] = temp[0];
		//Max
		fivenum[4] = temp[tempi-1];
		printf("The five-number summary for temperature is {%lf,%lf,%lf,%lf,%lf}\n",fivenum[0],fivenum[1],fivenum[2],fivenum[3],fivenum[4]);
		tempvar[0] = ceil((double)humii/2);  //the "middle"
		tempvar[1] = ceil((double)(humii+1)/2); //one above the middle for even-number sized arrays
		fivenum[2] = (humi[(int) tempvar[0]-1]+humi[(int) tempvar[1]-1])/2; //subtract one for 0 indexing
		//Q1
		tempvar[0] = ceil((double)(ceil((double)(humii+1)/2)-1)/2); //basically the same logic
		tempvar[1] = ceil((double) ceil((double)(humii+1)/2)/2); //the left middle of the middle 
		fivenum[1] = (humi[(int) tempvar[0]-1]+humi[(int) tempvar[1]-1])/2; //again subtract 1 for index
		//Q3
		tempvar[0] = ceil((double)(ceil((double)(humii+1)/2)-1)/2) + ceil((double)humii/2);
		tempvar[1] = ceil((double)ceil((double)(humii+1)/2)/2) + ceil((double)humii/2);
		fivenum[3] = (humi[(int) tempvar[0]-1]+humi[(int) tempvar[1]-1])/2;
		//Min
		fivenum[0] = humi[0];
		//Max
		fivenum[4] = humi[humii-1];
		printf("The five-number summary for humidity is {%lf,%lf,%lf,%lf,%lf}\n",fivenum[0],fivenum[1],fivenum[2],fivenum[3],fivenum[4]);
		}
		break;
	
	// default:
	// 	break;
	}
	
	// int i;
	// for( i = 0 ; i < 5; i++ ) {   
    //   printf("%f ", values[i]);
   	// }
	return 0;
}