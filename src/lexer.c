#include "include/lexer.h"
#include "include/token.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

lexer_t *init_lexer(char *content){
    lexer_t *lexer = calloc(1, sizeof(struct _lexer));
    lexer->content = content;
    lexer->index = 0;
    lexer->current_char = content[lexer->index];
    lexer->line = 1;
    lexer->column = 1;
    return lexer;
}

void lexer_advance(lexer_t *lexer){
    if(lexer->current_char != '\0' && lexer->index < strlen(lexer->content)){
        lexer->index += 1;
        lexer->current_char = lexer->content[lexer->index];
    } else {
    }
}

void lexer_skip_whitespace(lexer_t *lexer){
    // lexer->current_char == 10 -> new line
    
    while (lexer->current_char == ' ' || lexer->current_char == '\t'|| lexer->current_char == '\n'){       
        if (lexer->current_char == '\t') {
            lexer->column += 4;
        }
        lexer_advance(lexer);
    }
}

token_t *lexer_get_next_token(lexer_t *lexer){
    while (lexer->current_char != '\0' && lexer->index < strlen(lexer->content))
    {
        if (lexer->current_char == '\n') {
            lexer->column = 0;
            lexer->line += 1;
        }

        if (lexer->current_char == '\t') {
            lexer->column += 4;
        }

        if( lexer->current_char == ' ') {
             lexer->column += 1;
        }

        // printf("%d\n", lexer->column);

        if (lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n') {                        
            lexer_skip_whitespace(lexer);
        }

        if(isalnum(lexer->current_char)) {
            return lexer_collect_id(lexer);
        }

        if(lexer->current_char == '"') {
            return lexer_collect_string(lexer);
        }

        switch (lexer->current_char)
        {
        case '=':
            return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
        case ':':
            return lexer_advance_with_token(lexer, init_token(TOKEN_COLON, lexer_get_current_char_as_string(lexer)));
        case ';':
            return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
        case ',':
            return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer)));
        case '(':
            return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));
        case ')':
            return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
        case '{':
            return lexer_advance_with_token(lexer, init_token(TOKEN_LCURL, lexer_get_current_char_as_string(lexer)));
        case '}':
            return lexer_advance_with_token(lexer, init_token(TOKEN_RCURL, lexer_get_current_char_as_string(lexer)));
        // case '\n':
        //     return lexer_advance_with_token(lexer, init_token(TOKEN_NEW_LINE, lexer_get_current_char_as_string(lexer)));
        //     break;            
        default:
            break;
        }
    }
    return init_token(TOKEN_EOF, "\0");    
}

token_t *lexer_collect_string(lexer_t *lexer){
    lexer_advance(lexer);

    // Note(lluz): can be optimized with diferent allocation
    char *value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->current_char != '"')
    {
        char *str = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(str) + 1)*sizeof(char));
        strcat(value, str);
        lexer->column += 1;
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    return init_token(TOKEN_STRING, value);
    
}

// Note(lluz): TODO: check if first character is number
token_t *lexer_collect_id(lexer_t *lexer) {
    // Note(lluz): can be optimized with diferent allocation
    char *value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->current_char))
    {
        lexer->column += 1;
        char *str = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(str) + 1)*sizeof(char));
        strcat(value, str);
        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);

}

token_t *lexer_advance_with_token(lexer_t *lexer, token_t *token) {
    lexer->column += 1;
    lexer_advance(lexer);
    return token;
}

char *lexer_get_current_char_as_string(lexer_t *lexer){
    char *str = calloc(2, sizeof(char));
    str[0] = lexer->current_char;
    str[1] = '\0';
    return str;
}