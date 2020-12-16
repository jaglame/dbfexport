#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "dbfexport.h"

// 'text      ' -> 'text'
// ' text      ' -> ' text'
int Clen(char * text, int len) {

    int i;
    for(i=len-1; i>=0; i--) {
        if(text[i] != ' ')
            break;
    }

    return i+1;
}

// '   12345' -> '12345'
int Nlen(char * text, int len) {
    int i, n;
    n = 0;
    for(i=len-1; i>=0; i--) {
        if(text[i] == ' ')
            break;
        n++;
    }

    return n; // len-i-1
}

Field* get_field_by_name(Fields *fields_reader, char *name) {
    
    int i;
    Field *field;
    for(i=0; i<fields_reader->count; i++) {
        field = fields_reader->fields[i];
        if(strcmp(field->name, name) == 0) {
            //printf("%s %i\n", field->name, i);
            return field;
        }
    }

    return NULL;
}

Fields* generate_fields(Fields *fields_reader, char *columns_str) {

    int i, j, m, len;
    char c;
    char field_name[255];

    Field *field;
    Field *field_new;
    Field **fields_new=NULL;
    Fields *fields_final;

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
                    fields_new = (Field**)realloc(fields_new, count*sizeof(Field*));
                    fields_new[count-1] = field;
                }
            }

            i = j+1;
        }
    }

    fields_final = (Fields*)malloc(sizeof(Fields));
    fields_final->fields = fields_new;
    fields_final->count = count;
    return fields_final;
}

int export(Params *params) {

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

    int col, row, i, len, size, deleted_count;
    short secure = MAX_FIELDS;
    short columns_order[MAX_FIELDS];
    short columns_max = MAX_FIELDS;
    int count;
    void (*coder)(char*,char**); // encoding

    Field *field;
    Field **fields = NULL;
    Fields *fields_reader = (Fields*)malloc(sizeof(Fields));    
    Fields *fields_writer;
    Header header; 

    separator = params->separator;
    count = 0;

    fr = fopen(params->pathr, "r");
    if(!fr) {
        fprintf(stderr, "DBF file not found\n");
        return -1;
    }

    fread(&header, sizeof(Header), 1, fr);
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

        field = (Field*)malloc(sizeof(Field));

        fread(field, sizeof(Field), 1, fr);
        record_size += field->length;

        fields = (Field**)realloc(fields, fields_count*sizeof(Field*));
        fields[fields_count-1] = field;
    }

    fields_reader->fields = fields;
    fields_reader->count = fields_count;
    fields_writer = fields_reader;
    buffer = (char*)malloc((record_size*sizeof(char)));

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
        fields_writer = generate_fields(fields_reader, params->fields);
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

    for(row=0; row<records; row++) {

        if(row < params->offset)
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
        for(col=0; col<fields_writer->count; col++) {

            field = fields_writer->fields[col];
            text[field->length] = 0;
            strncpy(text, buffer+field->displacement-1, field->length);

            if(col)
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


