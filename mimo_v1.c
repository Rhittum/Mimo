#include<stdio.h>

int main(int argc,char* argv[]){
	if(argc<2) return 1;
	FILE *fp=fopen(argv[1],"r");

	unsigned char buf=0;

	long jump=-1, stack[32];
	int ptr=0, c, sp=0;
	while((c=fgetc(fp)) != EOF) {
		switch(c) {
			case '>':
				ptr=(ptr+1)%8;
				break;
			case '+':
				buf^=1<<(7-ptr);
				break;
			case ':':
				stack[sp++]=jump=ftell(fp);
				break;
			case '?':
				if (buf>48 && jump!=-1){
					buf--;
					fseek(fp, stack[sp-1], SEEK_SET);
				} else if (sp>0) sp--;
				break;
			case '.':
				putchar(buf);
				break;
		}
	}
	fclose(fp);
	return 0;
}
