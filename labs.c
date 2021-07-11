#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

long int power2(int n, int k)
{
    return n << k;
}

char* intToBit(int n) {
    char * result = malloc(32);
    int i = 0;
    while ((n & 0b10000000000000000000000000000000) == 0) {n <<=1; i++;}
    int j = 0;
    while (i < 32) {
        result[j++] = n & 0b10000000000000000000000000000000 ? '1' : '0';
        i++;
        n <<= 1;
    }
    result[i] = '\0';
    return result;
}

int main(int argc, char *argv[])
{
    if (argc == 1 || argc == 2)
    {
        printf("Input integers to be shifted.\n");
        exit(1);
    }
    int input = atoi(argv[1]);
    int power = atoi(argv[2]);
    printf("Original: %d, %s\n", input, intToBit(input));
    printf("Shifted: %ld, %s\n", power2(input, power),intToBit( power2(input, power)));
}
