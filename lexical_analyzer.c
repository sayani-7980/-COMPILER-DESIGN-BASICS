#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char* keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int isKeyword(const char* word) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == '=' || ch == '<' || ch == '>' || ch == '!';
}

int main() {
    FILE *fp;
    char ch, buffer[100];
    int i = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error opening input.c\n");
        return 1;
    }

    printf("LEXICAL ANALYSIS OUTPUT:\n");
    printf("=========================\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            buffer[i++] = ch;
        } else {
            if (i > 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer))
                    printf("Keyword    : %s\n", buffer);
                else if (isdigit(buffer[0]))
                    printf("Number     : %s\n", buffer);
                else
                    printf("Identifier : %s\n", buffer);
                i = 0;
            }

            if (isOperator(ch)) {
                printf("Operator   : %c\n", ch);
            }
        }
    }

    fclose(fp);
     return 0;
}
