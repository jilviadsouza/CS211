#include <stdio.h>
#include <stdlib.h>


int get(unsigned short x, int n){

	

	return (x >> n) & 1;
}

//compares the values at first and last index, moving towards the middle
//if no value is the same, not a palindrome. 
void isPalindrome(unsigned short n){

	for(int i = 0; i < 8; i++){
		if(get(n, i) != get(n, 15 - i)){
			printf("Not-Palindrome\n");
			return;
		}
	}

	printf("Is-Palindrome\n");
}
int main(int argc, char* argv[])
{

	char *a = argv[1];
	unsigned short x = atoi(a);

	isPalindrome(x);
}
