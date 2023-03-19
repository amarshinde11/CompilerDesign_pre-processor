/* Include the predefined header file */
#include<stdio.h>  #include<string.h>
#include<stdlib.h>
////////////////
/* include the user defined header file */
#include"header.h"

/* macro definition */
#define PRINTF(x) printf("num = %d \n", x);

int main()
{
    /* local variables */
    printf("Hello World\n");
    printf("This is project for pre-processor stage\n");

    int max;    /* declare a maximum */
    int num1, num2;
    int result = 0;

    printf("Enter the num1: "); /* enter the first number */
	scanf("%d", &num1); // scan the number
    /* hello world */hello//printf("Enter the num2: ");
    	scanf("%d", &num2);
    result = num1 + num2;
    printf("result = %d\n", result);

    //max = num1 > num1 ? (max = num1) /* num1 is maximum */: (max = num2) /* num2 is maximum*/;
    printf("max: %d\n", max);
    //printf("max: %d\n", max);
    return 0;
}
// This is end of main function.
