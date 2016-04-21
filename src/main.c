#include "tester.h"
#include "lagrange.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    enum sorting_method sort;

    if(strcmp(argv[2], "heap") != 0) {
        sort = HEAPSORT;
    } else if(strcmp(argv[2], "quicker") != 0) {
        sort = QUICKERSORT;
    } else {
        printf("Unrecognised sorting method: %s\n", argv[2]);
        return -1;
    }

    test_with_reruns(argv[1], 100, sort);

    return 0;
}