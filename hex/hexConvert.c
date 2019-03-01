#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 1024
#define HEXSIZE 2049


void loadFileText(char *file, char inBuffer[BUFSIZE])
{
	printf("Loading text...\n");

	int c, position = 0;
	FILE* inFile = fopen(file, "r");
	
	while(true)
	{
		c = fgetc(inFile);

		if (c == EOF)
			break;
		else if (c == '\n')
			c = '\0';
		else
			inBuffer[position] = c;	
	}

	
}

void convertToHex(char inBuffer[BUFSIZE], char hexBuffer[HEXSIZE])
{
	int index = 0;
	
	for (int i = 0; i < BUFSIZE; i++)
	{
		sprintf((hexBuffer + i * 2), "%02X", inBuffer[index]);
		index++;
	}	
}

void exportCipherText(char hexBuffer[HEXSIZE])
{
	FILE* outFile = fopen("hexcopy.txt", "w");
	fwrite(hexBuffer, sizeof(char), HEXSIZE, outFile);
}

void exportPlainText(char inBuffer[BUFSIZE])
{

}

void init_encrypt(char *file)
{
	char inBuffer[BUFSIZE], hexBuffer[HEXSIZE];
	loadFileText(file, inBuffer);
	convertToHex(inBuffer, hexBuffer);
	exportCipherText(hexBuffer);
}

void init_decrypt(char *file)
{
	char inBuffer[BUFSIZE], hexBuffer[HEXSIZE];
	loadFileText(file, hexBuffer);
	convertToPlain();
	exportPlainText(inBuffer);
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		printf("Usage: convertHex <operation> <file>\n");
		return 1;
	if (strncmp(argv[1], "-e", sizeof(argv[1]) == 0))
		init_encrypt(argv[2]);
	if (strncmp(argv[1], "-d", sizeof(argv[1]) == 0))
		init_decrypt(argv[2]);
}
