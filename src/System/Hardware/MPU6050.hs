{-# language CPP #-}
{-# language QuasiQuotes #-}
{-# language TemplateHaskell #-}

module System.Hardware.MPU6050
    ( setup
    , getYawPitchRoll
    ) where

import Foreign.C.Types
import Foreign.Marshal.Array
import Foreign.Ptr
import qualified Language.C.Inline.Cpp as C

C.include "DMP.h"

setup :: IO Bool
setup = [C.exp| int{ setup() } |] >>= return . (== 0)

getYawPitchRoll :: IO (Float, Float, Float)
getYawPitchRoll = do
  pYpr <- [C.exp| float*{ getYawPitchRoll() } |]
  [CFloat y, CFloat p, CFloat r] <- peekArray 3 pYpr
  return (y, p, r)

