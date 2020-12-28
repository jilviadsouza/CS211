#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int missCount, hitCount, readCount = 0, writeCount = 0;
unsigned long int count;
struct Node** cache;
char* policy;

typedef struct Node{
	unsigned long long int tag;
	int valid;
	unsigned long int time; 
}Node;

//creates cache 
struct Node** createCache(int sets, int n){
	cache = (Node**)malloc(sizeof(Node*)*sets);

	for(int i = 0; i < sets; i++){
		cache[i] = (Node*)malloc(sizeof(Node)*n);
	}
	for(int i = 0; i < sets; i++){
		for(int j = 0; j < n; j++){
			cache[i][j].valid = 0;
		}
	}
	return cache;
};

void memoryOperations(unsigned long long int tagIndex, unsigned long long int setIndex, int n){
	int min = 0;

	for(int i = 0; i < n; i++){
		if(cache[setIndex][i].valid == 0){
			missCount++;
			readCount++;
			count++;

			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;
			return;
		} else {
			if(strcmp(policy, "f") == 0 && cache[setIndex][i].tag == tagIndex){
				hitCount++;
				return;
			}

			if(strcmp(policy, "l") == 0 && cache[setIndex][i].tag == tagIndex){
				hitCount++;
				count++;
				cache[setIndex][i].time = count;
				return;
			}
			if(i == (n-1)){
				missCount++;
				readCount++;
				min = 0;

				for(int j = 0; j < n; j++){
					if(cache[setIndex][j].time <= cache[setIndex][min].time){
						min = j;
					}
				}

				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				return;
			}
		}
	}
	return;
}

//frees cache at the end
void freeCache(Node** cache, int sets, int n){
	for(int i = 0; i < sets; i++){
		free(cache[i]);
	}
	free(cache);
	return;
}

int main(int argc, char* argv[]){

	if(argc != 6){
		printf("insufficient arguments");
		return 0;
	}

	//first arg cache size
	int cacheSize = atoi(argv[1]);

	if(ceil(log2(cacheSize)) != floor(log2(cacheSize))){
		printf("Error! cache size not power of 2");
		return 0;
	}

	//fourth arg is block size
	int blockSize = atoi(argv[4]);
	if(ceil(log2(blockSize)) != floor(log2(blockSize))){
		printf("Error, blockSize not power of 2");
		return 0;
	}

	//second arg is associativity
	char assocN[7] = "assoc:";
	int n = 0;
	int sets = 0;

	if(strcmp(argv[2], "direct")!= 0 && strcmp(argv[2], "assoc")!= 0 && argv[2][5]!= ':'){
		printf("Error! incorrect associativity");
		return 0;
	} else {
		if(strcmp(argv[2], "direct") == 0){
			n = 1;
			sets = cacheSize/blockSize;

		} else if(strcmp(argv[2], "assoc") == 0){
			sets = 1;
			n = cacheSize/blockSize;
		
		} else {
			//checks letter by letter until : for assoc:n
			for(int i = 0; i < 6; i++){
				if(assocN[i] != argv[2][i]){
					printf("Error! incorrect associativity");
					return 0;
				}
			}

			sscanf(argv[2], "assoc:%d", &n);

			//is n supposed to be a power of 2? YES
			if(ceil(log2(n)) != floor(log2(n))){
				printf("Error! n is not power of 2");
				return 0;
			} else {

				sets = cacheSize/blockSize/n;
			}
		}
	}

	//third arg is replacement policy
	if(strcmp(argv[3], "fifo") != 0 && strcmp(argv[3], "lru")!= 0){
		printf("Error, incorrect policy");
		return 0;
	}

	if(strcmp(argv[3], "fifo") == 0){
		policy = "f";
	}
	if(strcmp(argv[3], "lru") == 0){
		policy = "l";
	}

	

	//fifth arg is trace file
	FILE* fp = fopen(argv[5], "r");

	if(fp == NULL){
		printf("error with trace file");
		return 0;
	}
	
	//variables to store info from trace file
	char letter;
	unsigned long long int address;

	//bits for tag, index and offset
	int offsetBit = log2(blockSize);
	int setBit = log2(sets);

	cache = createCache(sets, n);

	unsigned long long int setmask = ((1<<setBit)-1);
	unsigned long long int setIndex;
	unsigned long long int tagIndex;

	while(fscanf(fp, "%*x: %c %llx\n", &letter, &address) == 2){
		setIndex = (address>>offsetBit)& setmask;
		tagIndex = address>>(offsetBit + setBit);

		if(letter == 'W'){
			writeCount++;
			memoryOperations(tagIndex, setIndex, n);
			continue;
		}

		if(letter == 'R'){
			memoryOperations(tagIndex, setIndex, n);
			continue;
		} else {
			printf("invalid character\n");
			break;
		}
	}
	freeCache(cache, sets, n);
	fclose(fp);
	printf("Memory reads: %d\n", readCount);
	printf("Memory writes: %d\n", writeCount);
	printf("Cache hits: %d\n", hitCount);
	printf("Cache misses: %d\n", missCount);
	return 0;
}
