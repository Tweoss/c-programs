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

	double temp[3];
	double humi[3];

	numbers(temp,humi,3,3);
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
	// double values[] = { 88.0001, 56.23, 100.1234, 2, 25 };
	// qsort(values, 5, sizeof(double), cmpfunc);
	qsort(temp,tempi,sizeof(double),cmpfunc);
	qsort(humi,humii,sizeof(double),cmpfunc);
	int selector[3] = {}; //selector with depth up to 5
	char *depth1[] = {"Mean","Median","Mode","Standard Deviation","Skewness","Kurtosis","r","R^2","Least-Squares Regression Line","Quadratic Regression","Sinusoidal Regression"};
	selector[0] = request(depth1,11);
	
	// int i;
	// for( i = 0 ; i < 5; i++ ) {   
    //   printf("%f ", values[i]);
   	// }
	return 0;
}