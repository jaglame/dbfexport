
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



#include "encoding.h"





int main(int argc, char * argv[]) {

    int i;
    char *pathr = 0;
    char *pathw = "stdout";
    char *separator = "|";
    char *encoding = "cp1252";
    int limit=-1, offset=0;

    //printf("Argument count=%d\n", argc);
    for (i = 0; i < argc; i++) {
        //printf("Argument %s\n", argv[i]);

        if(i == 1) {
            pathr = argv[1];
        }
        else if (strcmp(argv[i], "-w") == 0) {
            pathw = argv[++i];
        }
        else if (strcmp(argv[i], "--separator") == 0) {
            separator = argv[++i];
            if(strcmp(separator, "\\t") == 0) // TAB
                separator = "\t";
        }
        else if (strcmp(argv[i], "--limit") == 0) {
            limit = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--offset") == 0) {
            offset = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--encoding") == 0) {
            encoding = argv[++i];
        }
    }

    //printf("(%s) (%s) (%s) (%i) (%i)\n", pathr, pathw, separator, offset, limit);
    //test_encoding("cp1252");
    //test_encoding("cp437");
    //char *pathr = "/home/jose/Escritorio/SGI/respaldos/credito/20201130/pamovfij.dbf";
    //char *pathw = "/home/jose/Escritorio/proyectos/github/dbfexport/output/new_pamovfijo.txt";
    //char *pathr = "/home/jose/Escritorio/SGI/respaldos/credito/20201130/mae_pres.dbf";
    //char *pathw = "/home/jose/Escritorio/proyectos/github/dbfexport/output/new_mae_pres.txt";
    export(pathr, pathw, separator, offset, limit, encoding);
    return 0;
}

