#include "my_bc.h"
#include <stdio.h>

// simple global error state

static int g_err = 0;

void err_set_parse(void) {
    if (!g_err)
      g_err = 1;
}

const char *err_message(void) {
    if (g_err == 1)
      return "parse error";
    return "";
}

void err_print_and_clear(void) {
    const char *m = err_message();
    if (m && *m) {
        fprintf(stderr, "%s\n", m);
    } 
    g_err = 0;  
}