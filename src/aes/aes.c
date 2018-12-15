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

void MixColumns(int InBlock[NUM_ROWS][NUM_COLS], int SBlock[NUM_ROWS][NUM_COLS])
{

}

void ShiftRows(int InBlock[NUM_ROWS][NUM_COLS], int SBlock[NUM_ROWS][NUM_COLS])
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			if (m % 2 == 0)
				SBlock[m][n] = InBlock[m][((n + m) % NUM_COLS)];
			else if (m % 2 == 1)
				SBlock[m][n] = InBlock[m][((n + (m + (NUM_COLS / 2))) % NUM_COLS)];	
			printf("%d ", SBlock[m][n]);
		}
		printf("\n");
	}
}

void CreateArray(int InBlock[NUM_ROWS][NUM_COLS], int SBlock[NUM_ROWS][NUM_COLS])
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
	printf("\n\n");
	ShiftRows(InBlock, SBlock);
	
	printf("\n\n%d", SBlock[1][0]);
	
	MixColumns(InBlock, SBlock);
}


int main(void)
{
	int InBlock[NUM_ROWS][NUM_COLS], SBlock[NUM_ROWS][NUM_COLS];	
	
	CreateArray(InBlock, SBlock);
}
