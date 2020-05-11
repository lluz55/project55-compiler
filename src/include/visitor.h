#ifndef VISITOR_H
#define VISITOR_H
#include <ctype.h>
#include "ast.h"

typedef struct _visitor 
{
    ast_t **variable_definitions;
    size_t variable_definitions_size;
} visitor_t;


visitor_t *init_visitor();

ast_t *visitor_visit(visitor_t *visitor, ast_t *node);

ast_t *visitor_variable_definition(visitor_t *visitor, ast_t *node);

ast_t *visitor_variable(visitor_t *visitor, ast_t *node);

ast_t *visitor_function_call(visitor_t *visitor, ast_t *node);

ast_t *visitor_string(visitor_t *visitor, ast_t *node);

ast_t *visitor_compound(visitor_t *visitor, ast_t *node);

#endif