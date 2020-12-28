#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned short  x;

//sets the nth bit of x to v
int set(unsigned short x, int n, int v){

	//clear the nth bit, and set it to v

	return  (x & (~(1 << n))) | (v << n);
	
}

//returns the complement of the nth bit of x
int comp(unsigned short x, int n){

	return  (x ^ (1 << (n)));
}

//gets the value of the nth bit of x
int get(unsigned short x, int n){

	

	return (x >> n) & 1;
}

int main(int argc, char* argv[])
{

	FILE *fp = fopen(argv[1], "r");

	if(fp == NULL) return 0;

	char str[5];
	//unsigned short x;
	int n, v;

	fscanf(fp, "%hu\n", &x);
	//printf("x: %d\n", x);

	while(fscanf(fp, "%s\t%d\t%d\n", str, &n, &v) > 0){

		
		if(strcmp(str, "get") == 0){
			int a = get(x, n);
			//printf("x : %d\n", x );
			printf("%d\n", a);
		} else if (strcmp(str, "comp") == 0){
			x = comp(x, n);
			//printf("x : %d\n", x );
			printf("%hu\n",x);
		} else if (strcmp(str, "set") == 0){
			x = set(x, n, v);
			//printf("x : %d\n", x );
			printf("%hu\n", x);
		}
	}
	fclose(fp);
	return 0;
}
