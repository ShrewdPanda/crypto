#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define DEFAULT_KEYSIZE 128
#define MODULO 2

#define NUM_BITS 8
#define NUM_COLS 4
#define NUM_ROWS 4

#define C 0x63


void BitScrambler(int State[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			State[m][n] = State[m][n] ^ (((State[m][n] << 4 ) | (State[m][n] >> (NUM_BITS - 4))) % NUM_BITS) ^ \
				      ((((State[m][n]) << 5) | (State[m][n] >> (NUM_BITS - 5))) % NUM_BITS) ^ \
				      ((((State[m][n]) << 6) | (State[m][n] >> (NUM_BITS - 6))) % NUM_BITS) ^ \
				      ((((State[m][n]) << 7) | (State[m][n] >> (NUM_BITS - 7))) % NUM_BITS) ^ C; 
		}
	}	
}


int GetKey(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (strncmp("-k", argv[i], argc) == 0)
			return atoi(argv[i + 1]);	
		else
			return DEFAULT_KEYSIZE;
	}
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

int modulo(int stateVal)
{
	int initVal = stateVal % MODULO;

	if (initVal < 0)
		initVal += MODULO;
	return initVal;
}

void MultInv(int State[NUM_ROWS][NUM_COLS])
{
	for (int m; m < NUM_ROWS; m++)
	{
		for (int n; n < NUM_COLS; n++)
		{
			State[m][n] = modulo(State[m][n]);
			
			for (int i = 0; i < MODULO; i++)
				if (modulo((State[m][n]) * i) == 1)
					State[m][n] = i;	
		}
	}	
}


void SendCipherText()
{
	char outBuffer[BUFSIZE];
	FILE* cipherFile = fopen("cipher.txt", "w");
	fwrite(outBuffer, sizeof(char), sizeof(outBuffer), cipherFile);
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

void ConvertToHex(int c)
{
		
}

void Decrypt(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS], int num_rounds)
{
	for (int m = 0; m < (num_rounds - 1); m++)
	{
		InvSubBytes(State);	
		InvShiftRows(State);
		InvMixColumns(State);
		InvKeyRounds(State);
	}
		InvSubBytes(State);
		InvShiftRows(State);
		InvKeyRounds(State);
}


void Encrypt(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS], int num_rounds)
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{	
			State[m][n] = InBlock[m][n];
		}
	}

	for (int m = 0; m < (num_rounds - 1); m++)
	{
		printf("Substituting Bytes...\n");
		SubBytes(State);	
		printf("Shifting Rows...\n");
		ShiftRows(State);
		printf("Mixing Columns...\n");
		MixColumns(State);
		printf("Performing Keyrounds...\n");
		KeyRounds(State);
	}
		SubBytes(State);
		ShiftRows(State);
		KeyRounds(State);
		
		printf("Outputting CipherText...\n");
		SendCipherText(State);
}

void GetPlainText(int InBlock[NUM_ROWS][NUM_COLS], char *argv[])
{
	int letter, position = 0;
	
	FILE* infile = fopen(argv[2], "r");
	FILE* hexfile = fopen("hex.txt", "w");
	
	char inBuffer[BUFSIZE];
	char hexBuffer[BUFSIZE * 2 + 1];
	
	printf("Extracting text...\n");

	while (1)
	{
		letter = fgetc(infile);
		
		if (letter == EOF)
			break;
		else if (letter == '\n')
		{	
			inBuffer[position] = '\0';
			position++;
		}
		else
		{
			inBuffer[position] = letter;
			sprintf(hexBuffer + position * 2, "%02X", inBuffer[position]);
			position++;	
		}
	}
	
	printf("Exporting hex...\n");
	fwrite(hexBuffer, sizeof(char), sizeof(hexBuffer), hexfile);

	position = 0;

	// store the hex from outBuffer into InBlock.
	for (int i = 0; i < NUM_COLS; i++)
	{
		for (int j = 0; j < NUM_ROWS; j++)
		{
			InBlock[j][i] = hexBuffer[position];
			position++;
		}
	}
		
}

void init(int InBlock[NUM_ROWS][NUM_COLS], int State[NUM_ROWS][NUM_COLS], int num_rounds, char *argv[])
{
	if (strncmp(argv[1], "-e", 2) == 0)
	{
		printf("Encrypting '%s' ...\n", argv[2]);
		Encrypt(InBlock, State, num_rounds);
	}
	else if (strncmp(argv[1], "-d", 2) == 0)
	{
		printf("Decrypting '%s' ...\n", argv[2]);
		Decrypt(InBlock, State, num_rounds);
	}
	else
	{
		printf("In these parts, we either Encrypt (-e), or we Decrypt (-d).\nWhat's it gonna be, partner?\n");
		perror("Operation not declared.\n");
	}
}

int main(int argc, char *argv[])
{
	int num_rounds = 12;
	int InBlock[NUM_ROWS][NUM_COLS], State[NUM_ROWS][NUM_COLS];	

	if (argc < 3)
	{
		printf("Usage: aes [-e, -d] <file> [-k <keysize> *optional*]\n");
		return 1;
	}
	else
	{	
		printf("Opening input file...\n");
		GetPlainText(InBlock, argv);	
		
		int keysize = GetKey(argc, argv);
		
		if (keysize == 128)
			init(InBlock, State, num_rounds, argv);
		else if (keysize == 192)
		{
			num_rounds = 14;
			init(InBlock, State, num_rounds, argv);
		}
		else if (keysize == 256)
		{
			num_rounds = 16;
			init(InBlock, State, num_rounds, argv);
		}
		else
			perror("Invalid keysize");	
	}
}
