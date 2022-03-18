#include <stdio.h>
#include <ctype.h>

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

//Functions
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

// Character Classes
#define LETTER 0
#define UNKNOWN 99

#define IDENT_A 11
#define IDENT_B 12
#define IDENT_C 13




int main(int argc, char* argv[]) {
	if ((in_fp = fopen(argv[1], "r")) == NULL) {
		printf("File does not exist");
	} else {
		getChar();
	}




	return 0;
}

// Set nextToken to what the next character in the input file is.
int lookup(char ch) {
   switch (ch){
		case 'a':
			addChar();
			nextToken = IDENT_A;
			break;
		case 'b':
			addChar();
			nextToken = IDENT_B;
			break;
		case 'c':
			addChar();
			nextToken = IDENT_C;
			break;
		default:
			addChar();
			nextToken = EOF;
			break;
	}
}

void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	} else {
		printf("Error - lexeme is too long.\n");
	}
}

void getChar() {
	if ((nextChar = getc(in_fp)) != EOF) {
		if (nextChar == 'a' || nextChar == 'b' || nextChar == 'c') {
			charClass = LETTER;
		} else {
			charClass = UNKNOWN;
		}
	} else {
		charClass = EOF;
	}
}

void getNonBlank() {
	while (isspace(nextChar)) {
		getChar();
	}
}

int lex() {
	lexLen = 0;
	getNonBlank();

	switch (charClass) {
		case LETTER:
			lookup(nextChar);
			getChar();
			break;
		case UNKNOWN:
			error();
			break;
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = '\0';
			break;
	}
	
	printf("Next token is %d, next lexeme is %s\n", nextToken, lexeme);
	return nextToken;
}