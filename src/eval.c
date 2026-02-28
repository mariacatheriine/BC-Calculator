#include "my_bc.h"

// evaluate rpn expression, return result

int eval_rpn(const t_vec *rpn)
{
    t_vec stack;
    vec_init(&stack, sizeof(int));

    for (size_t i = 0; i < rpn->size; i++)
    {
        t_token tk = *(t_token*)((char*)rpn->data + i * rpn->elem);

        if (tk.type == TOK_INT)
        {
            vec_push(&stack, &tk.ival);
        }
        else if (tk.type == TOK_OP)
        {
            int b = *(int*)vec_back(&stack);
            vec_pop(&stack);

            int a = *(int*)vec_back(&stack);
            vec_pop(&stack);

            int result;

            if (tk.op == '+')
                result = a + b;
            else if (tk.op == '-')
                result = a - b;
            else if (tk.op == '*')
                result = a * b;
            else if (tk.op == '/')
                result = a / b;
            else if (tk.op == '%')
                result = a % b;
            else
                result = 0;

            vec_push(&stack, &result);
        }
    }

    int final = *(int*)vec_back(&stack);
    vec_free(&stack);
    return final;
}