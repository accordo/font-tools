#include <stdio.h>
#include <string.h>

char zero[8];
char one[8];


int BIT(int n, int b)
{
	return n & (1<<b);
}

void putbit(int bit)
{
	if(bit) printf("%s", one);
	else printf("%s", zero);
	return;
}

void putbits(int ch, int n, int msb)
{
	int j;

	n %= sizeof(ch) * 8;

	for(j=0; j<n; j++) {
		if(msb) putbit(BIT(ch, j));
		else   putbit(BIT(ch, n-j-1));
		
	}
}

int main(int argc, char *argv[])
{
	int i;

	strcpy(zero, "_");
	strcpy(one, "O");

	printf("#ifndef __DEF01_H__\n" 
		"#define __DEF01_H__\n");
	putchar('\n');

	for(i=0; i<256; i++) {
		printf("#define ");
		putbits(i, 8, 0);
		printf("   0x%02X", i);
		putchar('\n');
	}

	putchar('\n');
	printf("#endif\n");
	putchar('\n');
}

