#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct _ast
{
    enum {
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_CONSTANT,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_COMPOUND,
        AST_NOOP,
        // TODO(lluz) implement bellow
        // Comptime function
        AST_COMP_TIME_FUNCTION,
        AST_COMP_TIME_CALL,
        // Struct
        AST_STRUCT_DEFINITION,
        AST_STRUCT_FIELD,
    } type;

    // Variable definition
    char *variable_definition_name;
    struct _ast *variable_definition_value;
    
    // Ast variable
    char *variable_name;
    
    // Function call
    char *function_call_name;
    struct _ast *function_call_args;
    size_t function_call_args_size;

    // Strings
    char *string_value;

    // Compound
    struct _ast** compound_value;
    size_t compound_size;

} ast_t;

ast_t *init_ast(int type);


#endif