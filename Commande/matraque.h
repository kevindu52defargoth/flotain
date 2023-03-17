void mattr(float matrix[2][2], float transposed[2][2]);
void matmul(float matrix1[2][2], float matrix2[2][2], float result[2][2]);
void vectmul(float matrix[2][2], float vector[2], float result[2]);
void matadd(float matrix1[2][2], float matrix2[2][2], float result[2][2]);
void vectadd(float vector1[2], float vector2[2], float result[2]);
void vectsous(float vector1[2], float vector2[2], float result[2]);
void matinv(float matrix[2][2], float inverse[2][2]);
void fusion (float xhat[2], float P[2][2], float u[2], float z[2]);
void printmat(float matrix[2][2]);