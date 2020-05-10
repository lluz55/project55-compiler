#include "include/ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ast_t *init_ast(int type) {
    ast_t *ast = calloc(1, sizeof(struct _ast));
    ast->type = type;

    // Variable definition
    ast->variable_definition_name = (void *)0;
    ast->variable_definition_value = (void *)0;
    
    // Ast variable
    ast->variable_name = (void *)0;
    
    // Function call
    ast->function_call_name = (void *)0;
    ast->function_call_args = (void *)0;
    ast->function_call_args_size = 0;

    // Strings
    ast->string_value = (void *)0;

    // Compound
    ast->compound_value = (void *)0;
    ast->compound_size = 0;

    return ast;
}