HDRS = I2Cdev.h MPU6050_6Axis_MotionApps20.h MPU6050.h debug.h
CMN_OBJS = I2Cdev.o MPU6050.o DMP.o
CXXFLAGS = -Wall -DDMP_FIFO_RATE=9 -DDEBUG_OUT -g -O2
DMP_OBJS = main.o
TARGET = demo_dmp

.PHONY: all build clean

all: $(TARGET)

$(TARGET): $(CMN_OBJS) $(DMP_OBJS)
	$(CXX) -o $@ $^ -lm

build: $(CMN_OBJS)

$(CMN_OBJS) : $(HDRS)

clean:
	rm -f $(CMN_OBJS) $(DMP_OBJS) $(TARGET)

