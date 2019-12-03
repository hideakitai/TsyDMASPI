#if defined(KINETISK)

#include "MasterT32.h"

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN

void tsydmaspi_rxisr_0();


Master0::~Master0()
{
    destroy();
}

bool Master0::begin(const SPISettings& setting)
{
    return this->MasterBase::begin(SPI, setting);
}

DMAChannel* Master0::dmarx()
{
    static DMAChannel *rx = new DMAChannel();
    return rx;
}

DMAChannel* Master0::dmatx()
{
    static DMAChannel *tx = new DMAChannel();
    return tx;
}

bool Master0::initDmaTx()
{
    if (dmatx() == nullptr)
    {
        Serial.println("[ERROR] create dma tx buffer failed");
        return false;
    }
    // TODO:
    // txChannel_()->disable();
    // txChannel_()->destination((volatile uint8_t&)SPI1_PUSHR);
    // txChannel_()->disableOnCompletion();
    // txChannel_()->triggerAtHardwareEvent(DMAMUX_SOURCE_SPI1_TX);
    if (dmatx()->error())
    {
        delete dmatx();
        return false;
    }
    return true;
}

bool Master0::initDmaRx()
{
    if (dmarx() == nullptr)
    {
        Serial.println("[ERROR] create dma tx buffer failed");
        return false;
    }
    // TODO:
    // rxChannel_()->disable();
    // rxChannel_()->source((volatile uint8_t&)SPI1_POPR);
    // rxChannel_()->disableOnCompletion();
    // rxChannel_()->triggerAtHardwareEvent(DMAMUX_SOURCE_SPI1_RX);
    // rxChannel_()->attachInterrupt(rxIsr_);
    // rxChannel_()->interruptAtCompletion();
    if (dmarx()->error())
    {
        delete dmarx();
        return false;
    }
    return true;
}

void Master0::destroy()
{
    if (dmarx() != nullptr) delete dmarx();
    if (dmatx() != nullptr) delete dmatx();
}

void Master0::initTransaction()
{
    // TODO:
    // SPI1_SR = 0xFF0F0000;
    // SPI1_RSER = SPI_RSER_RFDF_RE | SPI_RSER_RFDF_DIRS | SPI_RSER_TFFF_RE | SPI_RSER_TFFF_DIRS;
}

void Master0::clearTransaction()
{
    // TODO:
    // SPI1_RSER = 0;
    // SPI1_SR = 0xFF0F0000;
}



ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

#endif // defined(KINETISK)
