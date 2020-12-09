

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
    short col_max;

    FIELD *field;
    FIELD *field_new;
    //FIELD fields_new[fields_reader->count];

    FIELD **fields_new=NULL;

    short count = 0;

    //short, i, j, m, len, index;    
    //fields_writer = (struct Field*) malloc((2*sizeof(struct Field)));
    //fields_writer[0] = fields[0];
    //fields_writer[1] = fields[0];
    //fields_writer_count = 2;


    col_max = 0;
    m = strlen(columns_str)-1;
    i = 0;


    for(j=0; j<=m; j++) {

        c = columns_str[j];
        if(c == ' ' || j == m) {
            //printf("%i -> %i (%c)\n", j, m, columns[j]);
            //memcpy(person.name, myname, strlen(myname)+1 );


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

                    field_new = fields_new[count-1];
                    //strcpy(field_new->name, field->name);
                    //field_new->length = field->displacement;
                    //field_new->length = field->length;

                    //printf("NAME(out): %s\n", field_new->name);
                }
            }

            i = j+1;
        }
    }

    //FIELDS fields_r;
    //fields_r.fields = fields_new;
    //fields_r.count = count;
    //FIELDS *fields_2 = &fields_r;  
    //return fields_2;
    // str = (char *) malloc(15);




    FIELDS * fields_final = (FIELDS*)malloc(sizeof(FIELDS));
    fields_final->fields = fields_new;
    fields_final->count = count;


    int z;
    for(z=0; z<count; z++) {
        printf("NAME(out.xx): %s\n", fields_final->fields[z]->name);
    }


    //printf("%d\n", (long)&fields_final);
    return fields_final;

    //return fields_2;

    //return fields_writer; // new columns_max
}



int export(char *pathr, char *pathw, char *mode, char *separator, int offset, int limit, char*encoding) {

    FILE *fr; // reader
    FILE *fw; // writer

    bool cmp, deleted;
    char terminator;
    char * buffer;

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
    //FIELD fields[MAX_FIELDS];

    //FIELDS * fields = (FIELDS*)malloc(sizeof(FIELDS));

    FIELD **fields = NULL;

    //FIELD **fields = (FIELD**)malloc(MAX_FIELDS*sizeof(FIELD*)); // pointers.



    FIELDS *fields_reader = (FIELDS*)malloc(sizeof(FIELDS));    
    FIELDS *fields_writer;

    struct Header header; 


    //struct Date date;
    //struct Field *fields_writer;




    if(!separator)
        separator = ";";
    if(!mode)
        mode = "w";

    count = 0;



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

        fields_count++;

        fseek(fr, -1, SEEK_CUR);
        //field = &fields[fields_count++];


        field = (FIELD*)malloc(sizeof(FIELD));

        fread(field, sizeof(struct Field), 1, fr);
        record_size += field->length;

        fields = (FIELD**)realloc(fields, fields_count*sizeof(FIELD*));
        fields[fields_count-1] = field;


        //printf("displacement: %i %i\n", field->displacement, field->length);

    }

    fields_reader->fields = fields;
    fields_reader->count = fields_count;
    fields_writer = fields_reader;

    //printf("%i\n", fields_count);
    //for(c=0; c<fields_writer->count; c++) {
    //    printf("%s\n", fields_writer->fields[c]->name);
    //}
    //return 0;
    //buffer = malloc();



    //fields_writer = fields;
    //fields_writer_count = fields_count;

    buffer = (char*) malloc((record_size*sizeof(char))); /*+1 for '\0' character */

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



    //fields_writer = &fields_reader;


    /*
    fields_writer = (struct Field*) malloc((2*sizeof(struct Field)));
    fields_writer[0] = fields[0];
    fields_writer[1] = fields[0];
    fields_writer_count = 2;
    */


    //printf("%s\n", fields_writer[0].name);
    //return 0;

    //columns_max = columns;
    //for(c=0; c<columns_max; c++){
    //    columns_order[c] = c;
    //}



    //char * columns_str = "A_SOCIO A_NRO_PRE A_FEC_PRE A_MONT_PRE A_CUOTA A_PLAZO A_SDO_PRE A_POR_INTE A_POR_MULT A_RUBRO A_ACU_CUOT A_ACU_PAGO A_ACU_INTE  A_NRO_REFI A_FEC_DESD A_RELACION";
    char * columns_str = "A_SOCIO A_NRO_PRE A_SOCIO A_SOCIO";
    //char * columns_str = "A_NRO_PRE A_SOCIO A_SOCIO";
    //columns_max = generate_column(fields, columns_order, columns_txt, columns_max);
    //printf("%i %i\n", columns_max, columns_order[0]);


    //FIELDS * xfields;

        
    fields_writer = generate_column(fields_reader, columns_str);


    printf("count(%i)\n", fields_writer->count);
    printf("count(%i)\n", fields_writer->count);
    printf("count(%i)\n", fields_writer->count);
    printf("count(%i)\n", fields_writer->count);

    if(fields_writer->count > 0) {

        for(c=0; c<fields_writer->count; c++) {

            //printf("%s of %i\n", fields_writer->fields[c].name, fields_writer->count);
            printf("xxx%s\n", fields_writer->fields[c]->name);

        }        
    }
    else {
        fprintf(stderr, "No Columns\n");
        return -1;
    }

    

    //printf("FINAL?--> () %i\n", fields_writer->count);

    //return 0;




    //int xxx = sizeof(fields_writer) / sizeof(FIELD);
    //int xxx = sizeof(*fields_writer)  / sizeof(int);
    //return 0;

    // Write output.
    if(strcmp(pathw, "stdout") == 0)
        fw = stdout;
    else
        fw = fopen(pathw, mode);


    

    //fields_writer_count = fields_writer.count;



    //printf("FINAL?--> () %i\n", fields_writer->count);

    for(r=0; r<records; r++) {

        
        //printf("FINAL?--> () %i\n", fields_writer->count);

        //continue;

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
        
        fread(buffer, record_size, 1, fr);


        //printf("FINAL?--> () %i\n", fields_writer->count);
        //continue;
 


        for(c=0; c<fields_writer->count; c++) {




            //field = &fields[c];
            //field = &fields_writer[c];
            field = fields_writer->fields[c];
            text[field->length] = 0;
            strncpy(text, buffer+field->displacement-1, field->length);

            //printf("%s %s\n", field->name, text);

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

            //printf("%s\n", text);
            


        }

        fwrite("\n", 1, 1, fw);

        //printf("buffer-> %s", buffer);

        /*        
        for(c=0; c<columns; c++) {
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
        */



        count++;
    }

    fclose(fw);
    fclose(fr);
    printf("COUNT(%i) RECORDS(%i) DELETED(%i) FIELDS(%i)\n", count, records, deleted_count, fields_count); 
    return 0;
}


