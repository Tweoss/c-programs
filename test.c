#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void dht11_dat(double *temp, double *humid);
int digitornot(const char *s);
int request(char *strings[], int stringi);
int cmpfunc(const void * a, const void * b);
double mean(double array[], int arrayi, const char *s, bool shouldDisplay);
void fivennum(double array[], int size, const char *s);
void numbers(double temp[], double humid[], int tempi, int humi);
double stdd(double array[], int arrayi, const char*s, bool shouldDisplay);


int main()
{
	double temperature;
	double humidity;
	dht11_dat(&temperature, &humidity);

	double temp[22] = {1,1,1,2,2,2,2,3,3,3,3,4,5,6,7,8,8,8,8,9,9,9};
	double humi[5]  = {0,1,2,5,6};

	numbers(temp,humi,sizeof(temp)/sizeof(double), sizeof(humi)/sizeof(double)); //sizeof(temp),sizeof(humi));
	return 0;
}
//generates random data
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
//checks if input string is integer
int digitornot(const char *s)
{
	while (*s) {
		if (isdigit(*s++) == 0) return 0;
	}
	return 1;
}
//displays options, returns the selected
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
//for qsorting
int cmpfunc (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}
//calculates mean
double mean(double array[], int arrayi, const char *s, bool shouldDisplay){
	double tempvar = 0;
	int i;
	for (i=0;i<arrayi;i++){
		tempvar += array[i];
	}
	tempvar = tempvar/arrayi;
	if (shouldDisplay){
		printf("The mean %s is %lf.\n",s,tempvar);
	}
	return tempvar;
}
//calculates five-number summary
void fivenum(double array[], int size, const char *s){
	double tempvar[2];
	double summary[5];
	//Median
	tempvar[0] = ceil((double) size   /2); //the "middle" (btw double forces decimal calculation)
	tempvar[0] = ceil((double)(size+1)/2); //one above the middle for even-number sized arrays
	summary[2] = (array[(int) tempvar[0]-1]+array[(int) tempvar[0]-1])/2; //subtract one for 0 indexing
	//Q1
	tempvar[0] = ceil((double)(ceil((double)(size+1)/2)-1)/2); //basically the same logic
	tempvar[0] = ceil((double) ceil((double)(size+1)/2)   /2); //the left middle of the middle 
	summary[1] = (array[(int) tempvar[0]-1]+array[(int) tempvar[0]-1])/2; //again subtract 1 for index
	//Q3
	tempvar[0] = ceil((double)(ceil((double)(size+1)/2)-1)/2) + ceil((double)size/2);
	tempvar[1] = ceil((double) ceil((double)(size+1)/2)   /2) + ceil((double)size/2);
	summary[3] = (array[(int) tempvar[0]-1]+array[(int) tempvar[1]-1])/2;
	//Min
	summary[0] = array[0];
	//Max
	summary[4] = array[size-1];
	printf("The five-number summary for %s is {%lf,%lf,%lf,%lf,%lf}.\n",s,summary[0],summary[1],summary[2],summary[3],summary[4]);
}
//caluculates mode(s)
void mode(double array[], int size, const char *s){
	double mode[size/2];//the mode(s)
	memset(mode, 0, sizeof(mode));
	int i;
	// (which by this method can be at most 1/2 of total #elements)
	//note: this will return multiple modes (if they exist)
	int modii = 0; //the current index of the mode
	double tempvar[3];
	// memset(mode, 0, sizeof(mode));
	// modii = 0;
	tempvar[0] = 0;	// stores the score of the highscore
	tempvar[1] = 0;	//stores the current #
	tempvar[2] = 0;	// stores the score of current #
	for (i=0;i<size;i++){
		if ((tempvar[1] != array[i]) || (i==0)){ //New number
			tempvar[1] = array[i]; //store new current #
			tempvar[2] = 1; //store new score (1)
		}
		else { //Not new number
			tempvar[2]++; //increase current score

			if (tempvar[2] > tempvar[0]){ // if greater than highscore
				memset(mode, 0, sizeof(mode));

				tempvar[0] = tempvar[2];
				mode[0] = tempvar[1];
				modii = 1; 
			} else 
			if (tempvar[2] == tempvar[0]){ // if equals the highscore
				mode[modii] = tempvar[1];
				modii++;
			}
		}
	}
	if (!((int) tempvar[0])){ // if there are no modes
		printf("There are no modes for %s.\n",s);
	}
	else {	
	printf("The mode(s) for %s are {",s);
	printf("%lf",mode[0]);
	for (i=1;i<modii;i++){
		printf(",%lf",mode[i]);
	}
	printf("} with multiplicity %d.\n",(int)tempvar[0]);
	}
}
//calculates standard deviation
double stdd(double array[], int arrayi, const char*s, bool shouldDisplay){
	double tempvar = 0;
	int i;
	mean(array,arrayi,s,0);
	for (i=0;i<arrayi;i++){
		tempvar += pow(array[i]-mean(array,arrayi,NULL,0),2);
	}
	tempvar = sqrt(tempvar/(arrayi-1));
	if (shouldDisplay){
		printf("The sample standard deviation of %s is %lf.\n",s,tempvar);
	}
	return tempvar;
}
//calculates skewness


void numbers(double temp[] , double humi[], int tempi, int humii){
	double tempvar[4] = {}; //for interm calcs
	qsort(temp,tempi,sizeof(double),cmpfunc);
	qsort(humi,humii,sizeof(double),cmpfunc);

	int selector[3] = {}; //selector with depth up to 3 (prob only use 1)
	char *depth1[] = {"Mean","Five-Number Summary","Mode","Standard Deviation","Skewness","Kurtosis","r","R^2","Least-Squares Regression Line","Quadratic Regression","Sinusoidal Regression"};
	selector[0] = request(depth1,11);

	int i, j; //arbitrary index
	// double calcval[2][2]; //mean, stddev (avoid recalc)

	switch (selector[0])
	{
	//MEAN
	case 1:{
		mean(temp,tempi,"temperature",1);
		mean(humi,humii,"humidity"   ,1);
	}
		break;
	//FIVE-NUMBER SUMMARY
	case 2: {
		fivenum(temp,tempi,"temperature");
		fivenum(humi,humii,"humidity");
	}
		break;
	//MODE
	case 3: {
		mode(temp,tempi,"temperature");
		mode(humi,humii,"humidity");
	}
		break;
	//STD. DEV.
	case 4: {
		stdd(temp,tempi,"temperature",1);
		stdd(humi,humii,"humidity"   ,1);
	}
		break;
	//SKEWNESS
	case 5: {

	}
		break;

	// default:
	// 	break;
	}
	/*RERUN????*/
	// char *cont[] = {"Stop","Continue"};
	// if (request(cont,2)-1){
	// 	numbers(temp,humi,tempi,humii);
	// }

}