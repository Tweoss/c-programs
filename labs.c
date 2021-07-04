#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define CONTINUE 0
#define LOSS 1
#define WIN 2

int main(int argc, char *argv[])
{
    float count[5][6] = {0};

    printf("Enter salesperson 0 to stop.\n");
    uint32_t person = 0, product = 0;
    float dollar_value = 0.;
    while (true)
    {
        printf("Person #: ");
        scanf("%d", &person);
        if (person == 0 || person > 4)
        {
            break;
        }
        printf("Product #: ");
        scanf("%d", &product);
        if (product == 0 || product > 5)
        {
            break;
        }
        printf("Dollar Value: ");
        scanf("%f", &dollar_value);
        count[person - 1][product - 1] += dollar_value;
    }
    // sum rows, columns
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            count[4][j] += count[i][j];
            count[i][5] += count[i][j];
            count[4][5] += count[i][j];
        }
    }
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            printf("%f\t", count[i][j]);
        }
        printf("\n");
    }
}
