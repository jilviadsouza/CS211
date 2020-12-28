/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
void print(double **matrix, int m, int n);

// main method starts here
int main(int argc, char** argv){

    // your code goes here

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL) return 0;

    int n, m, i; // n is col, m is rows
    fscanf(fp, "%d\n", &n);
    n += 1;
    fscanf(fp, "%d\n", &m);
    double temp;

    double **X = malloc(sizeof(double*) *m);

    for(i = 0; i < m; i++){
        X[i] = malloc(sizeof(double)*n);
    }

    double **Y = malloc(sizeof(double*) * m);       
    for (i = 0; i < m; i++) {
        Y[i] = malloc(sizeof(double));
    }

    for(i = 0; i < m; i++){
        X[i][0] = 1;
    }

    int j;
    for(i = 0; i <m; i++){
        for(j = 0; j < n; j++){
            if( j != n-1){
                fscanf(fp, "%lf,", &temp);
                X[i][j+1] = temp;
            } else {
                fscanf(fp, "%lf\n", &temp);
                Y[i][0] = temp;
            }
        }
    }

    fclose(fp);

    FILE *fp1 = fopen(argv[2], "r");
    if( fp1 == NULL) return 0;

    int m1;
    fscanf(fp1, "%d\n", &m1);

    double **X_test = malloc(sizeof(double*) * m1);
    for(i = 0; i < m1; i++){
        X_test[i] = malloc(sizeof(double) * n);
    }

    for(i = 0; i < m1; i++){
        X_test[i][0] = 1;
    }

    for(i = 0; i <m1; i++){
        for(j = 0; j < n-1; j++){
                fscanf(fp1, "%lf,", &temp);
                X_test[i][j+1] = temp;
        }
    }
   // printf("\nXTEST\n");
    //print(X_test, m1, n);
    fclose(fp1);


    double** matTran = transposeMatrix(X, m, n);
    //printf("STEP 1");
    //print(matTran, n, m);
    //multiply matTran times X
    double** matMultiplied = multiplyMatrix(matTran, X, n, m, m, n);
    //printf("STEP 2");
   // print(matMultiplied, n, n);
    double** matInversed = inverseMatrix(matMultiplied, n);
   // printf("STEP 3");
   // print(matInversed, n, n);
   //printf("120 is good\n");
   double** invXt = multiplyMatrix(matInversed, matTran, n, n, n, m);
   //print(Y, m, 1);
   //printf("STEP 4");
   //print(invXt, n, m);
   double** W = multiplyMatrix(invXt, Y, n, m, m, 1);
   //to find Yfinal
    //printf("STEP 5");
   // print(W, n, 1);
    //printf("STEP 6");
    //print(X_test, m1, m1);
    double** Yfinal = multiplyMatrix(X_test, W, m1, n, n, 1);
   print(Yfinal, m1, 1);

   
   for(i = 0; i < m; i++){
    free(X[i]);
   }

   free(X);

   for(i = 0; i < m; i++){
    free(Y[i]);
   }
   free(Y);

   for(i = 0; i < m1; i++){
    free(X_test[i]);
   }
   free(X_test);

   for(i = 0; i < n; i++){
    free(matTran[i]);
   }
   free(matTran);

   for(i = 0; i < n ; i++){
    free(matMultiplied[i]);
   }
   free(matMultiplied);

   for(i = 0; i < n; i++){
    free(matInversed[i]);
   }
   free(matInversed);
   for(i = 0; i <n ; i++){
    free(invXt[i]);
   }
   free(invXt);
   for(i = 0; i < n ; i++){
    free(W[i]);
   }
   free(W);
   for(i = 0; i < m1 ; i++){
    free(Yfinal[i]);
   }
   free(Yfinal);
    
   return 0;

}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*));
    for(int i=0; i<r1; i++) {
        result[i] = malloc(sizeof(double) * c2);
        for(int j=0; j<c2; j++) result[i][j] = 0;
    }

    for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
         for (int k = 0; k < c1; ++k) {
            result[i][j] += matA[i][k] * matB[k][j];
         }
      }
   }

    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=malloc(col*sizeof(double*)); 
    for(int i = 0; i < col; i++){
        matTran[i]= malloc(sizeof(double) * row);
    }

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            matTran[j][i] = mat[i][j];
        }
    }
    
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{
    //identity matrix
    double** matI=malloc(dimension*sizeof(double*)); 
    for(int i = 0; i < dimension; i++){
        matI[i] = malloc(sizeof(double) * dimension);
    }

    //filling the identity matrix
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(i == j){
                matI[i][j] = 1;
            } else {
                matI[i][j] = 0;
            }
        }
    }

    //row operations 
    int p;
    for(p = 0; p < dimension; p++){
        
        //pivot element
        double f = matA[p][p];
        
        //divide MatA[i] by f
        if(f!=1){
            for(int i=0; i<dimension; i++){
                matA[p][i] = matA[p][i]/f;
                matI[p][i] = matI[p][i]/f;
            }
        }
        
        //divide matI[p] by f
        for(int i = p+1; i < dimension; i++){
            f = matA[i][p];

            //subtract matA[p]*f from m[i]
            //subtract matI[p] * f from n[i]
            for(int j=0;j<dimension;j++){
                matA[i][j] = matA[i][j] - f*matA[p][j];
                matI[i][j] = matI[i][j] - f*matI[p][j];
            }
        }
    }
    for(p = dimension - 1; p >= 0; p--){
        for(int i = p - 1; i >= 0; i--){
            double f = matA[i][p];

            //subtract matA[p] * f from matA[i]
            //subtract matI[p] *f from matI[i]
            for(int j=0;j<dimension;j++){
                matA[i][j] = matA[i][j]-matA[p][j]*f;
                matI[i][j] = matI[i][j]-matI[p][j]*f;
            }
        }
    }   
	return matI;
}

void print(double **matrix, int m, int n){
    int i, j;
    //printf("----------------------\n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%0.0lf  ",matrix[i][j]);
        }
        printf("\n");
    }
   // printf("----------------------\n");
}


