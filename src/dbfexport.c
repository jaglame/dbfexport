
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "dbfexport.h"

int main(int argc, char * argv[]) {

    int i;
    char *pathr = 0;
    char *pathw = "stdout";
    char *separator = "|";
    char *encoding = "cp1252";
    char *mode = "w";
    char *fields = 0;
    int limit=-1, offset=0;
    Params params;

    //printf("Argument count=%d\n", argc);
    for (i = 0; i < argc; i++) {
        //printf("Argument %s\n", argv[i]);

        if(i == 1) {
            pathr = argv[1];
        }
        else if (strcmp(argv[i], "-out") == 0) {
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
        else if (strcmp(argv[i], "--append") == 0) {
            mode = "a";
        }
        else if (strcmp(argv[i], "--fields") == 0) {
            fields = argv[++i];
        }
    }

    params.pathr = pathr;
    params.pathw = pathw;
    params.mode = mode;
    params.separator = separator;
    params.offset = offset;
    params.limit = limit;
    params.encoding = encoding;
    params.fields = fields;
    return export(&params);
}

