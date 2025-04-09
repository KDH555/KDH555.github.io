#include <stdio.h>

void main()
{
	int n = 0x1234567;
	char* pn = (char*)&n;

	printf("n: %#x\n", n);
	printf("&n: %p\n", &n);
	printf("1st:%p, %#x\n", &(*pn), *pn);
	printf("2nd:%p, %#x\n", &(*(pn+1)), *(pn+1));
	printf("3rd:%p, %#x\n", &(*(pn+2)), *(pn+2));
	printf("long size: %ld\n", sizeof(long));
	printf("short size: %ld\n", sizeof(short));
}
