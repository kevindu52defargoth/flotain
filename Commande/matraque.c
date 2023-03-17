#include <stdio.h>
#include "matraque.h"

/*
int main(){
	float xhat[2] = {0.2, 0.3};
	float u[2] = {0.3, 0.4};
	float P[2][2] = {{0, 0}, {0, 0}};
	float z[2] = {0.21, 0.31};
	
	fusion(xhat, P, u, z);	
	printf("[%f, %f]\n", xhat[0], xhat[1]);
}
*/

void mattr(float matrix[2][2], float transposed[2][2]){
    transposed[0][0] = matrix[0][0];
    transposed[0][1] = matrix[1][0];
    transposed[1][0] = matrix[0][1];
    transposed[1][1] = matrix[1][1];
}

void matmul(float matrix1[2][2], float matrix2[2][2], float result[2][2]){
    result[0][0] = matrix1[0][0] * matrix2[0][0] + matrix1[0][1] * matrix2[1][0];
    result[0][1] = matrix1[0][0] * matrix2[0][1] + matrix1[0][1] * matrix2[1][1];
    result[1][0] = matrix1[1][0] * matrix2[0][0] + matrix1[1][1] * matrix2[1][0];
    result[1][1] = matrix1[1][0] * matrix2[0][1] + matrix1[1][1] * matrix2[1][1];
}

void vectmul(float matrix[2][2], float vector[2], float result[2]){
    result[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1];
    result[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1];
}

void matadd(float matrix1[2][2], float matrix2[2][2], float result[2][2]){
    result[0][0] = matrix1[0][0] + matrix2[0][0];
    result[0][1] = matrix1[0][1] + matrix2[0][1];
    result[1][0] = matrix1[1][0] + matrix2[1][0];
    result[1][1] = matrix1[1][1] + matrix2[1][1];
}

void vectadd(float vector1[2], float vector2[2], float result[2]){
    result[0] = vector1[0] + vector2[0];
    result[1] = vector1[1] + vector2[1];
} 

void vectsous(float vector1[2], float vector2[2], float result[2]){
    result[0] = vector1[0] - vector2[0];
    result[1] = vector1[1] - vector2[1];
} 

void matinv(float matrix[2][2], float inverse[2][2]) {
    // Calculate the determinant of the matrix
    float det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	if (det != 0) {
		// Calculate the inverse of the matrix
		inverse[0][0] = matrix[1][1] / det;
		inverse[0][1] = -matrix[0][1] / det;
		inverse[1][0] = -matrix[1][0] / det;
		inverse[1][1] = matrix[0][0] / det;
	} else {
		printf("Not inversible\n");
	}
}

void printmat(float matrix[2][2]){
	printf("[%f, %f; %f, %f]\n", matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
}


void fusion (float xhat[2], float P[2][2], float u[2], float z[2]) {
	float A[2][2] = {{1, 0}, {0, 1}};
	float At[2][2] = {{1, 0}, {0, 1}};
	float H[2][2] = {{1, 0}, {0, 1}};
	float Ht[2][2] = {{1, 0}, {0, 1}};
	float deltaT = 0.2;
	float B[2][2] = {{deltaT, 0}, {0, deltaT}};
	float R[2][2] = {{0.01, 0}, {0, 0.01}};
	float I[2][2] = {{1, 0}, {0, 1}};
	
	float xtemp[2];
	float tempa[2];
	float tempb[2];
	float temp2a[2][2];
	float temp2b[2][2];
	float Ptemp[2][2]; 	
	float Ktemp[2][2];

	vectmul(A, xhat, tempa); 
	vectmul(B, u, tempb); 
	vectadd(tempa, tempb, xtemp); //xtemp pris
	
	matmul(A,P, temp2a);
	matmul(temp2a, At, temp2b);
	matadd(temp2b, R, Ptemp); //Ptemp pris
	
	matmul(H, Ptemp, temp2a);
	matmul(temp2a, Ht, temp2b);
	matadd(temp2b, R, temp2a);
	matinv(temp2a, temp2b);
	matmul(Ht, temp2b, temp2a);
	matmul(Ptemp, temp2a, Ktemp); //Ktemp pris
	
	vectmul(H, xtemp, tempa);
	vectsous(z, tempa, tempb);
	vectmul(Ktemp, tempb, tempa);
	vectadd(xtemp, tempa, xhat); //xhat changé
	
	matmul(Ktemp, H, temp2a);
	matadd(I, temp2a, temp2b);
	matmul(temp2b, Ptemp, P); //P changé
}
