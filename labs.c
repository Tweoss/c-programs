#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct Point
{
    double x;
    double y;
};

double distance(struct Point a, struct Point b)
{
    return sqrt(pow(a.x - b.x, 2.) + pow(a.y - b.y, 2.));
}

int main(int argc, char *argv[])
{
    struct Point a, b;

    a.x = atof(argv[1]);
    a.y = atof(argv[2]);
    b.x = atof(argv[3]);
    b.y = atof(argv[4]);

    printf("%f\n", distance(a, b));
}
