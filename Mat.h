#ifndef __MAT_H
#define __MAT_H

// Defining the macro DISABLE_ERROR_HANDLE will disable all error checks to increase performance

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
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
#ifndef DISABLE_ERROR_HANDLE
    if (i >= mat->m) {
        printf("getElem(Mat *mat, int i, int j): i exceeds the row count.\n");
        return 0.0;
    }
    if (j >= mat->n) {
        printf("getElem(Mat *mat, int i, int j): j exceeds the col count.\n");
        return 0.0;
    }
#endif
    return mat->matrix[i * mat->n + j];
}

void setElem(Mat *mat, int i, int j, double val) {
#ifndef DISABLE_ERROR_HANDLE
    if (i >= mat->m) {
        printf("setElem(Mat *mat, int i, int j, double val): i exceeds the row count.\n");
        return;
    }
    if (j >= mat->n) {
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

void switchRow(Mat *mat, int a, int b) {
#ifndef DISABLE_ERROR_HANDLE
    if (a >= mat->m) {
        printf("switchRow(const Mat *mat, int a, int b): a exceeds the row count.");
        return;
    }
    if (b >= mat->m) {
        printf("switchRow(const Mat *mat, int a, int b): b exceeds the row count.");
        return;
    }
#endif

    double temp;
    for (int i = 0; i < mat->n; i++) {
        temp = getElem(mat, a, i);
        setElem(mat, a, i, getElem(mat, b, i));
        setElem(mat, b, i, temp);
    }
}

void moveTop(Mat *mat) {
    for (int i = 0; i < mat->m; i++) {
        bool zeroed = true;
        for (int j = 0; j < mat->n; j++)
            if (getElem(mat, i, j) != 0) zeroed = false;
        if (!zeroed) continue;

        bool reachedEnd = true;
        for (int j = i + 1; j < mat->m; j++) {
            zeroed = true;
            for (int k = 0; k < mat->n; k++)
                if (getElem(mat, j, k) != 0) zeroed = false;
            if (zeroed) continue;

            reachedEnd = false;

            double temp;
            for (int k = 0; k < mat->n; k++) {
                temp = getElem(mat, i, k);
                setElem(mat, i, k, getElem(mat, j, k));
                setElem(mat, j, k, temp);
            }
            break;
        }
        if (reachedEnd) break;
    }
}

void rref(Mat *mat) {
    for (int i = 0; i < mat->m && i < mat->n; i++) {
        // Divides each element by the diagonal
        double diagonal = getElem(mat, i, i);
        if (diagonal != 0)
            for (int j = 0; j < mat->n; j++)
                setElem(mat, i, j, getElem(mat, i, j) / diagonal);

        // Row operations on lower rows to make the lower rows 0 under the leading 1
        for (int j = i + 1; j < mat->m; j++) {
            double ratio = getElem(mat, j, i);
            for (int k = 0; k < mat->n; k++)
                setElem(mat, j, k, getElem(mat, j, k) - ratio * getElem(mat, i, k));
        }
    }

    for (int i = mat->m - 1; i > 0; i--) {
        // Row operations on upper rows to make the upper rows 0 above the leading 1
        for (int j = 0; j < i; j++) {
            double ratio = getElem(mat, j, (i < mat->n) ? i : (mat->n - 1));
            for (int k = 0; k < mat->n; k++)
                setElem(mat, j, k, getElem(mat, j, k) - ratio * getElem(mat, i, k));
        }
    }

    moveTop(mat);
}

void printMat(const Mat *mat) {
#ifndef DISABLE_ERROR_HANDLE
    if (!mat->m || !mat->n) {
        printf("printMat(const Mat *mat): matrix has not been initialized.\n");
        return;
    }
#endif

    printf("printing mat (%dx%d):\n", mat->m, mat->n);
    for (int i = 0; i < mat->m; i++) {
        printf("%s ", (i == 0) ? "┌" : (i == mat->m - 1) ? "└" : "│");
        for (int j = 0; j < mat->n; j++)
            printf("% 5.5f%s", getElem(mat, i, j), (j < mat->n - 1) ? ", " : "");
        printf(" %s\n", (i == 0) ? "┐" : (i == mat->m - 1) ? "┘" : "│");
    }
}

#endif
