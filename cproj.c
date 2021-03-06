#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void dht11_dat(double *temp, double *humid);
int digitornot(const char *s);
int requ(char *strings[], int stringi);
int cmpfunc(const void * a, const void * b);
double mean(double array[], int arrayi, const char *s, bool shouldDisplay);
void five(double array[], int size, const char *s);
void numbers(double temp[], double humid[], int tempi, int humi);
double stdd(double array[], int arrayi, const char*s, bool shouldDisplay, int adjust);
double skew(double array[], int arrayi, const char*s, bool shouldDisplay);
double kurt(double array[], int arrayi, const char*s);
double corr(double temp[], double humi[], int tempi, int humii, bool shouldDisplay);
double cors(double temp[], double humi[], int tempi, int humii, bool shouldDisplay);
void   lsrl(double temp[], double humi[], int tempi, int humii, bool shouldDisplay);
void	*matmul(int arow, int acol, int brow, int bcol, double a[arow][acol], double b[brow][bcol]);
void	*mattra(int arow, int acol, double a[arow][acol]);


int main()
{
	double temperature;
	double humidity;
	dht11_dat(&temperature, &humidity);

	double temp[6] = {3, 8, 10, 17, 24, 27};
	double humi[7] = {2, 2, 8, 10, 13, 18, 20};

	double mata[4][3] = {{1,0,0},{0,2,3},{5,7,9},{5,5,5}};
	double matb[3][3] = {{1,0,0},{0,1,0},{0,2,-1}};
	//identity matrix (4x4)
	double iden[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

	// for (size_t i = 0; i < n; ++i)
	// 	for (size_t j = 0; j < n; ++j)
	// 		A[i][j] = someinvolvedfunction(i, j);

	// double (*c)[3] = matmul(3,3,3,3,mata,matb);

	//second number is num of columns
	double (*c)[4] = mattra(4,3,mata);
/*
	int i,j; //arbitrary index
	// printf("HEY:\n");
	for (i=0;i<4;i++){
		for (j=0;j<3;j++){
			printf("%f, ",c[j][i]);
		}
		// printf("\n");
	}
	// printf("\n");
	free(c);
*/
	numbers(temp,humi,sizeof(temp)/sizeof(double), sizeof(humi)/sizeof(double)); //sizeof(temp),sizeof(humi));
	return 0;
}
//generates random data
void	 dht11_dat(double *temp, double *humid)
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
int		 digitornot(const char *s)
{
	while (*s) {
		if (isdigit(*s++) == 0) return 0;
	}
	return 1;
}
//displays options, returns the selected
int		 requ(char *strings[], int stringi){
	int i;
	char input[10] = {};
	for (i = 0; i < stringi; i++){
		printf("%d. %s\n", i+1, strings[i]);
	}
	fgets(input,10,stdin);
	strtok(input, "\n");

	while (!(digitornot(input)) || (atoi(input) > stringi) || (atoi(input) < 0)){
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
int		 cmpfunc (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}
//data loading 
void    *dataload(const char *s,int numofdoubles){
    double buffer[numofdoubles*8];
    FILE *ptr = fopen(s,"rb");
    int bytecount; //the total number of bytes in the file
    int byte; //the current byte
    int i; //arbitrary index
    do {
      byte = fgetc(ptr);
      if( feof(ptr) ) {
         break ;
      }
      bytecount++;
   } while(1);
   if (!(bytecount > sizeof(buffer)/sizeof(double))){
       ptr = fopen(s,"rb");
       for (i=0; i<numofdoubles*sizeof(double);i++){
           buffer[i] = fgetc(ptr);
       }
   }
   else {
       printf("Error: Not enough buffer size.\n");
   }
   return ptr;
}
//matrix multiplication A*B

//matrix transpose A^(T)
void	*mattra(int arow, int acol, double a[arow][acol]){
	int i, j;//arbitrary index
	double (*c)[arow] = malloc(sizeof(double[acol][arow]));
	for (i=0;i<arow;i++){ // These two lines loop through the
		for (j=0;j<acol;j++){ // elements of the input matrix
			c[j][i] = a[i][j];
			printf("%f,%d,%d\n ",c[j][i],j,i);
		}
	}
	return c;
}
// //matrix determinant finding (specifically 4x4)
// double	 matdet(int arow, int acol, double a[arow][acol]){
// 	return a[0][0]*(0				 +
// 			(a[1][1]*a[2][2]*a[3][3])+
// 			(a[1][2]*a[2][3]*a[3][0])+
// 			(a[1][3]*a[2][1]*a[3][2])-
// 			(a[1][1]*a[2][3]*a[3][2])-
// 			(a[1][2]*a[2][1]*a[3][3])-
// 			(a[1][3]*a[2][2]*a[3][1])-
// 		)
// 		-a[0][1]*(0				 +
// 			(a[0][1]*a[2][2]*a[3][3])+
// 			(a[0][2]*a[2][3]*a[3][0])+
// 			(a[0][3]*a[2][1]*a[3][2])-
// 			(a[0][1]*a[2][3]*a[3][2])-
// 			(a[0][2]*a[2][1]*a[3][3])-
// 			(a[0][3]*a[2][2]*a[3][1])-
// 		)
// 		+a[0][2]*(0				 +
// 			(a[1][1]*a[0][2]*a[3][3])+
// 			(a[1][2]*a[0][3]*a[3][0])+
// 			(a[1][3]*a[0][1]*a[3][2])-
// 			(a[1][1]*a[0][3]*a[3][2])-
// 			(a[1][2]*a[0][1]*a[3][3])-
// 			(a[1][3]*a[0][2]*a[3][1])-
// 		)
// 		-a[0][3]*(0				 +
// 			(a[1][1]*a[2][2]*a[0][3])+
// 			(a[1][2]*a[2][3]*a[0][0])+
// 			(a[1][3]*a[2][1]*a[0][2])-
// 			(a[1][1]*a[2][3]*a[0][2])-
// 			(a[1][2]*a[2][1]*a[0][3])-
// 			(a[1][3]*a[2][2]*a[0][1])-
// 		);
// }
//trace calculator (4x4)
// double	 matrac(int arow, int acol, double a[arow][acol]){
// 	double tempvar = 1;
// 	int i;
// 	for 
// }
//matrix inverse finding (4x4)

//calculates mean
double	 mean(double array[], int arrayi, const char *s, bool shouldDisplay){
	double tempvar = 0;
	int i;
	for (i=0;i<arrayi;i++){
		tempvar += array[i];
	}
	tempvar = tempvar/arrayi;
	if (shouldDisplay){
		printf("The mean %s is %f.\n",s,tempvar);
	}
	return tempvar;
}
//calculates five-number summary
void	 fivenum(double array[], int size, const char *s){
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
	printf("The five-number summary for %s is {%f,%f,%f,%f,%f}.\n",s,summary[0],summary[1],summary[2],summary[3],summary[4]);
}
//caluculates mode(s)
void	 mode(double array[], int size, const char *s){
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
	printf("%f",mode[0]);
	for (i=1;i<modii;i++){
		printf(",%f",mode[i]);
	}
	printf("} with multiplicity %d.\n",(int)tempvar[0]);
	}
}
//calculates standard deviation
double	 stdd(double array[], int arrayi, const char*s, bool shouldDisplay, int adjust){
	double tempvar[2] = {};
	tempvar[1] = mean(array,arrayi,NULL,0);
	int i;
	for (i=0;i<arrayi;i++){
		tempvar[0] += pow(array[i]-tempvar[1],2);
	}
	tempvar[0] = sqrt(tempvar[0]/(arrayi-adjust));
	if (shouldDisplay){
		printf("The sample standard deviation of %s is %f.\n",s,tempvar[0]);
	}
	return tempvar[0];
}
//calculates skewness (adjusted Fisher-Pearson standardized moment coefficient)
double	 skew(double array[], int arrayi, const char*s, bool shouldDisplay){
	double tempvar[3] = {};
	tempvar[1] = mean(array,arrayi,NULL,0);
	tempvar[2] = stdd(array,arrayi,NULL,0,0);
	int i;
	for (i=0;i<arrayi;i++){
		tempvar[0] += pow(array[i]-tempvar[1],3);
	}
	tempvar[0] /= sqrt(arrayi*(arrayi-1))/(arrayi-2)/(arrayi)/pow(tempvar[2],3);
	if (shouldDisplay){
		printf("The skewness for the %s distribution is %f\n",s,tempvar[0]);
	}
	return tempvar[0];
}
//calculates excess kurtosis (kurtosis-3)
double	 kurt(double array[], int arrayi, const char*s) {
	double tempvar[3] = {};
	tempvar[1] = mean(array,arrayi,NULL,0);
	tempvar[2] = stdd(array,arrayi,NULL,0,0);
	int i;
	for (i=0;i<arrayi;i++){
		tempvar[0] += pow(array[i]-tempvar[1],4);
	}
	tempvar[0] /= (arrayi*pow(tempvar[2],4))-3;
	
	printf("The excess kurtosis for the %s distribution is %f\n",s,tempvar[0]);
	
	return tempvar[0];
}
//calculates r
double	 corr(double temp[], double humi[], int tempi, int humii, bool shouldDisplay){
    double tempvar[4] = {};
    tempvar[0] = mean(temp,tempi,NULL,0);
    tempvar[1] = mean(humi,humii,NULL,0);
    tempvar[2] = stdd(temp,tempi,NULL,0,1);
    tempvar[3] = stdd(humi,humii,NULL,0,1);
    // printf("%f, %f, %f, %f\n",tempvar[0],tempvar[1],tempvar[2],tempvar[3]);
    double r = 0;
    int i;
    if (tempi == humii){
        for (i=0;i<tempi;i++) {
            r += (temp[i]-tempvar[0])/tempvar[2]*(humi[i]-tempvar[1])/tempvar[3];
            // printf("%f, ",r);
        }
        r /= tempi-1;
        if (shouldDisplay){
            printf("The correlation between temperature and humidity is %f.\n",r);
        }
        return r;
    }
    else {
        printf("Error: There must be the same number of humidity and temperature readings.\n");
        return 0;
    }

}
//calculates r^2
double	 cors(double temp[], double humi[], int tempi, int humii, bool shouldDisplay){
    double vartemp;
    vartemp = pow(corr(temp,humi,tempi,humii,0),2);
    if (shouldDisplay){
        printf("The r^2, the percentage of variation in humidity explained by the variation in temperature or vice versa, is %f.\n",vartemp);
    }
    return vartemp;
}
//calculates the least-squares regression line
void	 lsrl(double temp[], double humi[], int tempi, int humii, bool shouldDisplay){
    double tempvar[2];
    tempvar[0] = corr(temp,humi,tempi,humii,0)*stdd(humi,humii,NULL,0,1)/stdd(temp,tempi,NULL,0,1);
    tempvar[1] = mean(humi,humii,NULL,0) - tempvar[0]*mean(temp,tempi,NULL,0);
    if (shouldDisplay){
        corr(temp,humi,tempi,humii,1);cors(temp,humi,tempi,humii,1);
        printf("The least-squares regression line for the effect of temperature on humidity is y = %f*x + %f.\n",tempvar[0],tempvar[1]);
    }
}
//calculates the least-squares regression quadratic
void	 lsrq(double temp[], double humi[], int tempi, int humii, bool shouldDisplay){

}

void numbers(double temp[] , double humi[], int tempi, int humii){
	double tempvar[4] = {}; //for interm calcs
	qsort(temp,tempi,sizeof(double),cmpfunc);
	qsort(humi,humii,sizeof(double),cmpfunc);

	int selector[3] = {}; //selector with depth up to 3 (prob only use 1)
	char *depth1[] = {"Mean","Five-Number Summary","Mode","Standard Deviation","Skewness","Kurtosis","Least-Squares Regression Line","Quadratic Regression","Sinusoidal Regression"};
	selector[0] = requ(depth1,9);

	int i, j; //arbitrary index

	switch (selector[0])
	{
	//MEAN
	case 1:{
		mean(temp,tempi,"temperature",1);
		mean(humi,humii,"humidity"   ,1);
		break;
	}
	//FIVE-NUMBER SUMMARY
	case 2: {
		fivenum(temp,tempi,"temperature");
		fivenum(humi,humii,"humidity");
		break;
	}
	//MODE
	case 3: {
		mode(temp,tempi,"temperature");
		mode(humi,humii,"humidity");
		break;
	}
	//STD. DEV.
	case 4: {
		stdd(temp,tempi,"temperature",1,1);
		stdd(humi,humii,"humidity"   ,1,1);
		break;
	}
	//SKEWNESS
	case 5: {
		skew(temp,tempi,"temperature",1);
		skew(humi,humii,"humidity"   ,1);
		break;
	}
	//KURTOSIS
	case 6: {
		kurt(temp,tempi,"temperature");
		kurt(humi,humii,"humidity"   );
		break;
	}
    //LSRL
    case 7: {
        lsrl(temp,humi,tempi,humii,1);
        break;
    }

	// default:
	// 	break;
	}

}