#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "DMP.h"

int main(int argc, char *argv[]) {
    int rc = setup();
    printf("rc:%d\n", rc);
    usleep(100000);
    float old[3] = {0};
    for (;;) {
        float* ypr = getYawPitchRoll();
        if (memcmp(old, ypr, sizeof(old)) != 0) {
            printf("ypr:    %7.2f %7.2f %7.2f\n", ypr[0], ypr[1], ypr[2]);
            memcpy(old, ypr, sizeof(old));
        }
    }
    return 0;
}

