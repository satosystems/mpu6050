#include <stdio.h>
#include <unistd.h>
#include "DMP.h"

int main(int argc, char *argv[]) {
    int rc = setup();
    printf("rc:%d\n", rc);
    usleep(100000);
    for (;;) {
        float* ypr = getYawPitchRoll();
        printf("ypr:    %7.2f %7.2f %7.2f\n", ypr[0], ypr[1], ypr[2]);
    }
    return 0;
}

