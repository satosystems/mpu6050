.PHONY: build demo

build:
	stack build

demo: build
	stack exec mpu6050-demo

