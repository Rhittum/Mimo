#include<stdio.h>
#include <string.h>

int main(int argc,char* argv[]){
	if(argc<2) return 1;
	FILE *fp=fopen(argv[1],"r");
	if(!fp) return 1;

	unsigned char buf[300];
	char code[300];
	memset(buf,48,300);
	int code_len = fread(code,1,300,fp);

	int stack[32];
	int ptr=0, pc=0, sp=0, mov=1;
	while(pc<code_len) {
		char c = code[pc++];
		switch(c) {
			case '>':
				ptr=(ptr+mov+300)%300;
				break;
			case '_':
				buf[ptr]+=mov;
				break;
			case ':':
				stack[sp++]=pc;
				break;
			case '?':
				if (buf[ptr]>48){
					pc=stack[sp-1];
					continue;
				} else if (sp>0) sp--;
				break;
			case '^':
				mov=-mov;
				break;
			case ',':
				buf[ptr]=getchar();
				break;
			case '.':
				putchar(buf[ptr]);
				break;
		}
	}
	fclose(fp);
	return 0;
}
