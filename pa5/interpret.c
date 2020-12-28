#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[])
{
	char line[100][100];

	int i = 0;
	int totalLines = 0;

	FILE *fp;
	fp = fopen(argv[1], "r");

    if(fp == NULL) return 0;

    while(fgets(line[i], 100, fp)){
    	line[i][strlen(line[i])] = '\0';
    	i++;
    }
    fclose(fp);
    totalLines = i;
    
    int registers[4];
    int start = 2;

    //loop through the array and use sscanf to get the first word, and then strcmp them
    for(int j = 0; j < totalLines; j++){
    	
    	char registersStr[4];
    	char instruction[20];
    	instruction[0] = ' ';
    	sscanf(line[j], "%s", instruction);
    	if(instruction[0] == ' '){ // if blank line, skip it. it is still in the array, but since it has no instruction, we wont be needing it
    		continue;
    	}
    	//printf("%s\n", instruction);

    	//now we got the first words. the instructions 
    	if(strcmp(instruction, "read") == 0){
    		//read command line arg
    		//store in registers index. ax = 0, bx = 1, cx = 2, dx = 3
            sscanf(line[j], "%s %s", instruction, registersStr);
           
            registers[registersStr[0]-97] = atoi(argv[start]);
    		start++;

    		/*for(int i = 0; i < 4; i++){
    			printf("Registers: %d\t", registers[i]);
    		}*/
    	} else if(strcmp(instruction, "print") == 0){
    		char temp[10];
            //print 99
    		sscanf(line[j], "%s %s", instruction, temp);

    		
    		if(isdigit(temp[0])){
    			printf("%d", atoi(temp));
    		} else{
    			printf("%d", registers[temp[0]-97]);
    		}

    	} else if(strcmp(instruction, "mov")==0){
    		char temp[10];
    		char temp1[10];
    		//mov 42 cx
    		//mov ax bx
    		sscanf(line[j], "%s %s %s", instruction, temp, temp1);
    		if(isdigit(temp[0])){
    			registers[temp1[0]-97] = atoi(temp);
    		} else {
    			registers[temp1[0]-97] = registers[temp[0]-97];
    		} 
    	} else if(strcmp(instruction, "add") == 0){
    		char temp[10];
    		char temp1[10];
    		//add 1 ax
    		//add ax bx
    		sscanf(line[j], "%s %s %s", instruction, temp, temp1);
    		if(isdigit(temp[0]) || temp[0] == '-'){
    			registers[temp1[0]-97] += atoi(temp);
    		} else {
    			registers[temp1[0]-97] += registers[temp[0]-97];
    		}
    	} else if(strcmp(instruction, "sub") == 0){
    		char temp[10];
    		char temp1[10];
    		//sub 1 ax
    		//sub ax bx
    		sscanf(line[j], "%s %s %s", instruction, temp, temp1);
    		if(isdigit(temp[0]) || temp[0] == '-'){
    			registers[temp1[0]-97] -= atoi(temp);
    		} else {
    			registers[temp1[0]-97] -= registers[temp[0]-97];
    		}
    	} else if(strcmp(instruction, "mul") == 0){
    		char temp[10];
    		char temp1[10];
    		//mul 1 ax
    		//mul ax bx
    		sscanf(line[j], "%s %s %s", instruction, temp, temp1);
            
            
    		if(isdigit(temp[0]) || temp[0] == '-'){
    			registers[temp1[0]-97] *= atoi(temp);
    		} else {
    			registers[temp1[0]-97] *= registers[temp[0]-97];
    		}
    	} else if(strcmp(instruction, "div") == 0){
    		char temp[10]; //ax
    		char temp1[10]; //bx
    		//div 10 ax
    		//div ax bx
    		sscanf(line[j], "%s %s %s", instruction, temp, temp1);
    		if(isdigit(temp[0]) || temp[0] == '-'){
                registers[temp1[0]-97] = atoi(temp) / registers[temp1[0]-97];
    		} else {
                registers[temp1[0]-97] = registers[temp[0]-97]/registers[temp1[0]-97];
                
    		}
    	} else if(strcmp(instruction, "je") == 0){
            //je 10 dx 4 --> jump to line 10 if dx == 4
            //je 10 4 dx
            char lineNumber[10];
            char temp[10]; //x
            char temp1[10]; //y
            int x = -1, y = -2;

            sscanf(line[j], "%s %s %s %s", instruction, lineNumber, temp, temp1);

            if(isdigit(temp[0])){
                x = atoi(temp);

            } else {
                x = registers[temp[0]-97];

            }
            if(isdigit(temp1[0])){
                y = atoi(temp1);

            } else {
                y = registers[temp1[0]-97];

            }

            if(x == y){

                j = atoi(lineNumber)-1;

            }

    	} else if(strcmp(instruction, "jne") == 0){
            char lineNumber[10];
            char temp[10]; //x
            char temp1[10]; //y
            int x = -1, y = -2;

            sscanf(line[j], "%s %s %s %s", instruction, lineNumber, temp, temp1);

            if(isdigit(temp[0])){
                x = atoi(temp);
 
            } else {
                x = registers[temp[0]-97];
            }
            if(isdigit(temp1[0])){
                y = atoi(temp1);
            } else {
                y = registers[temp1[0]-97];
            }

            if(x != y){
                j = atoi(lineNumber)-1;
            }

        } else if(strcmp(instruction, "jg") == 0){
            char lineNumber[10];
            char temp[10]; //x
            char temp1[10]; //y
            int x = -1, y = -2;

            sscanf(line[j], "%s %s %s %s", instruction, lineNumber, temp, temp1);

            if(isdigit(temp[0])){
                x = atoi(temp);

            } else {
                x = registers[temp[0]-97];

            }
            if(isdigit(temp1[0])){
                y = atoi(temp1);

            } else {
                y = registers[temp1[0]-97];

            }

            if(x > y){

                j = atoi(lineNumber)-1;
            }
        } else if(strcmp(instruction, "jge") == 0){
            char lineNumber[10];
            char temp[10]; //x
            char temp1[10]; //y
            int x = -1, y = -2;

            sscanf(line[j], "%s %s %s %s", instruction, lineNumber, temp, temp1);

            if(isdigit(temp[0])){
                x = atoi(temp);

            } else {
                x = registers[temp[0]-97];
            }
            if(isdigit(temp1[0])){
                y = atoi(temp1);
            } else {
                y = registers[temp1[0]-97];
            }

            if(x >= y){

                j = atoi(lineNumber)-1;

            }
        } else if(strcmp(instruction, "jl") == 0){
            char lineNumber[10];
            char temp[10]; //x
            char temp1[10]; //y
            int x = -1, y = -2;

            sscanf(line[j], "%s %s %s %s", instruction, lineNumber, temp, temp1);

            if(isdigit(temp[0])){
                x = atoi(temp);

            } else {
                x = registers[temp[0]-97];

            }
            if(isdigit(temp1[0])){
                y = atoi(temp1);

            } else {
                y = registers[temp1[0]-97];

            }

            if(x < y){

                j = atoi(lineNumber)-1;

            }
        } else if(strcmp(instruction, "jle") == 0){
            char lineNumber[10];
            char temp[10]; //x
            char temp1[10]; //y
            int x = -1, y = -2;

            sscanf(line[j], "%s %s %s %s", instruction, lineNumber, temp, temp1);

            if(isdigit(temp[0])){
                x = atoi(temp);
            } else {
                x = registers[temp[0]-97];
            }
            if(isdigit(temp1[0])){
                y = atoi(temp1);
            } else {
                y = registers[temp1[0]-97];

            }

            if(x <= y){

                j = atoi(lineNumber)-1;

            }
        } else if(strcmp(instruction, "jmp") == 0){
            //jmp 5 
            char lineNumber[10];
            sscanf(line[j], "%s %s", instruction, lineNumber);


            if(isdigit(lineNumber[0])){
                j = atoi(lineNumber)-1;
            }
        }
       /* printf("line: %d\n", j);
    	for(int i = 0; i < 4; i++){

    	printf("\nRegisters: %d\t", registers[i]);
    	}*/
    }
    

    return 0;

}


