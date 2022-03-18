// Group: Zachary Meyner, Ryan Vaughn, Amelia Sigmund

#include <stdio.h>
#include <ctype.h>

#define true 1
#define false 0

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();
int parses = true;

//Functions
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

//Recursive Descent Functions
void S();
void A();
void B();
void C();
void error();


// Character Classes
#define LETTER 0

// Identifiers for terminals
#define IDENT_A 11
#define IDENT_B 12
#define IDENT_C 13

// This part was done by Zach

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("USAGE:\n./parse [file]\n");
	}

	if (argc == 2){
		if ((in_fp = fopen(argv[1], "r")) == NULL) {
			printf("File does not exist.\n");
		} else {
			getChar();
			/*
			do {
			lex();
			} while (nextToken != EOF);
			*/
			lex();
			S();
		}
	}

	if (parses == true) {
		printf("\033[1;32m");
		printf("Statement parses.\n");
		printf("\033[0m");
	} else {
		printf("\033[1;31m"); 
		printf("Statement does not parse.\n");
		printf("\033[0m");
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

// This part was done by Ryan

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


// This part was done by Amelia

// Parser for S Nonterminal
// S -> A
void S() {
	printf("Enter S\n");
	A();
	printf("Exit S\n");
}


// Parser for A Nonterminal
// A -> a | aA | B
void A() {
	printf("Enter A\n");

	if (nextToken == IDENT_A) {
		lex();

		if (nextToken != EOF) {
			A();
		}
	} else {
		B();
	}
}

// Parser for B Nonterminal
// B -> b | bbB | C
void B() {
	printf("Enter C\n");

	if (nextToken == IDENT_B) {
		lex();

		if (nextToken == IDENT_B) {
			lex();
			B();
		}
	} else {
		C();
	}

	printf("Exit B\n");
}

// Parser for C Nonterminal
// C -> cc | cCc
void C() {
	printf("Enter C\n");

	if (nextToken == IDENT_C) {
		int totalC = 0;

		while (nextToken == IDENT_C) {
			totalC++;
			lex();
		}

		if (totalC % 2 != 0) {
			error();
		}
	} else {
		error();
	}

	printf("Exit C\n");
}

void error() {
	parses = false;
}