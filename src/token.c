#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/token.h"

token_t *init_token(int type, char *value) {
    token_t *token = calloc(1,sizeof(token_t));
    token->type = type;
    token->value = value;
    return token;
}

char *get_token_name(int token_type) {
    switch (token_type)
    {
    case TOKEN_SEMI:
        return ";";
    default:
        break;
    }
}