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

void MixColumns(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS])
{

}

void ShiftRows(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS])
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			if (m % 2 == 0)
				State[m][n] = InBlock[m][((n + m) % NUM_COLS)];
			else if (m % 2 == 1)
				State[m][n] = InBlock[m][((n + (m + (NUM_COLS / 2))) % NUM_COLS)];	
			printf("%d ", State[m][n]);
		}
		printf("\n");
	}
}

void EncryptRounds(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS])
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{	
			InBlock[m][n] = ConcatVar(m, n);
			printf("%d ", InBlock[m][n]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	ShiftRows(InBlock, State);
	MixColumns(InBlock, State);
}


int main(void)
{
	int InBlock[NUM_ROWS][NUM_COLS], State[NUM_ROWS][NUM_COLS];	
	
	EncryptRounds(InBlock, State);
}
