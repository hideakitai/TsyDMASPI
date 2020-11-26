# TsyDMASPI
This is SPI library using DMA buffer for Teensy, inspired by @crteensy 's [DmaSpi](https://github.com/crteensy/DmaSpi) and its @KurtE 's [fork for Teensy 4.0](https://github.com/KurtE/DmaSpi/tree/T4).

## Feature

- support DMA buffer (more than 64 byte transfer is available)
- Master has two ways to send/receive transactions
  - `transfer()` to send/receive transaction one by one
  - `queue()` and `yield()` to send/receive multiple transactions at once

## WARNING

This library currently supports only Teensy 4.0.


## Usage

```C++
#include <TsyDMASPI.h>

#define PIN_CS 10
#define DMASIZE 8192
uint8_t src[DMASIZE];
volatile uint8_t dest[DMASIZE];
volatile uint8_t dest1[DMASIZE];

void setup() {
    TsyDMASPI0.begin(PIN_CS, SPISettings(4000000, MSBFIRST, SPI_MODE3));

    // one by one transaction
    TsyDMASPI0.transfer(src, dest, DMASIZE);
    
    // multiple transaction at once
    TsyDMASPI0.queue(src, dest, DMASIZE);
    TsyDMASPI0.queue(src, dest1, DMASIZE);
    TsyDMASPI0.yield();
}
```


### One by One transfer

``` C++
// SPI with DMA on SPI0
TsyDMASPI0.begin(PIN_CS, SPISettings(4000000, MSBFIRST, SPI_MODE3));
TsyDMASPI0.transfer(tx_buf, rx_buf, DMASIZE);
```

### Multiple queued transfer

``` C++
// SPI with DMA on SPI0
TsyDMASPI0.begin(PIN_CS, SPISettings(4000000, MSBFIRST, SPI_MODE3));
TsyDMASPI0.queue(tx_buf0, rx_buf0, DMASIZE);
TsyDMASPI0.queue(tx_buf1, rx_buf1, DMASIZE);
TsyDMASPI0.yield(); // wait until all transactions will be done
```

## TODO (PR Welcome!!)

- Teensy LC, 3.2, 3.5, 3.6 implementation
- Slave mode with DMA for example like [this thread](https://forum.pjrc.com/threads/58023-Teensy-4-as-SPI-Slave)


## Embedded Libraries

- [TeensyDirtySTLErrorSolution v0.1.0](https://github.com/hideakitai/TeensyDirtySTLErrorSolution)


## License

MIT
