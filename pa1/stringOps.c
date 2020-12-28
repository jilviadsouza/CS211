#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
if(argc < 1){
	printf("insufficient arguments");
	return 0;
}
char *input;

for(int i = 1; i < argc; i++){
	input = argv[i];

	int j = 0;
	while(input[j] != '\0'){
		if(input[j] == 'a' || input[j] == 'e'
		|| input[j] == 'i'|| input[j] == 'o'
		|| input[j] == 'u'|| input[j] == 'A'
		|| input[j] == 'E'|| input[j] == 'I'
		|| input[j] == 'O'|| input[j] == 'U'){

			printf("%c", input[j]);
	}
		j++;
	}
}
printf("\n");
return 0;
}
