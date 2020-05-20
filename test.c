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
void mean(double array[], int arrayi, const char *s);
void fivennum(double array[], int size, const char *s);
double numbers(double temp[], double humid[], int tempi, int humi);

int main()
{
	double temperature;
	double humidity;
	dht11_dat(&temperature, &humidity);

	double temp[22] = {1,1,1,2,2,2,2,3,3,3,3,4,5,6,7,8,8,8,8,9,9,9};
	double humi[5]  = {0,1,2,5,6};
	// printf("%lu",sizeof(temp)/sizeof(double));
	numbers(temp,humi,22, 5); //sizeof(temp),sizeof(humi));
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

void mean(double array[], int arrayi, const char *s){
	double tempvar = 0;
	int i;
	for (i=0;i<arrayi;i++){
		tempvar += array[i];
	}
	tempvar = tempvar/arrayi;
	printf("The mean %s is %lf.\n",s,tempvar);
}

void fivenum(double array[], int size, const char *s){
	double tempvar[2];
	double summary[5];
	//Median
	tempvar[0] = ceil((double) size   /2); //the "middle" (btw double forces decimal calculation)
	tempvar[1] = ceil((double)(size+1)/2); //one above the middle for even-number sized arrays
	summary[2] = (array[(int) tempvar[0]-1]+array[(int) tempvar[1]-1])/2; //subtract one for 0 indexing
	//Q1
	tempvar[0] = ceil((double)(ceil((double)(size+1)/2)-1)/2); //basically the same logic
	tempvar[1] = ceil((double) ceil((double)(size+1)/2)   /2); //the left middle of the middle 
	summary[1] = (array[(int) tempvar[0]-1]+array[(int) tempvar[1]-1])/2; //again subtract 1 for index
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

double numbers(double temp[] , double humi[], int tempi, int humii){
	double tempvar[4] = {}; //for interm calcs
	int i; //arbitrary index
	qsort(temp,tempi,sizeof(double),cmpfunc);
	qsort(humi,humii,sizeof(double),cmpfunc);
	int selector[3] = {}; //selector with depth up to 3
	char *depth1[] = {"Mean","Five-Number Summary","Mode","Standard Deviation","Skewness","Kurtosis","r","R^2","Least-Squares Regression Line","Quadratic Regression","Sinusoidal Regression"};
	selector[0] = request(depth1,11);
	switch (selector[0])
	{
	//MEAN
	case 1:{
		mean(temp,tempi,"temperature");
		mean(humi,humii,"humidity");
		}
		break;
	//FIVE-NUMBER SUMMARY
	case 2: {
		fivenum(temp,tempi,"temperature");
		fivenum(humi,humii,"humidity");
		// tempvar[0] = 0;
		// double fivenum[5] = {}; 
		// {
		// //five-number summary
		// //Median
		// tempvar[0] = ceil((double)tempi/2);  //the "middle" (btw double forces decimal calculation)
		// tempvar[1] = ceil((double)(tempi+1)/2); //one above the middle for even-number sized arrays
		// fivenum[2] = (temp[(int) tempvar[0]-1]+temp[(int) tempvar[1]-1])/2; //subtract one for 0 indexing
		// //Q1
		// tempvar[0] = ceil((double)(ceil((double)(tempi+1)/2)-1)/2); //basically the same logic
		// tempvar[1] = ceil((double) ceil((double)(tempi+1)/2)/2); //the left middle of the middle 
		// fivenum[1] = (temp[(int) tempvar[0]-1]+temp[(int) tempvar[1]-1])/2; //again subtract 1 for index
		// //Q3
		// tempvar[0] = ceil((double)(ceil((double)(tempi+1)/2)-1)/2) + ceil((double)tempi/2);
		// tempvar[1] = ceil((double)ceil((double)(tempi+1)/2)/2) + ceil((double)tempi/2);
		// fivenum[3] = (temp[(int) tempvar[0]-1]+temp[(int) tempvar[1]-1])/2;
		// //Min
		// fivenum[0] = temp[0];
		// //Max
		// fivenum[4] = temp[tempi-1];
		// printf("The five-number summary for temperature is {%lf,%lf,%lf,%lf,%lf}.\n",fivenum[0],fivenum[1],fivenum[2],fivenum[3],fivenum[4]);
		// }
		// {
		// tempvar[0] = ceil((double)humii/2);  //the "middle"
		// tempvar[1] = ceil((double)(humii+1)/2); //one above the middle for even-number sized arrays
		// fivenum[2] = (humi[(int) tempvar[0]-1]+humi[(int) tempvar[1]-1])/2; //subtract one for 0 indexing
		// //Q1
		// tempvar[0] = ceil((double)(ceil((double)(humii+1)/2)-1)/2); //basically the same logic
		// tempvar[1] = ceil((double) ceil((double)(humii+1)/2)/2); //the left middle of the middle 
		// fivenum[1] = (humi[(int) tempvar[0]-1]+humi[(int) tempvar[1]-1])/2; //again subtract 1 for index
		// //Q3
		// tempvar[0] = ceil((double)(ceil((double)(humii+1)/2)-1)/2) + ceil((double)humii/2);
		// tempvar[1] = ceil((double)ceil((double)(humii+1)/2)/2) + ceil((double)humii/2);
		// fivenum[3] = (humi[(int) tempvar[0]-1]+humi[(int) tempvar[1]-1])/2;
		// //Min
		// fivenum[0] = humi[0];
		// //Max
		// fivenum[4] = humi[humii-1];
		// printf("The five-number summary for humidity is {%lf,%lf,%lf,%lf,%lf}.\n",fivenum[0],fivenum[1],fivenum[2],fivenum[3],fivenum[4]);
		// }
		}
		break;
	//MODE
	case 3: {
		tempvar[0] = 0; //kinda useless but eh
		double mode[tempi/2];//the mode(s)
		int modii; //the current index of the mode
		{
		//set tempvar to max
		// if (tempi > humii){tempvar[0] = tempi/2;} else {tempvar[0] = humii/2;}
		// double mode[(int) tempvar[0]];//the mode(s)

		
		// (which by this method can be at most 1/2 of total #elements)
		//note: this will multiple modes (if they exist)
		memset(mode, 0, sizeof(mode));
		modii = 0;
		tempvar[1] = 0;	// stores the score of the highscore
		tempvar[2] = 0;	//stores the current #
		tempvar[3] = 0;	// stores the score of current #
		for (i=0;i<tempi;i++){
			// printf("LOOP");
			if (tempvar[2] != temp[i]){ //New number
				tempvar[2] = temp[i]; //store new current #
				tempvar[3] = 1; //store new score (1)
				// printf("NEW: %lf,%d\n",tempvar[2],i);
			}
			else { //Not new number
				tempvar[3]++; //increase current score

				if (tempvar[3] > tempvar[1]){ // if greater than highscore
					memset(mode, 0, sizeof(mode));

					tempvar[1] = tempvar[3];
					// printf("NEW HIGH: %lf,%d\n",tempvar[2],(int)tempvar[1]);
					mode[0] = tempvar[2];
					modii = 1; 
				} else 
				if (tempvar[3] == tempvar[1]){ // if equals the highscore
					// tempvar[0] = tempvar[2];
					mode[modii] = tempvar[2];
					modii++;
					// printf("ANOT HIGH: %lf,%d\n",tempvar[2],(int)tempvar[1]);
				}
			}
		}
		if (!((int) tempvar[1])){ // if there are no modes
			printf("There are no modes for temperature.");
			break;
		} 
		printf("The mode(s) for temperature are {");
		printf("%lf",mode[0]);
		for (i=1;i<modii;i++){
			printf(",%lf",mode[i]);
		}
		printf("} with multiplicity %d.\n",(int)tempvar[1]);
		}
		{
		// (which by this method can be at most 1/2 of total #elements)
		//note: this will return multiple modes (if they exist)
		memset(mode, 0, sizeof(mode));
		modii = 0;
		tempvar[1] = 0;	// stores the score of the highscore
		tempvar[2] = 0;	//stores the current #
		tempvar[3] = 0;	// stores the score of current #
		for (i=0;i<humii;i++){
			if (tempvar[2] != humi[i] || !(tempvar[1])){ //New number
				tempvar[2] = humi[i]; //store new current #
				tempvar[3] = 1; //store new score (1)
				// printf("NEW: %lf,%d\n",tempvar[2],i);
			}
			else { //Not new number
				tempvar[3]++; //increase current score
				printf("\nREE: %lf =? %lf\n",tempvar[2],humi[i]);

				if (tempvar[3] > tempvar[1]){ // if greater than highscore
					memset(mode, 0, sizeof(mode));

					printf("\n\nNEW HIGH: %lf,%d,%d\n",tempvar[2],(int)tempvar[1],(int)tempvar[3]);
					tempvar[1] = tempvar[3];
					mode[0] = tempvar[2];
					modii = 1; // 
				} else 
				if (tempvar[3] == tempvar[1]){ // if equals the highscore
					// tempvar[0] = tempvar[2];
					mode[modii] = tempvar[2];
					modii++;
					// printf("ANOT HIGH: %lf,%d\n",tempvar[2],(int)tempvar[1]);
				}
			}
		}
		if (!((int) tempvar[1])){ // if there are no modes
			printf("There are no modes for humidity.");
			break;
		} 
		printf("The mode(s) for humidity are {");
		printf("%lf",mode[0]);
		for (i=1;i<modii;i++){
			printf(",%lf",mode[i]);
		}
		// printf("%lf",tempvar[1]);
		printf("} with multiplicity %d.",(int)tempvar[1]);
		}
		}
		break;
	case 4: {

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