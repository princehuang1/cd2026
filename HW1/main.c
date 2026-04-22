#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

int isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           ch == '_';
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

void printToken(char *token, char *type) {
    printf("%s: %s\n", token, type);
}

int main(void) {
    FILE *fp;
    int c;

    fp = fopen("main.c", "r");
    if (fp == NULL) {
        printf("Cannot open file main.c\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        char token[MAX_LEN];
        int i = 0;

        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            continue;
        }

        if (isLetter((char)c)) {
            token[i++] = (char)c;

            while ((c = fgetc(fp)) != EOF &&
                  (isLetter((char)c) || isDigit((char)c))) {
                token[i++] = (char)c;
            }

            token[i] = '\0';

            if (c != EOF) {
                ungetc(c, fp);
            }

            if (strcmp(token, "int") == 0) {
                printToken(token, "TYPE_TOKEN");
            }
            else if (strcmp(token, "main") == 0) {
                printToken(token, "MAIN_TOKEN");
            }
            else if (strcmp(token, "if") == 0) {
                printToken(token, "IF_TOKEN");
            }
            else if (strcmp(token, "else") == 0) {
                printToken(token, "ELSE_TOKEN");
            }
            else if (strcmp(token, "while") == 0) {
                printToken(token, "WHILE_TOKEN");
            }
            else {
                printToken(token, "ID_TOKEN");
            }
        }

        else if (isDigit((char)c)) {
            token[i++] = (char)c;

            while ((c = fgetc(fp)) != EOF && isDigit((char)c)) {
                token[i++] = (char)c;
            }

            token[i] = '\0';

            if (c != EOF) {
                ungetc(c, fp);
            }

            printToken(token, "LITERAL_TOKEN");
        }

        else if (c == '=') {
            int next = fgetc(fp);

            if (next == '=') {
                printToken("==", "EQUAL_TOKEN");
            } else {
                if (next != EOF) {
                    ungetc(next, fp);
                }
                printToken("=", "ASSIGN_TOKEN");
            }
        }

        else if (c == '>') {
            int next = fgetc(fp);

            if (next == '=') {
                printToken(">=", "GREATEREQUAL_TOKEN");
            } else {
                if (next != EOF) {
                    ungetc(next, fp);
                }
                printToken(">", "GREATER_TOKEN");
            }
        }

        else if (c == '<') {
            int next = fgetc(fp);

            if (next == '=') {
                printToken("<=", "LESSEQUAL_TOKEN");
            } else {
                if (next != EOF) {
                    ungetc(next, fp);
                }
                printToken("<", "LESS_TOKEN");
            }
        }

        else if (c == '+') {
            printToken("+", "PLUS_TOKEN");
        }

        else if (c == '-') {
            printToken("-", "MINUS_TOKEN");
        }

        else if (c == '(') {
            printToken("(", "LEFTPAREN_TOKEN");
        }

        else if (c == ')') {
            printToken(")", "REFTPAREN_TOKEN");
        }

        else if (c == '{') {
            printToken("{", "LEFTBRACE_TOKEN");
        }

        else if (c == '}') {
            printToken("}", "REFTBRACE_TOKEN");
        }

        else if (c == ';') {
            printToken(";", "SEMICOLON_TOKEN");
        }

        else {
            token[0] = (char)c;
            token[1] = '\0';
            printToken(token, "UNKNOWN_TOKEN");
        }
    }

    fclose(fp);
    return 0;
}
