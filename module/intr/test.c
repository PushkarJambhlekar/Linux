#include <stdio.h>
#include <string.h>
int main()
{
//	char abc[300];
//	int i,j;
//	scanf("%d%d",&i,&j);
//	printf("i = %d\tj = %d\n",i,j);
//	printf("out is : %d\n",i/j);
//	strcpy(abc, "This is test string\n");
	//asm ( "INT $0x3;" );
	asm volatile ( "INT $0x80" );
//	printf("%s",abc);
	return 0;
}
