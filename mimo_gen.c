#include <stdio.h>

void generate_bits(char c) {
    for (int i = 7; i >= 0; i--) {
        if ((c >> i) & 1) {
            printf("+");
        }
        printf(">");
    }
    printf(".");
}

int main() {
	//generate_bits('H');
	//generate_bits('e');
	//generate_bits('l');
	//generate_bits('l');
	//generate_bits('o');
	//generate_bits(',');
	//generate_bits(' ');
	//generate_bits('W');
	//generate_bits('o');
	//generate_bits('r');
	//generate_bits('l');
	//generate_bits('d');
	//generate_bits('!');
	generate_bits('\n');

	return 0;
}
