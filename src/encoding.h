



#define MAX_FIELDS 200
#define FIELD struct Field
#define FIELDS struct Fields

struct Header { 
    char version; 
    char year; 
    char month;
    char day;  
    int  records;
    short first_record;
    short length_record; // Length of one data record, including delete flag
    char data2[16]; // Reserved
    char data3; // Table flags
    char data4; // Code page mark
    short data5; // Reserved, contains 0x00
}; 

struct Field {
    char name[11];
    char type;
    unsigned int displacement; // Displacement of field in record
    unsigned char length;
    unsigned char decimal;
    unsigned char flags; // Field flags:
    char data1[4];  // Value of autoincrement Next value
    char data2;  // Value of autoincrement Step value
    char data3[8];  // Reserved                                                                                                                                                                                                                                                                
};

struct Fields {
    struct Field **fields;
    int count;
};

struct Date {
    char y[4];
    char m[2];
    char d[2];
};


typedef struct {
    char *pathr;
    char *pathw;
    char *mode;
    char *separator;
    int offset;
    int limit;
    char *encoding;
    char *fields;
}Params;

void cp1252(char*, char**);
void cp437(char*, char**);
int encode(char*, char*, int, void (*)(char*, char**));
void test_encoding(char*);
//int export(char*, char*, char*, char*, int, int, char*);
int export(Params*);



