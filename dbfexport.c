
#include<stdio.h>
#include<string.h>
#include "encoding.h"





int main() {

    char c = '\xf1';
    char c2[2];
    
    //cp1252(c, c2);

    //test_encoding("cp1252");
    //test_encoding("cp437");
    //printf("OK %s\n", c2);

    //char *pathr = "/home/jose/Escritorio/SGI/respaldos/credito/20201130/pamovfij.dbf";
    //char *pathw = "/home/jose/Escritorio/proyectos/github/dbfexport/output/new_pamovfijo.txt";

    char *pathr = "/home/jose/Escritorio/SGI/respaldos/credito/20201130/mae_pres.dbf";
    char *pathw = "/home/jose/Escritorio/proyectos/github/dbfexport/output/new_mae_pres.txt";

    export(pathr, pathw);

    return 0;
}

