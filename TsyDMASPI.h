#pragma once
#ifndef ARDUINO_TEENSY_DMA_SPI_H
#define ARDUINO_TEENSY_DMA_SPI_H

#if (!defined(__arm__) && defined(TEENSYDUINO))
#error THIS LIBRARY IS ONLY FOR TEENSY SERIES
#endif

// Teensy LC
#if defined (KINETISL)
#error TEENSY LC CURRENTLY NOT SUPPORTED
#include "TsyDMASPI/MasterTLC.h"
TsyDMASPI::Master0 TsyDMASPI0;
TsyDMASPI::Master1 TsyDMASPI1;

// Teensy 3.2
#elif defined(KINETISK)
#error TEENSY 3.2 CURRENTLY NOT SUPPORTED
#include "TsyDMASPI/MasterT32.h"
TsyDMASPI::Master0 TsyDMASPI0;

// Teensy 3.5, 3.6
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
#error TEENSY 3.5/3.6 CURRENTLY NOT SUPPORTED
#include "TsyDMASPI/MasterT36.h"
TsyDMASPI::Master0 TsyDMASPI0;
TsyDMASPI::Master1 TsyDMASPI1;
TsyDMASPI::Master2 TsyDMASPI2;

// Teensy 4.0
#elif defined(__IMXRT1062__)
#include "TsyDMASPI/MasterT40.h"
TsyDMASPI::Master0 TsyDMASPI0;
TsyDMASPI::Master1 TsyDMASPI1;
TsyDMASPI::Master2 TsyDMASPI2;

#else
#error UNKNOWN MCU
#endif


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN

void tsydmaspi_rxisr_0()
{
    TsyDMASPI0.dmarx()->clearInterrupt();
    TsyDMASPI0.next();
}

#ifndef KINETISK
void tsydmaspi_rxisr_1()
{
    TsyDMASPI1.dmarx()->clearInterrupt();
    TsyDMASPI1.next();
}
#endif

#if defined(__IMXRT1062__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
void tsydmaspi_rxisr_2()
{
    TsyDMASPI2.dmarx()->clearInterrupt();
    TsyDMASPI2.next();
}
#endif

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

#endif // ARDUINO_TEENSY_DMA_SPI_H
