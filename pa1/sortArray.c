#include <stdio.h>
#include <stdlib.h>

void sort (int arr[], int n){
	for(int i = 0; i < n -1; i++){
		for(int j = 0; j < n - i - 1;j++){
			if(arr[j] > arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("insufficient arguments! \n");
        return 0;
    }

    FILE *fp;
    int n;
    fp = fopen(argv[1], "r");

    if(fp == NULL) return 0;

    fscanf(fp, "%d\n", &n);

    int arr[n];// = (int *) malloc(sizeof(int) * n); 
    
    int evenCount, oddCount = 0;
    int i =0;
    int num;
    //find out how many odd and even numbers are there 
    while(fscanf(fp, "%d\t", &num) > 0){
	   arr[i] = num;
    //for(int i = 0; i < n; i++){
        if(num % 2 == 0){
            evenCount++;
        } else if(num % 2 != 0){
            oddCount++;
        }
        i++;
    }
  //  printf("%d\n", evenCount);
   // printf("%d\n", oddCount);

    //create 2 arrays
    int odd[oddCount];
    int even[evenCount];
    int c = 0;


    //populate each array
    for(int j = 0; j < n; j++){
        if(arr[j] % 2 == 0){
            even[c] = arr[j];
            c++;
            continue;
        }
    }
  // printf("%d\n", evenCount); 
   /* for(int a = 0; a < 2; a++ ){
        printf("%d\n", even[a]);
    }*/ 
    
    c = 0;
    
    for(int k = 0; k <= n; k++){
        if(arr[k] % 2 != 0){
            odd[c] = arr[k];
            c++;
            
        }
    }
   // for(int a = 0; a < oddCount; a++ ){
     //   printf("%d\n", odd[a]);
   // } 
    
    if(evenCount != 0){
        sort(even, evenCount);
    }
    //sort each array
    if(oddCount != 0){
        sort(odd, oddCount);
    }
    

    for(int a = 0; a < evenCount; a++ ){
       printf("%d\t", even[a]);
    }
        

    for(int b = oddCount - 1; b >= 0; b--){
        printf("%d\t", odd[b]);
    }
       // printf("\n");

        fclose(fp);
	//free(arr);
        return 0;
}
