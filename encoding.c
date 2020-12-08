
#include<stdio.h>
#include<string.h>
#include "encoding.h"

char * CP1252 = "\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff\x80\x81";


void cp1252(char *c1, char **c2) {

    char c = *c1;


    if(c == '\xa1')
        *c2 = "\xc2\xa1"; // ¡
    else if(c == '\xa2')
        *c2 = "\xc2\xa2"; // ¢
    else if(c == '\xa3')
        *c2 = "\xc2\xa3"; // £
    else if(c == '\xa4')
        *c2 = "\xc2\xa4"; // ¤
    else if(c == '\xa5')
        *c2 = "\xc2\xa5"; // ¥
    else if(c == '\xa6')
        *c2 = "\xc2\xa6"; // ¦
    else if(c == '\xa7')
        *c2 = "\xc2\xa7"; // §
    else if(c == '\xa8')
        *c2 = "\xc2\xa8"; // ¨
    else if(c == '\xa9')
        *c2 = "\xc2\xa9"; // ©
    else if(c == '\xaa')
        *c2 = "\xc2\xaa"; // ª
    else if(c == '\xab')
        *c2 = "\xc2\xab"; // «
    else if(c == '\xac')
        *c2 = "\xc2\xac"; // ¬
    else if(c == '\xae')
        *c2 = "\xc2\xae"; // ®
    else if(c == '\xaf')
        *c2 = "\xc2\xaf"; // ¯
    else if(c == '\xb0')
        *c2 = "\xc2\xb0"; // °
    else if(c == '\xb1')
        *c2 = "\xc2\xb1"; // ±
    else if(c == '\xb2')
        *c2 = "\xc2\xb2"; // ²
    else if(c == '\xb3')
        *c2 = "\xc2\xb3"; // ³
    else if(c == '\xb4')
        *c2 = "\xc2\xb4"; // ´
    else if(c == '\xb5')
        *c2 = "\xc2\xb5"; // µ
    else if(c == '\xb6')
        *c2 = "\xc2\xb6"; // ¶
    else if(c == '\xb7')
        *c2 = "\xc2\xb7"; // ·
    else if(c == '\xb8')
        *c2 = "\xc2\xb8"; // ¸
    else if(c == '\xb9')
        *c2 = "\xc2\xb9"; // ¹
    else if(c == '\xba')
        *c2 = "\xc2\xba"; // º
    else if(c == '\xbb')
        *c2 = "\xc2\xbb"; // »
    else if(c == '\xbc')
        *c2 = "\xc2\xbc"; // ¼
    else if(c == '\xbd')
        *c2 = "\xc2\xbd"; // ½
    else if(c == '\xbe')
        *c2 = "\xc2\xbe"; // ¾
    else if(c == '\xbf')
        *c2 = "\xc2\xbf"; // ¿
    else if(c == '\xc0')
        *c2 = "\xc3\x80"; // À
    else if(c == '\xc1')
        *c2 = "\xc3\x81"; // Á
    else if(c == '\xc2')
        *c2 = "\xc3\x82"; // Â
    else if(c == '\xc3')
        *c2 = "\xc3\x83"; // Ã
    else if(c == '\xc4')
        *c2 = "\xc3\x84"; // Ä
    else if(c == '\xc5')
        *c2 = "\xc3\x85"; // Å
    else if(c == '\xc6')
        *c2 = "\xc3\x86"; // Æ
    else if(c == '\xc7')
        *c2 = "\xc3\x87"; // Ç
    else if(c == '\xc8')
        *c2 = "\xc3\x88"; // È
    else if(c == '\xc9')
        *c2 = "\xc3\x89"; // É
    else if(c == '\xca')
        *c2 = "\xc3\x8a"; // Ê
    else if(c == '\xcb')
        *c2 = "\xc3\x8b"; // Ë
    else if(c == '\xcc')
        *c2 = "\xc3\x8c"; // Ì
    else if(c == '\xcd')
        *c2 = "\xc3\x8d"; // Í
    else if(c == '\xce')
        *c2 = "\xc3\x8e"; // Î
    else if(c == '\xcf')
        *c2 = "\xc3\x8f"; // Ï
    else if(c == '\xd0')
        *c2 = "\xc3\x90"; // Ð
    else if(c == '\xd1')
        *c2 = "\xc3\x91"; // Ñ
    else if(c == '\xd2')
        *c2 = "\xc3\x92"; // Ò
    else if(c == '\xd3')
        *c2 = "\xc3\x93"; // Ó
    else if(c == '\xd4')
        *c2 = "\xc3\x94"; // Ô
    else if(c == '\xd5')
        *c2 = "\xc3\x95"; // Õ
    else if(c == '\xd6')
        *c2 = "\xc3\x96"; // Ö
    else if(c == '\xd7')
        *c2 = "\xc3\x97"; // ×
    else if(c == '\xd8')
        *c2 = "\xc3\x98"; // Ø
    else if(c == '\xd9')
        *c2 = "\xc3\x99"; // Ù
    else if(c == '\xda')
        *c2 = "\xc3\x9a"; // Ú
    else if(c == '\xdb')
        *c2 = "\xc3\x9b"; // Û
    else if(c == '\xdc')
        *c2 = "\xc3\x9c"; // Ü
    else if(c == '\xdd')
        *c2 = "\xc3\x9d"; // Ý
    else if(c == '\xde')
        *c2 = "\xc3\x9e"; // Þ
    else if(c == '\xdf')
        *c2 = "\xc3\x9f"; // ß
    else if(c == '\xe0')
        *c2 = "\xc3\xa0"; // à
    else if(c == '\xe1')
        *c2 = "\xc3\xa1"; // á
    else if(c == '\xe2')
        *c2 = "\xc3\xa2"; // â
    else if(c == '\xe3')
        *c2 = "\xc3\xa3"; // ã
    else if(c == '\xe4')
        *c2 = "\xc3\xa4"; // ä
    else if(c == '\xe5')
        *c2 = "\xc3\xa5"; // å
    else if(c == '\xe6')
        *c2 = "\xc3\xa6"; // æ
    else if(c == '\xe7')
        *c2 = "\xc3\xa7"; // ç
    else if(c == '\xe8')
        *c2 = "\xc3\xa8"; // è
    else if(c == '\xe9')
        *c2 = "\xc3\xa9"; // é
    else if(c == '\xea')
        *c2 = "\xc3\xaa"; // ê
    else if(c == '\xeb')
        *c2 = "\xc3\xab"; // ë
    else if(c == '\xec')
        *c2 = "\xc3\xac"; // ì
    else if(c == '\xed')
        *c2 = "\xc3\xad"; // í
    else if(c == '\xee')
        *c2 = "\xc3\xae"; // î
    else if(c == '\xef')
        *c2 = "\xc3\xaf"; // ï
    else if(c == '\xf0')
        *c2 = "\xc3\xb0"; // ð
    else if(c == '\xf1')
        *c2 = "\xc3\xb1"; // ñ
    else if(c == '\xf2')
        *c2 = "\xc3\xb2"; // ò
    else if(c == '\xf3')
        *c2 = "\xc3\xb3"; // ó
    else if(c == '\xf4')
        *c2 = "\xc3\xb4"; // ô
    else if(c == '\xf5')
        *c2 = "\xc3\xb5"; // õ
    else if(c == '\xf6')
        *c2 = "\xc3\xb6"; // ö
    else if(c == '\xf7')
        *c2 = "\xc3\xb7"; // ÷
    else if(c == '\xf8')
        *c2 = "\xc3\xb8"; // ø
    else if(c == '\xf9')
        *c2 = "\xc3\xb9"; // ù
    else if(c == '\xfa')
        *c2 = "\xc3\xba"; // ú
    else if(c == '\xfb')
        *c2 = "\xc3\xbb"; // û
    else if(c == '\xfc')
        *c2 = "\xc3\xbc"; // ü
    else if(c == '\xfd')
        *c2 = "\xc3\xbd"; // ý
    else if(c == '\xfe')
        *c2 = "\xc3\xbe"; // þ
    else if(c == '\xff')
        *c2 = "\xc3\xbf"; // ÿ
    else if(c == '\x80')
        *c2 = "\xe2\x82\xac"; // €
    else if ((unsigned char)c > 127)
        *c1 = '?'; // unknow


    //printf("uchar %i %c %s\n", (unsigned char)c, *c1, *c2);

}



void test_encoding(char *encoding) {

    
    //char *test = 0;
    int len;
    char *name = 0;
    char *text = 0;
    char text2[2048];

    FILE *fw;



    if(strcmp(encoding, "cp1252") == 0) {

        name = "cp1252.txt";

        fw = fopen(name, "w");

        text = CP1252;
        len = strlen(text);

        printf("len:%i\n", len);

        len = encode(text, text2, len);
        text2[len] = 0;
        fwrite(text2, len, 1, fw);


        //printf("%s\n", text2);

        fclose(fw);


    }

    

}



int encode(char*text, char*text2, int len) {
    // cp1252 -> utf-8

    int i, j, k;
    char c1;
    char * c2;

    j = 0;
    i = 0;

    for(; i<len; ) {

        c2 = 0;
        c1 = text[i++];
        cp1252(&c1, &c2);


        if(c2 != 0) {
            //printf("%s\n", c2);
            //printf("zuchar %i %c %s(%i)\n", (unsigned char)c1, c1, c2, (int)strlen(c2));

            k = strlen(c2);
            memcpy(&*(text2+j), c2, k);
            j += k;

            //printf();
            //while(k--) {
            //    text2[j++] = c2[0]; 
            //}

            //text2[j++] = c2[0];    
            //text2[j++] = c2[1];
        }
        else {
            text2[j++] = c1;
        }
    }

    return j;
}







