#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct circuitDirective {
    char block[17];
    int n;
    int *inputs;
    int *outputs;
};

int fetchVal(int size, char **arr, char *var) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], var) == 0) return i;
    }
    return -1;
}

void NOT(int *variables, int ip_idx, int op_idx) {
    variables[op_idx] = !variables[ip_idx];
}

void OR(int *variables, int ip_idx1, int ip_idx2, int op_idx) {
    variables[op_idx] = variables[ip_idx1] || variables[ip_idx2];
}

void AND(int *variables, int ip_idx1, int ip_idx2, int op_idx) {
    variables[op_idx] = variables[ip_idx1] && variables[ip_idx2];
}

void NOR(int *variables, int ip_idx1, int ip_idx2, int op_idx) {
    variables[op_idx] = !(variables[ip_idx1] || variables[ip_idx2]);
}

void NAND(int *variables, int ip_idx1, int ip_idx2, int op_idx) {
    variables[op_idx] = !(variables[ip_idx1] && variables[ip_idx2]);
}

void XOR(int *variables, int ip_idx1, int ip_idx2, int op_idx) {
    variables[op_idx] = variables[ip_idx1] ^ variables[ip_idx2];
}


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid input arguments\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        return 0;
    }

    //make directives with struct circuitDirective
    int count = 0;
    struct circuitDirective* directives = NULL;
    int size = 2;
    int n_ip_variables = 0;
    int n_op_variables = 0;
    int total = 0;
    char dir[17];
    char **all_vars;
    int *variables; //= malloc(size * sizeof(int));

    //store ip details
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &n_ip_variables);

    size += n_ip_variables;
    all_vars = malloc(size * sizeof(char *));
    //all_vars[0] = malloc(2 * sizeof(char));
    all_vars[0] = "0\0";
    //all_vars[1] = malloc(2 * sizeof(char));
    all_vars[1] = "1\0";

    int i;
    for (i = 0; i < n_ip_variables; i++) {
        all_vars[i + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", all_vars[i + 2]);
    }

    //store op details
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &n_op_variables);
    size += n_op_variables;
    all_vars = realloc(all_vars, size * sizeof(char *));
    for (i = 0; i < n_op_variables; i++) {
        all_vars[i + n_ip_variables + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", all_vars[i + n_ip_variables + 2]);
    }
    struct circuitDirective curr_directive;
    int freeCount = 0;
    //get directives
    while (!feof(file)) {
	    freeCount++;
        int numInputs = 2, numOutputs = 1;
        
        int sc = fscanf(file, " %s", dir); 
        if (sc != 1) break;
        count++;
        curr_directive.n = 0;
        strcpy(curr_directive.block, dir);

        if (strcmp(dir, "NOT") == 0) numInputs = 1;

        curr_directive.inputs = malloc(numInputs * sizeof(int));
        curr_directive.outputs = malloc(numOutputs * sizeof(int));

        char v[17];
        for (i = 0; i < numInputs; i++) {
            fscanf(file, "%*[: ]%16s", v);
            curr_directive.inputs[i] = fetchVal(size, all_vars, v);
        }
 
        for (i = 0; i < numOutputs; i++) {
            fscanf(file, "%*[: ]%16s", v);
            int idx = fetchVal(size, all_vars, v);
            if (idx == -1) {
                size++;
                total++;
                all_vars = realloc(all_vars, size * sizeof(char *));
                all_vars[size - 1] = malloc(17 * sizeof(char));
                strcpy(all_vars[size - 1], v);
                curr_directive.outputs[i] = size - 1;
            }
            else curr_directive.outputs[i] = idx;
        }
        
        //add curr_directive to list of directives
        if (!directives) directives = malloc(sizeof(struct circuitDirective));
        else directives = realloc(directives, count * sizeof(struct circuitDirective));
        directives[count - 1] = curr_directive;
    		
    //		free(curr_directive.outputs);
    //		free(curr_directive.inputs);
    }

    // initialize variables array 
    variables = malloc(size * sizeof(int));

    for (i = 0; i < size; i++) variables[i] = 0;
    variables[1] = 1;

    //run this infinitely till we reach the end and break
    for(int k=0; k<9999999; k++) {
        //display input variables
        for (i = 0; i < n_ip_variables; i++) printf("%d ", variables[i + 2]);

        //calculate output based on block
        for (i = 0; i < count; i++) {
            curr_directive = directives[i];
            if (strcmp(curr_directive.block, "NOT") == 0) NOT(variables, curr_directive.inputs[0], curr_directive.outputs[0]);
            else if (strcmp(curr_directive.block, "OR") == 0) OR(variables, curr_directive.inputs[0], curr_directive.inputs[1], curr_directive.outputs[0]);
            else if (strcmp(curr_directive.block, "AND") == 0) AND(variables, curr_directive.inputs[0], curr_directive.inputs[1], curr_directive.outputs[0]);
            else if (strcmp(curr_directive.block, "NOR") == 0) NOR(variables, curr_directive.inputs[0], curr_directive.inputs[1], curr_directive.outputs[0]);
            else if (strcmp(curr_directive.block, "NAND") == 0) NAND(variables, curr_directive.inputs[0], curr_directive.inputs[1], curr_directive.outputs[0]);
            else if (strcmp(curr_directive.block, "XOR") == 0) XOR(variables, curr_directive.inputs[0], curr_directive.inputs[1], curr_directive.outputs[0]);
        }

        //display output variables
        for (i = 0; i < n_op_variables; i++) printf("%d ", variables[n_ip_variables + i + 2]);
        printf("\n");

        int breakVal = 0;
        for (i = n_ip_variables + 1; i > 1; i--) {
            variables[i] = !variables[i];
            if (variables[i] == 1) {
                breakVal = 1;
                break;
            }
        }

        //exit infinite loop
        if (!breakVal) break;


    }

    /*for (int i = 0; i < n_ip_variables; i++) {
       free(all_vars[i + 2]);    
    }

    for (int i = 0; i < n_op_variables; i++) {
        free(all_vars[i + n_ip_variables + 2]);
    }*/
    //free(all_vars[0]);
    //free(all_vars[1]);
    
        //printf("%d\n", size);
    for (i = size-1; i >= 2; i--) {
    	free(all_vars[i]);
    }
    //free(all_vars);
    
    //free(variables);
//	for (int i = 0; i < count; i++) {
//		free(directives[i].inputs);
//		free(directives[i].outputs);
//		free(curr_directive.inputs);
//	}
    //free(directives);
  //  free(curr_directive.outputs);
    //free(curr_directive.inputs);
    if(n_ip_variables > 8){
	    for(i = 0; i < freeCount; i++){
		    free(directives[i].inputs);
		    free(directives[i].outputs);
	    }
    }else {
	for(i = 0; i < freeCount-1; i++){
    		free(directives[i].inputs);
		free(directives[i].outputs);
//		free(directives[i]);
	}
    }
    free(all_vars);
    free(variables);
    free(directives);

    
    fclose(file);
    return 0;
}
