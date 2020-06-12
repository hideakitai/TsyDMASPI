#pragma once
#ifndef ARDUINO_TEENSY_DMA_SPI_H
#define ARDUINO_TEENSY_DMA_SPI_H

// reference
// https://github.com/KurtE/DmaSpi/tree/T4

#if (!defined(__arm__) && defined(TEENSYDUINO))
    #error THIS LIBRARY IS ONLY FOR TEENSY SERIES
#endif

#include "TsyDMASPI/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"


// Teensy LC
#if defined (KINETISL)
    #error TEENSY LC CURRENTLY NOT SUPPORTED
    #include "TsyDMASPI/MasterTLC.h"

// Teensy 3.5, 3.6
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
    #error TEENSY 3.5/3.6 CURRENTLY NOT SUPPORTED
    #include "TsyDMASPI/MasterT36.h"

// Teensy 3.2
#elif defined(KINETISK)
    #error TEENSY 3.2 CURRENTLY NOT SUPPORTED
    #include "TsyDMASPI/MasterT32.h"

// Teensy 4.0, 4.1
#elif defined(__IMXRT1062__)
    #include "TsyDMASPI/MasterT40.h"

// others
#else
    #error UNKNOWN MCU
#endif

#endif // ARDUINO_TEENSY_DMA_SPI_H
