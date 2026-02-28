#include "my_bc.h"
#include <stdio.h>


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
    int result = eval_rpn(&rpn);
    printf("%d\n", result);

    //success

    vec_free(&tokens);
    vec_free(&rpn);
    return 0;
}