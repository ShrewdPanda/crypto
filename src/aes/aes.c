#include <stdio.h>

#define NUM_ROWS 4
#define NUM_COLS 4


void BitScrambler(int State[NUM_ROWS][NUM_COLS])
{

}

int ConcatVars(int m, int n)
{
	int pow = 10;
	while (n >= pow)
		pow *= 10;
	return m * pow + n;
}


void KeyRounds(int State[NUM_ROWS][NUM_COLS])
{
	void KeyExpansion();
	void ApplyRound();
}


void MixColumns(int State[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			State[m][n] = (State[m][n] * 2) + ((State[(m + 2) % NUM_ROWS][n]) * 3) + (State[(m + 3) % NUM_ROWS][n]) + (State[((m + 4) % NUM_ROWS)][n]);
		}
	}
}


void MultInv(int State[NUM_ROWS][NUM_COLS])
{

}


void ShiftRows(int State[NUM_ROWS][NUM_COLS])
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			if (m % 2 == 0)
				State[m][n] = State[m][((n + m) % NUM_COLS)];
			else if (m % 2 == 1)
				State[m][n] = State[m][((n + (m + (NUM_COLS / 2))) % NUM_COLS)];	
		}
	}
}


void SubBytes(int State[NUM_ROWS][NUM_COLS])
{
	MultInv(State);
	BitScrambler(State);	
}


void Encrypt(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS])
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{	
			InBlock[m][n] = ConcatVars(m, n);
			State[m][n] = InBlock[m][n];
		}
	}

	SubBytes(State);	
	ShiftRows(State);
	MixColumns(State);
	KeyRounds(State);
}


int main(void)
{
	int InBlock[NUM_ROWS][NUM_COLS], State[NUM_ROWS][NUM_COLS];	
	
	Encrypt(InBlock, State);
}
