#ifndef __MAT_H
#define __MAT_H

// Defining the macro DISABLE_ERROR_HANDLE will disable all error checks to increase performance

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

void copyMat(const Mat *mat, Mat *output) {
#ifndef DISABLE_ERROR_HANDLE
    if (mat->m != output->m) {
        printf("copyMat(const Mat *mat, Mat *output): row number does not match.\n");
        return;
    }
    if (mat->n != output->n) {
        printf("copyMat(const Mat*mat, Mat *output): column number does not match.\n");
        return;
    }
#endif

    for (int i = 0; i < mat->m * mat->n; i++)
        output->matrix[i] = mat->matrix[i];
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

    copyMat(mat, output);

    for (int i = 0; i < output->m; i++) {
        // Divides each element by the diagonal
        double diagonal = getElem(output, i, i);
        for (int j = 0; j < output->n; j++)
            setElem(output, i, j, getElem(output, i, j) / diagonal);

        // Row operations on lower rows to make the lower rows 0 under the leading 1
        for (int j = i + 1; j < output->m; j++) {
            double ratio = getElem(output, j, i);
            for (int k = 0; k < output->n; k++)
                setElem(output, j, k, getElem(output, j, k) - ratio * getElem(output, i, k));
        }
    }

    for (int i = output->m - 1; i > 0; i--) {
        // Row operations on upper rows to make the upper rows 0 above the leading 1
        for (int j = 0; j < i; j++) {
            double ratio = getElem(output, j, i);
            for (int k = 0; k < output->n; k++)
                setElem(output, j, k, getElem(output, j, k) - ratio * getElem(output, i, k));
        }
    }
}

void printMat(const Mat *mat) {
#ifndef DISABLE_ERROR_HANDLE
    if (!mat->m || !mat->n) {
        printf("printMat(const Mat *mat): matrix has not been initialized.\n");
        return;
    }
#endif

    printf("printing mat (%dx%d):\n", mat->m, mat->n);
    for (int i = 0; i < mat->m; i++)
        for (int j = 0; j < mat->n; j++)
            printf("% 5.5f%s", getElem(mat, i, j), (j < mat->n - 1) ? ", " : "\n");
}

#endif
