#include<stdio.h>
int main(int argc,char* argv[]){if(argc<2)return 1;FILE *fp=fopen(argv[1],"r");unsigned char buf=0;int ptr=0;int c;while((c=fgetc(fp))!=EOF){switch(c){case'>':ptr=(ptr+1)%8;break;case'+':buf^=1<<(7-ptr);break;case'.':putchar(buf);buf=0;ptr=0;break;}}fclose(fp);return 0;}
