#include "MasterBase.h"

// TODO: dirty...
extern "C"
{
    void *__exidx_start __attribute__((__visibility__ ("hidden")));
    void *__exidx_end __attribute__((__visibility__ ("hidden")));
}


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN


volatile uint8_t MasterBase::dummy = 0;

bool MasterBase::begin(SPIClass& spic, const SPISettings& setting)
{
    spi = &spic;
    spi_setting = setting;
    spi->begin();
    if (!initDmaTx()) return false;
    if (!initDmaRx()) return false;
    return true;
}

void MasterBase::end()
{
    spi->end();
    destroy();
}

bool MasterBase::transfer(const uint8_t* tx_buf, const size_t size)
{
    return transfer(tx_buf, nullptr, size);
}

bool MasterBase::transfer(const uint8_t* tx_buf, volatile uint8_t* rx_buf, const size_t size)
{
    if (queue(tx_buf, rx_buf, size))
        yield();
    else
        return false;

    return true;
}

bool MasterBase::queue(const uint8_t* tx_buf, const size_t size)
{
    return queue(tx_buf, nullptr, size);
}

bool MasterBase::queue(const uint8_t* tx_buf, volatile uint8_t* rx_buf, const size_t size)
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

void MasterBase::yield()
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

size_t MasterBase::remained()
{
    size_t s;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        s = transactions.size();
    }
    return s;
}

void MasterBase::next()
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        endTransaction();
        beginTransaction();
    }
}

SPIClass* MasterBase::spiclass()
{
    return spi;
}

void MasterBase::beginTransaction()
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

    spi->beginTransaction(SPISettings());

    dmarx()->enable();
    dmatx()->enable();
}

void MasterBase::endTransaction()
{
    spi->endTransaction();
    transactions.pop_front();
    b_in_transaction = false;
    clearTransaction();
}

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

