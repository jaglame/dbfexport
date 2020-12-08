
#include<stdio.h>
#include<string.h>
#include "encoding.h"

char * CP1252 = "\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff\x80\x81";
char * CP437 = "\xad\x9b\x9c\x9d\xa6\xae\xaa\xf8\xf1\xfd\xe6\xfa\xa7\xaf\xac\xab\xa8\x8e\x8f\x92\x80\x90\xa5\x99\x9a\xe1\x85\xa0\x83\x84\x86\x91\x87\x8a\x82\x88\x89\x8d\xa1\x8c\x8b\xa4\x95\xa2\x93\x94\xf6\x97\xa3\x96\x81\x98\xcd";


void cp1252(char *c1, char **c2) {

    char c = *c1;
    char *p = 0;

    if(c == '\xa1')
        p = "\xc2\xa1"; // ¡
    else if(c == '\xa2')
        p = "\xc2\xa2"; // ¢
    else if(c == '\xa3')
        p = "\xc2\xa3"; // £
    else if(c == '\xa4')
        p = "\xc2\xa4"; // ¤
    else if(c == '\xa5')
        p = "\xc2\xa5"; // ¥
    else if(c == '\xa6')
        p = "\xc2\xa6"; // ¦
    else if(c == '\xa7')
        p = "\xc2\xa7"; // §
    else if(c == '\xa8')
        p = "\xc2\xa8"; // ¨
    else if(c == '\xa9')
        p = "\xc2\xa9"; // ©
    else if(c == '\xaa')
        p = "\xc2\xaa"; // ª
    else if(c == '\xab')
        p = "\xc2\xab"; // «
    else if(c == '\xac')
        p = "\xc2\xac"; // ¬
    else if(c == '\xae')
        p = "\xc2\xae"; // ®
    else if(c == '\xaf')
        p = "\xc2\xaf"; // ¯
    else if(c == '\xb0')
        p = "\xc2\xb0"; // °
    else if(c == '\xb1')
        p = "\xc2\xb1"; // ±
    else if(c == '\xb2')
        p = "\xc2\xb2"; // ²
    else if(c == '\xb3')
        p = "\xc2\xb3"; // ³
    else if(c == '\xb4')
        p = "\xc2\xb4"; // ´
    else if(c == '\xb5')
        p = "\xc2\xb5"; // µ
    else if(c == '\xb6')
        p = "\xc2\xb6"; // ¶
    else if(c == '\xb7')
        p = "\xc2\xb7"; // ·
    else if(c == '\xb8')
        p = "\xc2\xb8"; // ¸
    else if(c == '\xb9')
        p = "\xc2\xb9"; // ¹
    else if(c == '\xba')
        p = "\xc2\xba"; // º
    else if(c == '\xbb')
        p = "\xc2\xbb"; // »
    else if(c == '\xbc')
        p = "\xc2\xbc"; // ¼
    else if(c == '\xbd')
        p = "\xc2\xbd"; // ½
    else if(c == '\xbe')
        p = "\xc2\xbe"; // ¾
    else if(c == '\xbf')
        p = "\xc2\xbf"; // ¿
    else if(c == '\xc0')
        p = "\xc3\x80"; // À
    else if(c == '\xc1')
        p = "\xc3\x81"; // Á
    else if(c == '\xc2')
        p = "\xc3\x82"; // Â
    else if(c == '\xc3')
        p = "\xc3\x83"; // Ã
    else if(c == '\xc4')
        p = "\xc3\x84"; // Ä
    else if(c == '\xc5')
        p = "\xc3\x85"; // Å
    else if(c == '\xc6')
        p = "\xc3\x86"; // Æ
    else if(c == '\xc7')
        p = "\xc3\x87"; // Ç
    else if(c == '\xc8')
        p = "\xc3\x88"; // È
    else if(c == '\xc9')
        p = "\xc3\x89"; // É
    else if(c == '\xca')
        p = "\xc3\x8a"; // Ê
    else if(c == '\xcb')
        p = "\xc3\x8b"; // Ë
    else if(c == '\xcc')
        p = "\xc3\x8c"; // Ì
    else if(c == '\xcd')
        p = "\xc3\x8d"; // Í
    else if(c == '\xce')
        p = "\xc3\x8e"; // Î
    else if(c == '\xcf')
        p = "\xc3\x8f"; // Ï
    else if(c == '\xd0')
        p = "\xc3\x90"; // Ð
    else if(c == '\xd1')
        p = "\xc3\x91"; // Ñ
    else if(c == '\xd2')
        p = "\xc3\x92"; // Ò
    else if(c == '\xd3')
        p = "\xc3\x93"; // Ó
    else if(c == '\xd4')
        p = "\xc3\x94"; // Ô
    else if(c == '\xd5')
        p = "\xc3\x95"; // Õ
    else if(c == '\xd6')
        p = "\xc3\x96"; // Ö
    else if(c == '\xd7')
        p = "\xc3\x97"; // ×
    else if(c == '\xd8')
        p = "\xc3\x98"; // Ø
    else if(c == '\xd9')
        p = "\xc3\x99"; // Ù
    else if(c == '\xda')
        p = "\xc3\x9a"; // Ú
    else if(c == '\xdb')
        p = "\xc3\x9b"; // Û
    else if(c == '\xdc')
        p = "\xc3\x9c"; // Ü
    else if(c == '\xdd')
        p = "\xc3\x9d"; // Ý
    else if(c == '\xde')
        p = "\xc3\x9e"; // Þ
    else if(c == '\xdf')
        p = "\xc3\x9f"; // ß
    else if(c == '\xe0')
        p = "\xc3\xa0"; // à
    else if(c == '\xe1')
        p = "\xc3\xa1"; // á
    else if(c == '\xe2')
        p = "\xc3\xa2"; // â
    else if(c == '\xe3')
        p = "\xc3\xa3"; // ã
    else if(c == '\xe4')
        p = "\xc3\xa4"; // ä
    else if(c == '\xe5')
        p = "\xc3\xa5"; // å
    else if(c == '\xe6')
        p = "\xc3\xa6"; // æ
    else if(c == '\xe7')
        p = "\xc3\xa7"; // ç
    else if(c == '\xe8')
        p = "\xc3\xa8"; // è
    else if(c == '\xe9')
        p = "\xc3\xa9"; // é
    else if(c == '\xea')
        p = "\xc3\xaa"; // ê
    else if(c == '\xeb')
        p = "\xc3\xab"; // ë
    else if(c == '\xec')
        p = "\xc3\xac"; // ì
    else if(c == '\xed')
        p = "\xc3\xad"; // í
    else if(c == '\xee')
        p = "\xc3\xae"; // î
    else if(c == '\xef')
        p = "\xc3\xaf"; // ï
    else if(c == '\xf0')
        p = "\xc3\xb0"; // ð
    else if(c == '\xf1')
        p = "\xc3\xb1"; // ñ
    else if(c == '\xf2')
        p = "\xc3\xb2"; // ò
    else if(c == '\xf3')
        p = "\xc3\xb3"; // ó
    else if(c == '\xf4')
        p = "\xc3\xb4"; // ô
    else if(c == '\xf5')
        p = "\xc3\xb5"; // õ
    else if(c == '\xf6')
        p = "\xc3\xb6"; // ö
    else if(c == '\xf7')
        p = "\xc3\xb7"; // ÷
    else if(c == '\xf8')
        p = "\xc3\xb8"; // ø
    else if(c == '\xf9')
        p = "\xc3\xb9"; // ù
    else if(c == '\xfa')
        p = "\xc3\xba"; // ú
    else if(c == '\xfb')
        p = "\xc3\xbb"; // û
    else if(c == '\xfc')
        p = "\xc3\xbc"; // ü
    else if(c == '\xfd')
        p = "\xc3\xbd"; // ý
    else if(c == '\xfe')
        p = "\xc3\xbe"; // þ
    else if(c == '\xff')
        p = "\xc3\xbf"; // ÿ
    else if(c == '\x80')
        p = "\xe2\x82\xac"; // €

    if(p)
        *c2 = p;
    else if ((unsigned char)c > 127)
        *c1 = '?'; // unknow

}



void cp437(char *c1, char **c2) {

    char c = *c1;
    char *p = 0;

    if(c == '\xad')
        p = "\xc2\xa1"; // ¡
    else if(c == '\x9b')
        p = "\xc2\xa2"; // ¢
    else if(c == '\x9c')
        p = "\xc2\xa3"; // £
    else if(c == '\x9d')
        p = "\xc2\xa5"; // ¥
    else if(c == '\xa6')
        p = "\xc2\xaa"; // ª
    else if(c == '\xae')
        p = "\xc2\xab"; // «
    else if(c == '\xaa')
        p = "\xc2\xac"; // ¬
    else if(c == '\xf8')
        p = "\xc2\xb0"; // °
    else if(c == '\xf1')
        p = "\xc2\xb1"; // ±
    else if(c == '\xfd')
        p = "\xc2\xb2"; // ²
    else if(c == '\xe6')
        p = "\xc2\xb5"; // µ
    else if(c == '\xfa')
        p = "\xc2\xb7"; // ·
    else if(c == '\xa7')
        p = "\xc2\xba"; // º
    else if(c == '\xaf')
        p = "\xc2\xbb"; // »
    else if(c == '\xac')
        p = "\xc2\xbc"; // ¼
    else if(c == '\xab')
        p = "\xc2\xbd"; // ½
    else if(c == '\xa8')
        p = "\xc2\xbf"; // ¿
    else if(c == '\x8e')
        p = "\xc3\x84"; // Ä
    else if(c == '\x8f')
        p = "\xc3\x85"; // Å
    else if(c == '\x92')
        p = "\xc3\x86"; // Æ
    else if(c == '\x80')
        p = "\xc3\x87"; // Ç
    else if(c == '\x90')
        p = "\xc3\x89"; // É
    else if(c == '\xa5')
        p = "\xc3\x91"; // Ñ
    else if(c == '\x99')
        p = "\xc3\x96"; // Ö
    else if(c == '\x9a')
        p = "\xc3\x9c"; // Ü
    else if(c == '\xe1')
        p = "\xc3\x9f"; // ß
    else if(c == '\x85')
        p = "\xc3\xa0"; // à
    else if(c == '\xa0')
        p = "\xc3\xa1"; // á
    else if(c == '\x83')
        p = "\xc3\xa2"; // â
    else if(c == '\x84')
        p = "\xc3\xa4"; // ä
    else if(c == '\x86')
        p = "\xc3\xa5"; // å
    else if(c == '\x91')
        p = "\xc3\xa6"; // æ
    else if(c == '\x87')
        p = "\xc3\xa7"; // ç
    else if(c == '\x8a')
        p = "\xc3\xa8"; // è
    else if(c == '\x82')
        p = "\xc3\xa9"; // é
    else if(c == '\x88')
        p = "\xc3\xaa"; // ê
    else if(c == '\x89')
        p = "\xc3\xab"; // ë
    else if(c == '\x8d')
        p = "\xc3\xac"; // ì
    else if(c == '\xa1')
        p = "\xc3\xad"; // í
    else if(c == '\x8c')
        p = "\xc3\xae"; // î
    else if(c == '\x8b')
        p = "\xc3\xaf"; // ï
    else if(c == '\xa4')
        p = "\xc3\xb1"; // ñ
    else if(c == '\x95')
        p = "\xc3\xb2"; // ò
    else if(c == '\xa2')
        p = "\xc3\xb3"; // ó
    else if(c == '\x93')
        p = "\xc3\xb4"; // ô
    else if(c == '\x94')
        p = "\xc3\xb6"; // ö
    else if(c == '\xf6')
        p = "\xc3\xb7"; // ÷
    else if(c == '\x97')
        p = "\xc3\xb9"; // ù
    else if(c == '\xa3')
        p = "\xc3\xba"; // ú
    else if(c == '\x96')
        p = "\xc3\xbb"; // û
    else if(c == '\x81')
        p = "\xc3\xbc"; // ü
    else if(c == '\x98')
        p = "\xc3\xbf"; // ÿ

    if(p)
        *c2 = p;
    else if ((unsigned char)c > 127)
        *c1 = '?'; // unknow
}


int encode(char*text, char*text2, int len, void (*coder)(char*, char**)) {
    // cp1252 -> utf-8

    int i, j, k;
    char c1;
    char * c2;

    j = 0;
    i = 0;

    for(; i<len; ) {

        c2 = 0;
        c1 = text[i++];
        coder(&c1, &c2);

        if(c2 != 0) {
            k = strlen(c2);
            //memcpy(&*(text2+j), c2, k);
            memcpy(&(text2[j]), c2, k);
            j += k;
        }
        else {
            text2[j++] = c1;
        }
    }

    return j;
}



void test_encoding(char *encoding) {

    int len;
    char *name = 0;
    char *text = 0;
    char text2[2048];
    void (*coder)(char*,char**);

    FILE *fw;

    // cp437

    if(strcmp(encoding, "cp1252") == 0) {
        name = "cp1252.txt";
        text = CP1252;
        coder = cp1252;
    }
    else if(strcmp(encoding, "cp437") == 0) {
        name = "cp437.txt";
        text = CP437;
        coder = cp437;
    }

    if(name) {
        fw = fopen(name, "w");
        len = encode(text, text2, (int)strlen(text), coder);
        text2[len] = 0;
        fwrite(text2, len, 1, fw);
        fclose(fw);
    }
}



