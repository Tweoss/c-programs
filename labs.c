#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // minimizing # of printf statements. Use conditionals to determine whether character should be newline, space, or star
            printf("%c", i + j < 4 || j - i > 4 || i + j > 12 || i - j > 4  ? j == 9 ? '\n' :' ' : '*');
        }
    }
}
