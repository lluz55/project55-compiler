#include "include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *parser_eat(parser_t *parser, int token_type){
    if(parser->current_token->type == token_type) {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    } else {
        printf("Unexpected token `%s` at line %d, column %d. Expected token type `%s`\n",
                parser->current_token->value,
                parser->lexer->line,
                parser->lexer->column,
                get_token_name(token_type)
            );
    }
}

parser_t *init_parser(lexer_t *lexer){
    parser_t *parser = calloc(1, sizeof(struct _parser));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;
    return parser;
}

// Main entry point
ast_t *parser_parse(parser_t *parser){
    // FIX(lluz)
    return parser_parse_statements(parser);
}

// Parse statement based on current token
ast_t *parser_parse_statement(parser_t *parser){
    switch (parser->current_token->type)
    {
    case TOKEN_ID:
        return parser_parse_id(parser);
    }

    return init_ast(AST_NOOP);
}

// Parse list of statements
ast_t *parser_parse_statements(parser_t *parser){
    // compound = more than one expression grouped
    ast_t *compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct _ast));

    // Parse statement and add it to begin of compound's list
    ast_t *statement = parser_parse_statement(parser);
    compound->compound_value[0] = statement;
    compound->compound_size += 1;            
    
    // TODO(lluz) Implement without semi colon. Use new line instead
    while (parser->current_token && parser->current_token->type == TOKEN_SEMI) 
    {
        parser_eat(parser, TOKEN_SEMI);        
        ast_t *statement = parser_parse_statement(parser);
        
        
        if(statement) {
            compound->compound_size += 1;            
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size * sizeof(struct _ast)
            );
            compound->compound_value[compound->compound_size-1] = statement;        
        }
    }
    return compound;
}

ast_t *parser_parse_expr(parser_t *parser){
    switch (parser->current_token->type)
    {
    case TOKEN_STRING:
        return parser_parse_string(parser);
    case TOKEN_ID:
        return parser_parse_id(parser);
    }
    return init_ast(AST_NOOP);
}

ast_t *parser_parse_factor(parser_t *parser){
    
}

ast_t *parser_parse_term(parser_t *parser){
    
}

ast_t *parser_parse_function_call(parser_t *parser){
    ast_t *function_call = init_ast(AST_FUNCTION_CALL);

    function_call->function_call_name = parser->prev_token->value;
    parser_eat(parser, TOKEN_LPAREN);
    function_call->function_call_args = calloc(1, sizeof(struct _ast));
    
    ast_t *expr = parser_parse_expr(parser);
    function_call->function_call_args[0] = expr;
    function_call->function_call_args_size += 1;

    while (parser->current_token->type == TOKEN_COMMA) 
    {
        parser_eat(parser, TOKEN_COMMA);

        ast_t *expr = parser_parse_expr(parser);
        function_call->function_call_args[0] = expr;
        function_call->function_call_args_size += 1;

        
        function_call->function_call_args = realloc(
            function_call->function_call_args,
            function_call->function_call_args_size * sizeof(struct _ast)
        );
        function_call->function_call_args[function_call->function_call_args_size-1] = expr;        
    }
    parser_eat(parser, TOKEN_RPAREN);

    return function_call;
}

ast_t *parser_parse_variable(parser_t *parser){
    parser_eat(parser, TOKEN_ID);

    char *token_value = parser->current_token->value;
    if(parser->current_token->type == TOKEN_LPAREN) {
        return parser_parse_function_call(parser);
    }

    //TODO(lluz): implement compilation time execution

    ast_t *variable = init_ast(AST_VARIABLE);
    variable->variable_name = token_value;

    return variable;
}

ast_t *parser_parse_string(parser_t *parser){
    ast_t *string = init_ast(AST_STRING);
    string-> string_value = parser->current_token->value;
    parser_eat(parser, TOKEN_STRING);
    return string;
}

ast_t *parser_parse_id(parser_t *parser) {
    if(strcmp(parser->current_token->value, "var") == 0) {
        return parser_parse_variable_definition(parser);
    } else {
        return parser_parse_variable(parser);
    }
}

ast_t *parser_parse_variable_definition(parser_t *parser) {
    parser_eat(parser, TOKEN_ID); // expicting `var`
    char *variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); // expecting variable name
    parser_eat(parser, TOKEN_EQUALS); // expecting `=`

    ast_t *variable_value = parser_parse_expr(parser);
    ast_t *variable_definition = init_ast(AST_VARIABLE_DEFINITION);

    variable_definition->variable_name = variable_name;
    variable_definition->variable_definition_value = variable_value;
    return variable_definition;
}