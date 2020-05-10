#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/token.h"
#include "include/parser.h"

int main(int argc, char *argv[]) {
    // char *content = "pub fun main() {\n"
    //                     "\tprint(\"hello\")\n"
    //                 "}";
    // char *content = "\"main\"";
    char *content = "var nome = \"john doe\"\n;"
                    "print(name);";
                    

    lexer_t *lexer = init_lexer(content);
    parser_t *parser = init_parser(lexer);
    ast_t *root = parser_parse(parser);
    

    // printf("%d\n",root->type);
    // printf("%lu\n",root->compound_size);

    return 0;
}