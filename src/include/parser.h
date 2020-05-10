#ifndef PARSE_H
#define PARSE_H
#include "ast.h"
#include "lexer.h"

typedef struct _parser
{
    lexer_t *lexer;
    token_t *current_token;
    // Implements previous token
    token_t *prev_token;

} parser_t;

void *parser_eat(parser_t *parser, int token_type);

parser_t *init_parser(lexer_t *lexer);

ast_t *parser_parse(parser_t *parser);

ast_t *parser_parse_statement(parser_t *parser);

ast_t *parser_parse_statements(parser_t *parser);

ast_t *parser_parse_expr(parser_t *parser);

ast_t *parser_parse_factor(parser_t *parser);

ast_t *parser_parse_term(parser_t *parser);

ast_t *parser_parse_function_call(parser_t *parser);

ast_t *parser_parse_variable(parser_t *parser);

ast_t *parser_parse_variable_definition(parser_t *parser);

ast_t *parser_parse_string(parser_t *parser);

ast_t *parser_parse_id(parser_t *parser);
#endif