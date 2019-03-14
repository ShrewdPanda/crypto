#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE 16
#define DEFAULT_KEYSIZE 128
#define MODULO 256

#define NUM_BITS 8
#define NUM_COLS 4
#define NUM_ROWS 4

#define C 0x63

void bitScrambler(char state[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			state[m][n] = state[m][n] ^ (((state[m][n] << 4) % NUM_BITS) ^ \
				      (((state[m][n]) << 5) % NUM_BITS) ^ \
				      (((state[m][n]) << 6) % NUM_BITS) ^ \
				      (((state[m][n]) << 7) % NUM_BITS)) ^ C; 
		}
	}	
}

void bitUnScrambler(char state[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			state[m][n] = state[m][n] ^ (((state[m][n] >> 4) % NUM_BITS) ^ \
				      (((state[m][n]) >> 5) % NUM_BITS) ^ \
				      (((state[m][n]) >> 6) % NUM_BITS) ^ \
				      (((state[m][n]) >> 7) % NUM_BITS)) ^ C; 
		}
	}	
	
}

void multInv(char block[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			for (int i = 0; i < MODULO; i++)
			{	
				if ((block[m][n] & i % MODULO) == 1)
					block[m][n] = i;
			}
		}
	}	
}

int getKey(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (strncmp("-k", argv[i], argc) == 0)
			return atoi(argv[i + 1]);	
		else
			return DEFAULT_KEYSIZE;
	}
}

void invKeyRounds(char state[NUM_ROWS][NUM_COLS])
{

}

void mixColumns(char state[NUM_ROWS][NUM_COLS])
{
	for (int n = 0; n < NUM_COLS; n++)
	{
		state[0][n] ^= (state[0][n] * 0x02)  ^ ((state[1][n]) * 0x03)  ^ \
			       ((state[2][n])) ^ ((state[3][n]));
		
		state[1][n] ^= (state[0][n])  ^ ((state[1][n]) * 0x02)  ^ \
			       ((state[2][n]) * 0x03) ^ ((state[3][n]));
	
		state[2][n] ^= (state[0][n])  ^ ((state[1][n]))  ^ \
			       ((state[2][n]) * 0x02) ^ ((state[3][n]) * 0x03);
	
		state[3][n] ^= (state[0][n] * 0x03)  ^ ((state[1][n]))  ^ \
			       ((state[2][n])) ^ ((state[3][n]) * 0x02);
	}
}


void invMixColumns(char state[NUM_ROWS][NUM_COLS])
{
	for (int n = 0; n < NUM_COLS; n++)
	{
		state[0][n] ^= (state[0][n] * 0x0E)  ^ ((state[1][n]) * 0x0B)  ^ \
			       ((state[2][n]) * 0x0D) ^ ((state[3][n]) * 0x09);
		
		state[1][n] ^= (state[0][n] * 0x09)  ^ ((state[1][n]) * 0x0E)  ^ \
			       ((state[2][n]) * 0x0B) ^ ((state[3][n]) * 0x0D);
	
		state[2][n] ^= (state[0][n] * 0x0D)  ^ ((state[1][n]) * 0x09)  ^ \
			       ((state[2][n]) * 0x0E) ^ ((state[3][n]) * 0x0B);
	
		state[3][n] ^= (state[0][n] * 0x0B)  ^ ((state[1][n]) * 0x0D)  ^ \
			       ((state[2][n]) * 0x09) ^ ((state[3][n]) * 0x0E);
	}
}


void invShiftRows(char state[NUM_ROWS][NUM_COLS])
{
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			if (m % 2 == 0)
				state[m][n] = state[m][((n + m) % NUM_COLS)];
			else if (m % 2 == 1)
				state[m][n] = state[m][((n + (m + (NUM_COLS / 2))) % NUM_COLS)];	
		}
	}
}


void invSubBytes(char state[NUM_ROWS][NUM_COLS])	
{
	bitUnScrambler(state);
	multInv(state);
}


void keyRounds(char state[NUM_ROWS][NUM_COLS])
{
	void expandKeys();
	void applyRound();
}


void sendCipherText(char state[NUM_ROWS][NUM_COLS])
{
	FILE* outFile = fopen("cipher.txt", "w");
	char fileBuffer[BLOCKSIZE];
	int position = 0;

	for (int j = 0; j < NUM_COLS; j++)
	{
		for (int i = 0; i < NUM_ROWS; i++)
		{
			fileBuffer[position] = state[i][j];
			printf("%c", fileBuffer[position]);
			position++;
		}
	}
	
	fwrite(fileBuffer, sizeof(char), sizeof(fileBuffer), outFile);
}

void shiftRows(char state[NUM_ROWS][NUM_COLS])
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{
			if (m % 2 == 0)
				state[m][n] = state[m][((n + m) % NUM_COLS)];
			else if (m % 2 == 1)
				state[m][n] = state[m][((n + (m + (NUM_COLS / 2))) % NUM_COLS)];	
		}
	}
}


void subBytes(char State[NUM_ROWS][NUM_COLS])
{
	multInv(State);
	bitScrambler(State);	
}


void decrypt(char inBlock[NUM_ROWS][NUM_COLS], char state[NUM_ROWS][NUM_COLS], int num_rounds)
{
	for (int m = 0; m < (num_rounds - 1); m++)
	{
		invSubBytes(state);	
		invShiftRows(state);
		invMixColumns(state);
		invKeyRounds(state);
	}
		invSubBytes(state);
		invShiftRows(state);
		invKeyRounds(state);
}


void encrypt(char inBlock[NUM_ROWS][NUM_COLS], char state[NUM_ROWS][NUM_COLS], int num_rounds)
{	
	for (int m = 0; m < NUM_ROWS; m++)
	{
		for (int n = 0; n < NUM_COLS; n++)
		{	
			state[m][n] = inBlock[m][n];
		}
	}

	for (int m = 0; m < (num_rounds - 1); m++)
	{
		printf("Substituting Bytes...\n");
		subBytes(state);	
		printf("Shifting Rows...\n");
		shiftRows(state);
		printf("Mixing Columns...\n");
		mixColumns(state);
		printf("Performing Keyrounds...\n");
		keyRounds(state);
	}
		subBytes(state);
		shiftRows(state);
		keyRounds(state);
		
		printf("Outputting CipherText...\n");
		sendCipherText(state);
}

void getPlainText(char inBlock[NUM_ROWS][NUM_COLS], char *argv[])
{
	FILE* inFile = fopen(argv[2], "r");
	
	char fileBuffer[BLOCKSIZE];
	int position = 0;

	printf("Extracting text...\n");

	while (fgets(fileBuffer, sizeof(fileBuffer), inFile) != NULL)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			for (int i = 0; i < NUM_ROWS; i++)
			{
				if (fileBuffer[position] == '\n')
				{	
					inBlock[i][j] = '\0';
					printf("%c", inBlock[i][j]);
					position++;
				}
				else
				{
					inBlock[i][j] = fileBuffer[position];
					printf("%c", inBlock[i][j]);
					position++;	
				}
			}
		}
	}
	printf("\n");
}

void init(char inBlock[NUM_ROWS][NUM_COLS], char state[NUM_ROWS][NUM_COLS], int num_rounds, char *argv[])
{
	if (strncmp(argv[1], "-e", 2) == 0)
	{
		printf("Encrypting '%s' ...\n", argv[2]);
		encrypt(inBlock, state, num_rounds);
	}
	else if (strncmp(argv[1], "-d", 2) == 0)
	{
		printf("Decrypting '%s' ...\n", argv[2]);
		decrypt(inBlock, state, num_rounds);
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
	char inBlock[NUM_ROWS][NUM_COLS], state[NUM_ROWS][NUM_COLS];	

	if (argc < 3)
	{
		printf("Usage: aes [-e, -d] <file> [-k <keysize> *optional*]\n");
		return 1;
	}
	else
	{	
		printf("Opening input file...\n");
		getPlainText(inBlock, argv);	
		
		int keysize = getKey(argc, argv);
		
		if (keysize == 128)
			init(inBlock, state, num_rounds, argv);
		else if (keysize == 192)
		{
			num_rounds = 14;
			init(inBlock, state, num_rounds, argv);
		}
		else if (keysize == 256)
		{
			num_rounds = 16;
			init(inBlock, state, num_rounds, argv);
		}
		else
			perror("Invalid keysize");	
	}
}
