#include "Mat.h"

int main(int argc, char *argv[]) {
    Mat test;
    initMat(&test, 3, 4);

    test.matrix = (double[]){
        1, 2, 3, 4,
        4, 2, 6, 5,
        3, 6, 7, 1
    };

    rref(&test);
    printMat(&test);
}
