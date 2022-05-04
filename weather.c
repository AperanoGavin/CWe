#include <stdio.h>
#include <stdlib.h>
#include "include/api_call.c"
#include "include/json_parse.c"

int main(int argc, char **argv) {
    get_json();
    json_parse();
    
    return 0;
}
