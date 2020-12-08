
#include<stdio.h>
#include<string.h>
#include "encoding.h"





int main() {

    char c = '\xf1';
    char c2[2];
    
    //cp1252(c, c2);

    test_encoding("cp1252");

    //printf("OK %s\n", c2);
    return 0;
}

