

#include <stdio.h> 
#include <string.h> 
#include <stdbool.h> 
#include "encoding.h"

#define MAX_FIELDS 200

// 'text      ' -> 'text'
int Clen(char * text, int len) {

    int i;
    for(i=len-1; i>=0; i--) {
        if(text[i] != ' ')
            return i+1;
    }

    return 0;
}

// '   12345' -> '12345'
int Nlen(char * text, int len) {
    int i, n;
    n = 0;
    for(i=len-1; i>=0; i--) {
        if(text[i] == ' ')
            return n;
        n++;
    }

    return 0;
}

int export(char *pathr, char *pathw, char *mode, char *separator, int offset, int limit, char*encoding) {

    FILE *fr; // reader
    FILE *fw; // writer

    bool cmp, deleted;
    char terminator;

    short record_size;
    short columns = 0; 

    unsigned char text[300];
    unsigned char text2[1024];

    int c, r, i, len, size, deleted_count;
    short secure = MAX_FIELDS;
    short columns_order[MAX_FIELDS];
    short columns_max = MAX_FIELDS-1;
    int count;

    void (*coder)(char*,char**);

    if(!separator)
        separator = ";";
    if(!mode)
        mode = "w";

    count = 0;

    struct Field *field;
    struct Field fields[MAX_FIELDS];
    struct Header header; 
    struct Date date;

    fr = fopen(pathr, "r");
    if(!fr) {
        fprintf(stderr, "DBF file not found\n");
        return -1;
    }

    fread(&header, sizeof(struct Header), 1, fr);
    cmp = header.version==0x3; // 0x03 FoxBASE+/Dbase III plus, no memo
    if(!cmp) {
        fprintf(stderr, "No supportes version %i\n", header.version);
        fprintf(stderr, "ONLY 0x03 FoxBASE+/Dbase III plus, no memo\n");
        return -1;
    }

    while(secure--) {
        fread(&terminator, 1, 1, fr);
        cmp = terminator == 0x0D;
        if(cmp)
            break;
        fseek(fr, -1, SEEK_CUR);
        field = &fields[columns++];
        fread(field, sizeof(struct Field), 1, fr);
        record_size += field->length;
    }

    int position = ftell(fr);
    int records = header.records;

    if(position != header.first_record) {
        fprintf(stderr, "Invalid record position\n"); 
        return 0;
    }

    if(strcmp(encoding, "cp437") == 0)
        coder = cp437;
    else if(strcmp(encoding, "cp1252") == 0)
        coder = cp1252;
    else {
        fprintf(stderr, "Default encoding cp1252\n"); 
        coder = cp1252;
    }


    columns_max = columns-1;
    for(c=0; c<=columns_max; c++){
        columns_order[c] = c;
    }



    // Write output.
    if(strcmp(pathw, "stdout") == 0)
        fw = stdout;
    else
        fw = fopen(pathw, mode);

    for(r=0; r<records; r++) {

        if(r < offset)
            continue;
        if(limit > 0 && count >= limit)
            break;

        // Verificar si el registro está marcado para borrar.
        fread(&terminator, 1, 1, fr);
        deleted = (terminator == 0x2A);  // 0x2A -> *

        if(deleted) {
            fseek(fr, record_size, SEEK_CUR);
            deleted_count++;
            continue;
        }

        //for(c=0; c<columns; c++) {
            //field = &fields[c];

        for(i=0; i<=columns_max; i++) {

            c = columns_order[i];
            field = &fields[c];

            text[field->length] = 0;
            size = fread(&text, field->length, 1, fr);
            if(c)
                fwrite(separator, 1, 1, fw);

            if(field->type == 'C') {
                len = Clen(text, field->length);
                len = encode(text, text2, len, coder);
                fwrite(text2, len, 1, fw);
            }
            else if(field->type == 'N') {
                len = Nlen(text, field->length);
                fwrite(text+(field->length-len), len, 1, fw);
            }
            else if(field->type == 'D') {
                cmp = text[0] != ' ';
                if(cmp) {
                    /*
                    memcpy(&date, text, sizeof(struct Date));
                    fwrite(date.y, 4, 1, fw);
                    fwrite("-", 1, 1, fw);
                    fwrite(date.m , 2, 1, fw);
                    fwrite("-", 1, 1, fw);
                    fwrite(date.d , 2, 1, fw);
                    */

                    fwrite(text + 0, 4, 1, fw);
                    fwrite("-", 1, 1, fw);
                    fwrite(text + 4, 2, 1, fw);
                    fwrite("-", 1, 1, fw);
                    fwrite(text + 6, 2, 1, fw);
                }
            }
            else  {
                fprintf(stderr, "Type '%c' no supported\n", field->type);
            }
        }

        fwrite("\n", 1, 1, fw);
        count++;
    }

    fclose(fw);
    fclose(fr);
    printf("COUNT(%i) RECORDS(%i) DELETED(%i) COLUMNS(%i)\n", count, records, deleted_count, columns); 
    return 0;
}


