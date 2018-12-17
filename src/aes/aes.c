#include <stdio.h>
#include <string.h>

#define NUM_BITS 8
#define NUM_ROWS 4
#define NUM_COLS 4
#define c 0x63

void BitScrambler(int State[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			State[m][n] = State[m][n] ^ (((State[m][n] << 4 ) | (State[m][n] >> (NUM_BITS - 4))) % NUM_BITS) ^ \
				      ((((State[m][n]) << 5) | (State[m][n] >> (NUM_BITS - 5))) % NUM_BITS) ^ \
				      ((((State[m][n]) << 6) | (State[m][n] >> (NUM_BITS - 6))) % NUM_BITS) ^ \
				      ((((State[m][n]) << 7) | (State[m][n] >> (NUM_BITS - 7))) % NUM_BITS) ^ c; 
		}
	}	
}


int ConcatVars(int m, int n)
{
	int pow = 10;
	while (n >= pow)
		pow *= 10;
	return m * pow + n;
}


void InvKeyRounds(int State[NUM_ROWS][NUM_COLS])
{

}


void InvMixColumns(int State[NUM_ROWS][NUM_COLS])
{

}


void InvShiftRows(int State[NUM_ROWS][NUM_COLS])
{

}


void InvSubBytes(int State[NUM_ROWS][NUM_COLS])	
{

}


void KeyRounds(int State[NUM_ROWS][NUM_COLS])
{
	void ExpandKeys();
	void ApplyRound();
}


void MixColumns(int State[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			State[m][n] = (State[m][n] * 2) ^ ((State[(m + 2) % NUM_ROWS][n]) * 3) ^ \
				      (State[(m + 3) % NUM_ROWS][n]) ^ (State[((m + 4) % NUM_ROWS)][n]);
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


void Decrypt(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS])
{
	InvSubBytes(State);	
	InvShiftRows(State);
	InvMixColumns(State);
	InvKeyRounds(State);
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


int main(int argc, char* argv[])
{
	int InBlock[NUM_ROWS][NUM_COLS], State[NUM_ROWS][NUM_COLS];	

	if (argc < 3)
	{
		printf("Usage: aes [-e, -d] <file>\n");
		return 1;
	}
	else
	{	
		if (strncmp(argv[1], "-d", 2) == 0)
			Encrypt(InBlock, State);
		else if (strncmp(argv[1], "-d", 2) == 0)
			Decrypt(InBlock, State);
		else
			printf("Something's not right: Aborting program.\n");
			return 1;
	}
}
