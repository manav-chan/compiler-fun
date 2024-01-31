#include <stdio.h>
#include <string.h>

int dfa = 0;

void start(char c) {
    if(c == '_' || c == '$' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        dfa = 1;
    } else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=') {
        dfa = 2;
    } else if(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == ',' || c == '.') {
        dfa = 3;
    } else {
        dfa = 4;
    }
}

void state1(char c) {
    if(c == '_' || c == '$' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        dfa = 1;
    } else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=') {
        dfa = 2;
    } else if(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == ',' || c == '.') {
        dfa = 3;
    } else {
        dfa = 4;
    }
}

void state2(char c) {
    if(c == '_' || c == '$' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        dfa = 1;
    } else if(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == ',' || c == '.') {
        dfa = 3;
    } else {
        dfa = 4;
    }
}

void state3(char c) {
    if(c == '_' || c == '$' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        dfa = 1;
    } else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=') {
        dfa = 2;
    } else {
        dfa = 4;
    }
}

void dead(char c) {
    dfa = 4;
}

int isAccepted(char str[]) {
    int i, len = strlen(str);
    
    for(i=0; i<len; i++) {
        // printf("%d%c ", dfa, str[i]);
        if(dfa == 0)
            start(str[i]);
        else if(dfa == 1)
            state1(str[i]);
        else if(dfa == 2)
            state2(str[i]);
        else if(dfa == 3)
            state3(str[i]);
        else
            return 0;
    }
    if(dfa == 1 || dfa == 2 || dfa == 3)
        return 1;
    else
        return 0;
}

int checkToken(char c) {
    dfa = 0;
    start(c);
    if(dfa == 1) // Identifier
        return 1;
    else if(dfa == 2) // Operator
        return 2;
    else if(dfa == 3) // Separator
        return 3;
    else // Invalid Token
        return 0;
}

void tokenGenerator(char str[]) {
    int i, t, len = strlen(str);
    char tokens[500] = "";
    
    for(i=0; i<len; i++) {
        t = checkToken(str[i]);
        strcat(tokens, "<");
        if(t == 1) {
            strcat(tokens, "id");
        } else if(t == 2) {
            strcat(tokens, "op");
        } else if(t == 3) {
            strcat(tokens, "sep");
        } else {
            strcat(tokens, "Invalid Token");
        }
        strcat(tokens, ",");
        strncat(tokens, &str[i], 1);
        strcat(tokens, "> ");
    }
    printf("%s\n", tokens);
}

int main() {
    char str[] = "a=b+c*d";
    if(isAccepted(str))
        tokenGenerator(str);
    else
        printf("Not Accepted\n");
    return 0;
}