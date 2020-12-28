#include <stdio.h>
#include <stdlib.h>

//counts the number of 1s
//finds the pairs of 11
void countBits(unsigned short n){

	int count = 0;
	int pairs = 0;
	int num = n;
	

	while(num != 0){
		count += num & 1;
		num = num >> 1;
	}

	while(n != 0){
		int flag = n & 3; 
		if(flag == 3){
			n = n >> 2;
			pairs++;
		} else {
			n = n >> 1;
		}
	}

	

	if(count % 2 == 1){
		printf("Odd-Parity\t%d\n", pairs);
	}
	else {
		printf("Even-Parity\t%d\n", pairs);
	}
	

}

int main(int argc, char* argv[]){

	
	char *a = argv[1];
	unsigned short x = atoi(a);

	countBits(x);


}
