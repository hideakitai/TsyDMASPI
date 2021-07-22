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
    uint8_t pin_cs {10};
    bool b_active_low {true};

    std::deque<spi_transaction_t> transactions;
    bool b_in_transaction {false};
    volatile uint8_t dummy {0};

public:

    virtual ~MasterBase() {}

    bool begin(SPIClass& spic, const uint8_t cs, const SPISettings& setting, const bool active_low)
    {
        spi = &spic;
        pin_cs = cs;
        b_active_low = active_low;
        spi_setting = setting;
        pinMode(pin_cs, OUTPUT);
        spi->begin();
        if (!initDmaTx()) return false;
        if (!initDmaRx()) return false;
        return true;
    }

    void end()
    {
        spi->end();
        destroy();
    }

    // each derived class should have its own dma buffer
    virtual DMAChannel* dmarx() = 0;
    virtual DMAChannel* dmatx() = 0;

    bool transfer(const uint8_t* tx_buf, const size_t size)
    {
        return transfer(tx_buf, nullptr, size);
    }

    bool transfer(const uint8_t* tx_buf, volatile uint8_t* rx_buf, const size_t size)
    {
        if (queue(tx_buf, rx_buf, size))
            yield();
        else
            return false;

        return true;
    }

    bool queue(const uint8_t* tx_buf, const size_t size)
    {
        return queue(tx_buf, nullptr, size);
    }

    bool queue(const uint8_t* tx_buf, volatile uint8_t* rx_buf, const size_t size)
    {
        if ((size == 0) || (size > 0x7FFF))
        {
            Serial.printf("[ERROR] transaction size is invalid : %d\n", size);
            return false;
        }

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            transactions.emplace_back(spi_transaction_t());
            transactions.back().tx_buffer = tx_buf;
            transactions.back().rx_buffer = rx_buf;
            transactions.back().size = size;
            beginTransaction();
        }

        return true;
    }

    void yield()
    {
        while(1)
        {
            bool b = false;
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
            {
                b = transactions.empty();
            }
            if (b) break;
        }
    }

    size_t remained()
    {
        size_t s;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            s = transactions.size();
        }
        return s;
    }

    void next()
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            endTransaction();
            beginTransaction();
        }
    }

    // get SPIClass pointer to configure SPI directly
    SPIClass* spiclass() const
    {
        return spi;
    }

protected:

    void beginTransaction()
    {
        if (transactions.empty() || b_in_transaction) return;

        b_in_transaction = true;
        spi_transaction_t& trans = transactions.front();

        if (trans.rx_buffer)
            dmarx()->destinationBuffer(trans.rx_buffer, trans.size);
        else
        {
            dmarx()->destination(dummy);
            dmarx()->transferCount(trans.size);
        }

        if (trans.tx_buffer)
            dmatx()->sourceBuffer(trans.tx_buffer, trans.size);
        else
        {
            dmatx()->source(dummy);
            dmatx()->transferCount(trans.size);
        }

        initTransaction();

        spi->beginTransaction(spi_setting);
        digitalWriteFast(pin_cs, !b_active_low);

        dmarx()->enable();
        dmatx()->enable();
    }

    void endTransaction()
    {
        digitalWriteFast(pin_cs, b_active_low);
        spi->endTransaction();
        transactions.pop_front();
        b_in_transaction = false;
        clearTransaction();
    }

    virtual bool initDmaTx() = 0;
    virtual bool initDmaRx() = 0;
    virtual void destroy() = 0;
    virtual void initTransaction() = 0;
    virtual void clearTransaction() = 0;
};


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

namespace TsyDMASPI = arduino::teensy::spi::dma;


#endif // ARDUINO_TEENSY_DMA_SPI_MASTER_BASE_H
