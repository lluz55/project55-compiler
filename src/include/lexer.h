#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct _lexer
{
    char current_char;
    unsigned int index;
    char *content;
    // TODO(lluz): implement line and column numbers for debuging
    unsigned int line;
    unsigned int column;
} lexer_t;

lexer_t *init_lexer(char *content);

void lexer_advance(lexer_t *lexer);

void lexer_skip_whitespace(lexer_t *lexer);

token_t *lexer_get_next_token(lexer_t *lexer);

token_t *lexer_collect_string(lexer_t *lexer);

token_t *lexer_collect_id(lexer_t *lexer);

token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token);

char *lexer_get_current_char_as_string(lexer_t *lexer);


#endif