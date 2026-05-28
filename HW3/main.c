#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

#define TOKEN_NUM 1
#define TOKEN_PLUS 2
#define TOKEN_LPAREN 3
#define TOKEN_RPAREN 4
#define TOKEN_EOF 5
#define TOKEN_UNKNOWN 6

char input[MAX_LEN];
int pos = 0;
int token;
char tokenText[MAX_LEN];

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

void getToken(void) {
    int i = 0;

    while (input[pos] == ' ' || input[pos] == '\n' ||
           input[pos] == '\t' || input[pos] == '\r') {
        pos++;
    }

    if (input[pos] == '\0') {
        token = TOKEN_EOF;
        strcpy(tokenText, "EOF");
    }
    else if (isDigit(input[pos])) {
        while (isDigit(input[pos])) {
            tokenText[i++] = input[pos++];
        }
        tokenText[i] = '\0';
        token = TOKEN_NUM;
    }
    else if (input[pos] == '+') {
        tokenText[0] = input[pos++];
        tokenText[1] = '\0';
        token = TOKEN_PLUS;
    }
    else if (input[pos] == '(') {
        tokenText[0] = input[pos++];
        tokenText[1] = '\0';
        token = TOKEN_LPAREN;
    }
    else if (input[pos] == ')') {
        tokenText[0] = input[pos++];
        tokenText[1] = '\0';
        token = TOKEN_RPAREN;
    }
    else {
        tokenText[0] = input[pos++];
        tokenText[1] = '\0';
        token = TOKEN_UNKNOWN;
    }
}

void error(void) {
    printf("Syntax Error\n");
}

int parse_S(void);
int parse_S_prime(void);
int parse_E(void);

int parse_S(void) {
    printf("S -> E S'\n");

    if (token == TOKEN_NUM || token == TOKEN_LPAREN) {
        if (!parse_E()) return 0;
        if (!parse_S_prime()) return 0;
        return 1;
    }

    error();
    return 0;
}

int parse_S_prime(void) {
    if (token == TOKEN_PLUS) {
        printf("S' -> + S\n");
        getToken();
        if (!parse_S()) return 0;
        return 1;
    }
    else if (token == TOKEN_RPAREN || token == TOKEN_EOF) {
        printf("S' -> epsilon\n");
        return 1;
    }

    error();
    return 0;
}

int parse_E(void) {
    if (token == TOKEN_NUM) {
        printf("E -> num\n");
        printf("%s\n", tokenText);
        getToken();
        return 1;
    }
    else if (token == TOKEN_LPAREN) {
        printf("E -> ( S )\n");
        getToken();

        if (!parse_S()) return 0;

        if (token != TOKEN_RPAREN) {
            error();
            return 0;
        }

        getToken();
        return 1;
    }

    error();
    return 0;
}

int main(void) {
    printf("Input expression: ");

    if (fgets(input, MAX_LEN, stdin) == NULL) {
        return 0;
    }

    getToken();

    if (parse_S() && token == TOKEN_EOF) {
        printf("Parsing OK\n");
    }
    else {
        printf("Parsing Failed\n");
    }

    return 0;
}
