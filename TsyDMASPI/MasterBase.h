#ifndef ARDUINO_TEENSY_DMA_SPI_MASTER_BASE_H
#define ARDUINO_TEENSY_DMA_SPI_MASTER_BASE_H

#include <Arduino.h>
#include <util/atomic.h>
#include <SPI.h>
#include <DMAChannel.h>
#include <deque>
#include "Constants.h"


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN

class MasterBase
{
protected:

    struct spi_transaction_t
    {
        uint16_t size;
        const uint8_t* tx_buffer;
        volatile uint8_t* rx_buffer;
    };

    SPIClass* spi;
    SPISettings spi_setting;

    std::deque<spi_transaction_t> transactions;
    bool b_in_transaction {false};
    volatile static uint8_t dummy;

public:

    virtual ~MasterBase() {}

    bool begin(SPIClass& spic, const SPISettings& setting);
    void end();

    // each derived class should have its own dma buffer
    virtual DMAChannel* dmarx() = 0;
    virtual DMAChannel* dmatx() = 0;

    bool transfer(const uint8_t* tx_buf, const size_t size);
    bool transfer(const uint8_t* tx_buf, volatile uint8_t* rx_buf, const size_t size);

    bool queue(const uint8_t* tx_buf, const size_t size);
    bool queue(const uint8_t* tx_buf, volatile uint8_t* rx_buf, const size_t size);
    void yield();

    size_t remained();

    void next();

    // get SPIClass pointer to configure SPI directly
    SPIClass* spiclass();

protected:

    void beginTransaction();
    void endTransaction();

    virtual bool initDmaTx() = 0;
    virtual bool initDmaRx() = 0;
    virtual void destroy() = 0;
    virtual void initTransaction() = 0;
    virtual void clearTransaction() = 0;
};


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

namespace TsyDMASPI = arduino::teensy::spi::dma;


#endif // ARDUINO_TEENSY_DMA_SPI_MASTER_BASE_H
