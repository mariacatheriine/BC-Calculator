#include "my_bc.h"
#include <stdio.h>

/*
int main(int argc, char **argv) {
    if (argc != 2){
        err_set_parse();
        err_print_and_clear();
        return 1;
    }
    (void)argv;

    // vector tokens, vector rpn
    t_vec tokens, rpn;
    vec_init(&tokens, sizeof(t_token));
    vec_init(&rpn, sizeof(t_token));

    // lexer
    if (lex(argv[1], &tokens) != 0) {
        err_print_and_clear();
        vec_free(&tokens);
        vec_free(&rpn);
        return 1;
    }

    // shunting yard -> rpn
    if (to_rpn(&tokens, &rpn) != 0) {
        err_print_and_clear();
        vec_free(&tokens);
        vec_free(&rpn);
        return 1;
    }

    // evaluate rpn

    //success

    vec_free(&tokens);
    vec_free(&rpn);
    return 0;
}*/
int main(int argc, char **argv)
{
    printf("START\n");

    printf("argc = %d\n", argc);

    if (argc != 2)
    {
        printf("Wrong argc\n");
        return 0;
    }

    printf("Input: %s\n", argv[1]);

    // After lexer
    printf("After lexer\n");

    // After shunting
    printf("After shunting\n");

    // After evaluation
    printf("After eval\n");

    return 0;
}