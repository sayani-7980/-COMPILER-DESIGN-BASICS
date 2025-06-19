#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
const char *keywords[] = {
    "int", "float", "char", "if", "else", "for", "while", "return", "void", "double"
};
int isKeyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '=' || ch == '<' || ch == '>' || ch == '!');
}
int main() {
    FILE *fp;
    char ch, buffer[100];
    int i = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Could not open input.txt\n");
        return 1;
    }
printf("----- Lexical Analysis Output -----\n");

    while ((ch = fgetc(fp)) != EOF) {
        // Skip whitespace and special delimiters
        if (isspace(ch) || ch == ',' || ch == ';' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            if (i > 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer))
                    printf("[Keyword]    %s\n", buffer);
                else
                    printf("[Identifier] %s\n", buffer);
                i = 0;
            }
 }
        // Handle operators (one or two character)
        else if (isOperator(ch)) {
            if (i > 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer))
                    printf("[Keyword]    %s\n", buffer);
                else
                    printf("[Identifier] %s\n", buffer);
                i = 0;
            }
char next = fgetc(fp);
            if ((ch == '=' || ch == '!' || ch == '<' || ch == '>') && next == '=') {
                printf("[Operator]   %c%c\n", ch, next);
            } else {
                printf("[Operator]   %c\n", ch);
                ungetc(next, fp); // Push back if not two-character operator
            }
        }
 else {
            buffer[i++] = ch;
        }
    }

    // Handle last token if file ends without delimiter
    if (i > 0) {
        buffer[i] = '\0';
        if (isKeyword(buffer))
            printf("[Keyword]    %s\n", buffer);
        else
            printf("[Identifier] %s\n", buffer);
    }

    fclose(fp);
     return 0;
}
