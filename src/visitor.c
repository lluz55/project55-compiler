#include "include/visitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

static ast_t *builtin_function_print(visitor_t *visitor, ast_t **args, int args_size) {
    for (int i=0;i<args_size;i++){
        printf(" %s\n", args[i]->variable_name);
        ast_t *visited = visitor_visit(visitor, args[i]);
        // printf(" %d\n", visited->type);
        switch (visited->type)
        {
        case AST_STRING:
            printf("%s\n", visited->string_value);
            break;
        }
        printf("%p\n", visited);
    }

    return init_ast(AST_NOOP);
}

visitor_t *init_visitor() {
    visitor_t *visitor = calloc(1, sizeof(struct _visitor*));
    visitor->variable_definitions = (void*)0;
    visitor->variable_definitions_size = 0;
    return visitor;
}

ast_t *visitor_visit(visitor_t *visitor, ast_t *node){
    // printf(" %d\n", node->type);
    switch (node->type)
    {
    case AST_VARIABLE_DEFINITION:        
        return visitor_variable_definition(visitor, node);
    case AST_VARIABLE:        
        return visitor_variable(visitor, node);
    case AST_FUNCTION_CALL:        
        return visitor_function_call(visitor, node);
    case AST_STRING:        
        return visitor_string(visitor, node);
    case AST_COMPOUND:
        return visitor_compound(visitor, node);
    case AST_NOOP:
        return node;
    }

    printf("Uncaught statement of type `%d`\n", node->type);
    exit(1);
    return init_ast(AST_NOOP);
}

ast_t *visitor_variable_definition(visitor_t *visitor, ast_t *node){

    if(!visitor->variable_definitions) {
        visitor->variable_definitions = calloc(1, sizeof(struct _ast));
        visitor->variable_definitions[0] = node;
        visitor->variable_definitions_size += 1;
    } else {
        visitor->variable_definitions_size += 1;
        visitor->variable_definitions = realloc(
            visitor->variable_definitions,
            visitor->variable_definitions_size * sizeof(struct _ast)
        );
        visitor->variable_definitions[visitor->variable_definitions_size-1] = node;
    }
    return node;
}

ast_t *visitor_variable(visitor_t *visitor, ast_t *node){
    for (int i=0;i<visitor->variable_definitions_size;i++){
        ast_t *vardef = visitor->variable_definitions[i];

        if (strcmp(vardef->variable_name, node->variable_name)==0){
            printf(" %s\n", "here");
            return visitor_visit(visitor, vardef->variable_definition_value);
        }
    }

    printf("Undefined variable `%s`\n", node->variable_name);
    return node;
}

ast_t *visitor_function_call(visitor_t *visitor, ast_t *node){
    if(strcmp(node->function_call_name, "print") == 0) {
        return builtin_function_print(visitor, node->function_call_args, node->function_call_args_size);
    }

    printf("Undefined method `%s`\n", node->function_call_name);
    exit(1);
}

ast_t *visitor_string(visitor_t *visitor, ast_t *node){
    
}

ast_t *visitor_compound(visitor_t *visitor, ast_t *node){
    for(int i=0;i<node->compound_size;i++){
        visitor_visit(visitor, node->compound_value[i]);
    }
    return init_ast(AST_NOOP);
}