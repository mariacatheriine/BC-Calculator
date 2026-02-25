#include "my_bc.h"
#include <ctype.h>

/*
LEXER (string -> tokens)

Tasks: 
   - parse integers (base 10)
   - recognize ops: + - * / % ( )
   - skip spaces
   - detect unary + / -:
       * beginning of input
       * after '('
       * after another operator 
Unary: 
   '`' => unary plus
   '~' => unary minus
Parse errors
*/

static int push_int(t_vec *out, long long v){
    t_token t;
    t.type = TOK_INT;
    t.ival = v;
    t.op = 0;
    t.precedence = 0;
    t.assoc = ASSOC_LEFT;
    return vec_push(out, &t); 
}

static int push_paren(t_vec *out, int left){
    t_token t;
    t.type = left ? TOK_LPAREN : TOK_RPAREN;
    t.ival = 0;
    t.op = 0;
    t.precedence = 0;
    t.assoc = ASSOC_LEFT;
    return vec_push(out, &t);
}

static int push_op(t_vec *out, char op, int unary){
    t_token t;
    t.type = TOK_OP;
    t.ival = 0;
    t.assoc = ASSOC_LEFT;

    if (unary){
        // map to synctatic unary op symbols, highest precedence, right-assoc
        if (op == '-')
          t.op = '~'; // unary minus
        else if (op == '+')
          t.op = '`'; // unary plus
        else{
            err_set_parse();
            return -1;
        }
        t.precedence = 3;
        t.assoc = ASSOC_RIGHT;
    }
    else{
        t.op = op;
        if (op == '*' || op == '/' || op == '%'){
            t.precedence = 2;
            t.assoc = ASSOC_LEFT;
        }
        else { // + -
            t.precedence = 1;
            t.assoc = ASSOC_LEFT;
        }
    }
    return vec_push(out, &t);
}

int lex(const char *s, t_vec *out_tokens){
    size_t i = 0;
    int expect_unary = 1; 

    while (s[i]){
        // space?
        if (isspace((unsigned char)s[i])){
            i++;
            continue;
        }
        // digits?
        if (isdigit((unsigned char)s[i])){
            // parse a positive int literal; unary sign handled as an operator token
            long long v = 0;
            while (isdigit((unsigned char)s[i])){
                v = v * 10 + (s[i] - '0');
                i++;
            }
            if (push_int(out_tokens, v) != 0){
                err_set_parse();
                return -1;
            }
            expect_unary = 0; // after a number, following -, + binary
        } else if (s[i] == '+' || s[i] == '-'){
            if (push_op(out_tokens, s[i], expect_unary) != 0) {
                err_set_parse();
                return -1;
            }
            i++;
            // after any op, next could be unary
            expect_unary = 1;
        }
        else if(s[i] == '*' || s[i] == '/' || s[i] == '%'){ // * / %
            // these cannot be unary
            if (expect_unary) {
                err_set_parse();
                return -1;
            }
            if (push_op(out_tokens, s[i], 0) != 0){
                err_set_parse();
                return -1;
            }
            i++;
            expect_unary = 1;
        }
        else if (s[i] == '('){ // (
            if (push_paren(out_tokens, 1) != 0){
                err_set_parse();
                return -1;
            }
            i++;
            expect_unary = 1;
        }
        else if(s[i] == ')'){ // )
            if (push_paren(out_tokens, 0) != 0){
                err_set_parse();
                return -1;
            }
            i++;
            expect_unary = 1;
        }
        else { // unknown char: parse error 
            err_set_parse();
            return -1;
        }
    }
    return 0;
}