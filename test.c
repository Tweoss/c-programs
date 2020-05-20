#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void dht11_dat(double *temp, double *humid);
double numbers(double temp[], double humid[], int tempi, int humi);
int request(char *strings[], int stringi);
int digitornot(const char *s);

int main()
{
	double temperature;
	double humidity;
	dht11_dat(&temperature, &humidity);
	printf("%lf\n", temperature);
	printf("%lf\n", humidity);
	dht11_dat(&temperature, &humidity);
	printf("%lf\n", temperature);
	printf("%lf\n", humidity);
	dht11_dat(&temperature, &humidity);
	printf("%lf\n", temperature);
	printf("%lf\n", humidity);
	dht11_dat(&temperature, &humidity);
	printf("%lf\n", temperature);
	printf("%lf\n", humidity);
	char *ree[5] = {"abc","hehe","ree","meeow", "test"};
	printf("\n%d",request(ree,5));
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
	char input[3] = {};
	for (i = 0; i < stringi; i++){
		printf("%d. %s\n", i+1, strings[i]);
	}
	fgets(input,3,stdin);
	strtok(input, "\n");
	printf("---%s---",input);
	while (!(digitornot(input) && !(atoi(input) > stringi) && !(atoi(input) < 1))){
		printf("Please enter a valid number\n");
		for (i = 0; i < stringi; i++){
			printf("%d. %s\n", i+1, strings[i]);
		}
		fgets(input,3,stdin);
		strtok(input, "\n");
	}
	return atoi(input);
}

double numbers(double temp[], double humid[], int tempi, int humi){
	printf("%f",temp[1]);
	return temp[1];
}