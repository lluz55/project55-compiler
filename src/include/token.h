#ifndef TOKEN_H
#define TOKEN_H

typedef struct _token
{
    enum {
        TOKEN_ID,       // 0
        TOKEN_EQUALS,   // 1
        TOKEN_STRING,   // 2
        // TODO(lluz): Implement 
        // TOKEN_NEW_LINE,
        TOKEN_LPAREN,   // 3
        TOKEN_RPAREN,   // 4
        TOKEN_LCURL,    // 5
        TOKEN_RCURL,    // 6
        TOKEN_COLON,    // 7
        TOKEN_SEMI,     // 8
        TOKEN_COMMA,    // 9
        TOKEN_EOF,      // 10
    } type;

    char *value;
} token_t;


char *get_token_name(int token_type);

token_t *init_token(int type, char *value);

#endif