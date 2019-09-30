#include "Mat.h"

int main(int argc, char *argv[]) {
    Mat test;
    initMat(&test, 2, 3);

    test.matrix = (double[]){
        2, 0, 5,
        0, 1, 6
    };

    Mat output;
    initMat(&output, 2, 3);

    printMat(&test);
    rref(&test, &output);
    printMat(&output);
}
