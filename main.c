#include "Mat.h"

int main(int argc, char *argv[]) {
    Mat test;
    initMat(&test, 2, 2);

    setElem(&test, 0, 1, -1);
    setElem(&test, 1, 0, 1);

    Mat output;
    initMat(&output, 2, 2);

    printMat(&test);
    printMat(&output);
}
