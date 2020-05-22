#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void dht11_dat(double *temp, double *humid);
int main()
{
double temperature;
double humidity;
dht11_dat(&temperature, &humidity);
printf("%f\n", temperature);
printf("%f\n", humidity);
dht11_dat(&temperature, &humidity);
printf("%f\n", temperature);
printf("%f\n", humidity);
dht11_dat(&temperature, &humidity);
printf("%f\n", temperature);
printf("%f\n", humidity);
dht11_dat(&temperature, &humidity);
printf("%f\n", temperature);
printf("%f\n", humidity);
dht11_dat(&temperature, &humidity);
printf("%f\n", temperature);
printf("%f\n", humidity);

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