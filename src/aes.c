#include <stdio.h>

#define NUM_ROWS 4
#define NUM_COLS 4


int ConcatVar(int m, int n)
{
	int pow = 10;
	while (n >= pow)
		pow *= 10;
	return m * pow + n;
}

void ShiftRows(int InBlock[NUM_ROWS][NUM_COLS])
{
	
}

void CreateArray(int InBlock[NUM_ROWS][NUM_COLS])
{	
	int m, n;

	for (m = 0; m < NUM_ROWS; m++)
	{
		for (n = 0; n < NUM_COLS; n++)
		{	
			InBlock[m][n] = ConcatVar(m, n);
			printf("%d ", InBlock[m][n]);
		}
		printf("\n");
	}

	ShiftRows(InBlock);
}


int main(void)
{
	int InBlock[NUM_ROWS][NUM_COLS];
	
	CreateArray(InBlock);
}
