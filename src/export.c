

#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "encoding.h"



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


FIELD* get_field_by_name(FIELDS *fields_reader, char *name) {
    
    int i;
    struct Field *field;
    for(i=0; i<fields_reader->count; i++) {
        field = fields_reader->fields[i];
        if(strcmp(field->name, name) == 0) {
            //printf("%s %i\n", field->name, i);
            return field;
        }
    }

    return NULL;
}



FIELDS* generate_column(FIELDS *fields_reader, char *columns_str) {

    int i, j, m, len;
    char c;
    char field_name[255];

    FIELD *field;
    FIELD *field_new;
    FIELD **fields_new=NULL;
    FIELDS *fields_final;

    short count = 0;
    m = strlen(columns_str)-1;
    i = 0;

    for(j=0; j<=m; j++) {

        c = columns_str[j];
        if(c == ' ' || j == m) {

            len = j-i;
            if(j == m && c != ' ')
                len++;

            if(len) {

                field_name[len] = 0;
                memcpy(field_name, &columns_str[i], len);
                field = get_field_by_name(fields_reader, field_name);

                if(field) {
                    count++;
                    fields_new = (FIELD**)realloc(fields_new, count*sizeof(FIELD*));
                    fields_new[count-1] = field;
                }
            }

            i = j+1;
        }
    }

    fields_final = (FIELDS*)malloc(sizeof(FIELDS));
    fields_final->fields = fields_new;
    fields_final->count = count;
    return fields_final;
}



//int export(char *pathr, char *pathw, char *mode, char *separator, int offset, int limit, char*encoding) {
int export(Params * params) {


    FILE *fr; // reader
    FILE *fw; // writer

    bool cmp, deleted;
    char terminator;
    char * buffer;
    char *separator, *mode;

    short record_size;
    short fields_count = 0; 
    short fields_writer_count = 0;

    unsigned char text[300];
    unsigned char text2[1024];

    int c, r, i, len, size, deleted_count;
    short secure = MAX_FIELDS;
    short columns_order[MAX_FIELDS];
    short columns_max = MAX_FIELDS;
    int count;

    void (*coder)(char*,char**);

    FIELD *field;
    FIELD **fields = NULL;
    FIELDS *fields_reader = (FIELDS*)malloc(sizeof(FIELDS));    
    FIELDS *fields_writer;

    struct Header header; 


    separator = params->separator;
    //mode = params->mode;
    
    /*if(params->separator)

    else
        separator = ";";

    if(params->mode)
        mode = params->mode;
    else
        mode = "w";
    */

    count = 0;

    fr = fopen(params->pathr, "r");
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

        fields_count++;
        fseek(fr, -1, SEEK_CUR);

        field = (FIELD*)malloc(sizeof(FIELD));

        fread(field, sizeof(struct Field), 1, fr);
        record_size += field->length;

        fields = (FIELD**)realloc(fields, fields_count*sizeof(FIELD*));
        fields[fields_count-1] = field;
    }

    fields_reader->fields = fields;
    fields_reader->count = fields_count;
    fields_writer = fields_reader;
    buffer = (char*) malloc((record_size*sizeof(char)));

    int position = ftell(fr);
    int records = header.records;

    if(position != header.first_record) {
        fprintf(stderr, "Invalid record position\n"); 
        return -1;
    }

    if(strcmp(params->encoding, "cp437") == 0)
        coder = cp437;
    else if(strcmp(params->encoding, "cp1252") == 0)
        coder = cp1252;
    else {
        fprintf(stderr, "Default encoding cp1252\n"); 
        coder = cp1252;
    }

    if(params->fields) {
        fields_writer = generate_column(fields_reader, params->fields);
        if(fields_writer->count == 0) {
            fprintf(stderr, "No Columns\n");
            return -1;
        }
    }

    // Write output.
    if(strcmp(params->pathw, "stdout") == 0)
        fw = stdout;
    else
        fw = fopen(params->pathw, params->mode);

    for(r=0; r<records; r++) {

        if(r < params->offset)
            continue;
        if(params->limit > 0 && count >= params->limit)
            break;

        // Verificar si el registro está marcado para borrar.
        fread(&terminator, 1, 1, fr);
        deleted = (terminator == 0x2A);  // 0x2A -> *

        if(deleted) {
            fseek(fr, record_size, SEEK_CUR);
            deleted_count++;
            continue;
        }

        // read        
        fread(buffer, record_size, 1, fr);
        for(c=0; c<fields_writer->count; c++) {

            field = fields_writer->fields[c];
            text[field->length] = 0;
            strncpy(text, buffer+field->displacement-1, field->length);

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
                    fwrite(text + 0, 4, 1, fw);
                    fwrite("-", 1, 1, fw);
                    fwrite(text + 4, 2, 1, fw);
                    fwrite("-", 1, 1, fw);
                    fwrite(text + 6, 2, 1, fw);
                }
            }
            else  {
                //fprintf(stderr, "Type '%c' no supported\n", field->type);
            }
        }

        fwrite("\n", 1, 1, fw);
        count++;
    }

    fclose(fw);
    fclose(fr);
    printf("COUNT(%i) RECORDS(%i) DELETED(%i) FIELDS(%i)\n", count, records, deleted_count, fields_count); 
    return 0;
}


