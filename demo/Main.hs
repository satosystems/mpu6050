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

