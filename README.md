# MPU-6050 for Haskell on Raspberry Pi

[![Hackage](https://img.shields.io/hackage/v/mpu6050.svg)](https://hackage.haskell.org/package/mpu6050)
[![Build Status](https://travis-ci.org/satosystems/mpu6050.svg?branch=master)](https://travis-ci.org/satosystems/mpu6050)

[MPU-6050](https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/) is a Six-Axis device.
This library provided function that detect yaw, pitch and roll.

# How to use

```haskell
module Main where

import Control.Concurrent
import Control.Monad
import Text.Printf

import System.Hardware.MPU6050

main :: IO ()
main = do
  rc <- setup
  rc `unless` error "failed to setup MPU-6050"
  forever $ do
    threadDelay 100
    (y, p, r) <- getYawPitchRoll
    printf "ypr %7.2f %7.2f %7.2f\n" y p r
```

