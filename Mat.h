#ifndef __MAT_H
#define __MAT_H

#define DISABLE_ERROR_HANDLE
#undef DISABLE_ERROR_HANDLE

#include <stdio.h>
#include <stdlib.h>

typedef struct Mats {
    int m, n;
    double *matrix;
} Mat;

void initMat(Mat *mat, int m, int n) {
#ifndef DISABLE_ERROR_HANDLE
    if (!m || !n) {
        printf("initMat(Mat *mat, int m, int n): cannot create a matrix with 0 dimensions.\n");
        return;
    }
#endif

    mat->m = m;
    mat->n = n;

    mat->matrix = (double *)malloc(m * n * sizeof(double));
}

void cleanMat(Mat *mat) {
    free(mat->matrix);
}

double getElem(const Mat *mat, int i, int j) {
    return mat->matrix[i * mat->n + j];
}

void setElem(Mat *mat, int i, int j, double val) {
#ifndef DISABLE_ERROR_HANDLE
    if (i > mat->m) {
        printf("setElem(Mat *mat, int i, int j, double val): i exceeds the row count.\n");
        return;
    }
    if (j > mat->n) {
        printf("setElem(Mat *mat, int i, int j, double val): j exceeds the col count.\n");
        return;
    }
#endif

    mat->matrix[i * mat->n + j] = val;
}

void rref(const Mat *mat, Mat *output) {
#ifndef DISABLE_ERROR_HANDLE
    if (mat->m != output->m) {
        printf("rref(const Mat*mat, Mat *output): row number does not match.\n");
        return;
    }
    if (mat->n != output->n) {
        printf("rref(const Mat*mat, Mat *output): column number does not match.\n");
        return;
    }
#endif
}

void printMat(const Mat *mat) {
#ifndef DISABLE_ERROR_HANDLE
    if (!mat->m || !mat->n) {
        printf("printMat(const Mat *mat): matrix has not been initialized.\n");
        return;
    }
#endif

    for (int i = 0; i < mat->m; i++)
        for (int j = 0; j < mat->n; j++)
            printf("% 5.5f%s", getElem(mat, i, j), (j < mat->n - 1) ? ", " : "\n");
}

#endif
