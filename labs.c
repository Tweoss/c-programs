#include <stdio.h>
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		char *input = argv[1];
		int decimal = 0;
		int i;
		for (i = 0; input[i] != '\0'; i++)
		{
			decimal = decimal << 1;
			if (input[i] == '1')
			{
				// do power by shifting to the left.
				decimal += 1;
			}
		}
		printf("Decimal: %d\n", decimal);
		printf("Hex: ");
		// increment chunks based off the initial_offset
		int initial_offset = i%4;
		for (int j = initial_offset - 4; j < i; j += 4)
		{
			int hex_temp = 0;
			for (int k = j; k < j + 4; k++)
			{
					hex_temp = hex_temp << 1;
				if (k < 0) {
					continue;
				}
				else if (input[k] == '\0') {
					break;
				} else if (input[k] == '1')
				{
					hex_temp += 1;
				}
			}
			if (hex_temp < 10)
			{
				printf("%d", hex_temp);
			}
			else
			{
				switch (hex_temp)
				{
				case 10:
					printf("A");
					break;
				case 11:
					printf("B");
					break;
				case 12:
					printf("C");
					break;
				case 13:
					printf("D");
					break;
				case 14:
					printf("E");
					break;
				case 15:
					printf("F");
					break;
				}
			}
		}
		printf("\n");
	}
	return 0;
}