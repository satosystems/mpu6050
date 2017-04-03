#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "DMP.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
static MPU6050 mpu;

// MPU control/status vars
static bool dmpReady = false;  // set true if DMP init was successful
static uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
static uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
static float ypr[3] = {0};           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

int setup() {
    if (dmpReady) return 0;

    // initialize device
    printf("Initializing I2C devices...\n");
    mpu.initialize();

    // verify connection
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");

    // load and configure the DMP
    printf("Initializing DMP...\n");
    uint8_t devStatus = mpu.dmpInitialize();

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        printf("Enabling DMP...\n");
        mpu.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printf("DMP ready!\n");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
        return 0;
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
        return -1;
    }
}

float *getYawPitchRoll() {
    // if programming failed, don't try to do anything
    if (dmpReady) {
        // get current FIFO count
        uint16_t fifoCount = mpu.getFIFOCount();

        if (fifoCount == 1024) {
            // reset so we can continue cleanly
            mpu.resetFIFO();
            printf("FIFO overflow!\n");

        } else if (fifoCount >= 42) {
            // otherwise, check for DMP data ready interrupt (this should happen frequently)
            // read a packet from FIFO
            mpu.getFIFOBytes(fifoBuffer, packetSize);

            Quaternion q;           // [w, x, y, z]         quaternion container
            VectorFloat gravity;    // [x, y, z]            gravity vector

            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            ypr[0] *= 180 / M_PI, ypr[1] *= 180 / M_PI, ypr[2] *= 180 / M_PI;
//            printf("ypr  %7.2f %7.2f %7.2f\n", ypr[0], ypr[1], ypr[2]);
        }
    }
    return ypr;
}

