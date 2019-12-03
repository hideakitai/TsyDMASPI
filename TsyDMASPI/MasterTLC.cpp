#if defined (KINETISL)

#include "MasterTLC.h"

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN

void tsydmaspi_rxisr_0();
void tsydmaspi_rxisr_1();


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



Master1::~Master1()
{
    destroy();
}

bool Master1::begin(const SPISettings& setting)
{
    return this->MasterBase::begin(SPI1, setting);
}

DMAChannel* Master1::dmarx()
{
    static DMAChannel *rx = new DMAChannel();
    return rx;
}

DMAChannel* Master1::dmatx()
{
    static DMAChannel *tx = new DMAChannel();
    return tx;
}

bool Master1::initDmaTx()
{
    if (dmatx() == nullptr)
    {
        Serial.println("[ERROR] create dma tx buffer failed");
        return false;
    }
    // TODO:
    // dmatx()->disable();
    // dmatx()->destination((volatile uint8_t &)IMXRT_LPSPI3_S.TDR);
    // dmatx()->disableOnCompletion();
    // dmatx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI3_TX);
    if (dmatx()->error())
    {
        delete dmatx();
        return false;
    }
    return true;
}

bool Master1::initDmaRx()
{
    if (dmarx() == nullptr)
    {
        Serial.println("[ERROR] create dma tx buffer failed");
        return false;
    }
    // TODO:
    // dmarx()->disable();
    // dmarx()->source((volatile uint8_t &)IMXRT_LPSPI3_S.RDR);
    // dmarx()->disableOnCompletion();
    // dmarx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI3_RX);
    // dmarx()->attachInterrupt(tsydmaspi_rxisr_1);
    // dmarx()->interruptAtCompletion();
    if (dmarx()->error())
    {
        delete dmarx();
        return false;
    }
    return true;
}

void Master1::destroy()
{
    if (dmarx() != nullptr) delete dmarx();
    if (dmatx() != nullptr) delete dmatx();
}

void Master1::initTransaction()
{
    // TODO:
    // IMXRT_LPSPI3_S.TCR = (IMXRT_LPSPI3_S.TCR & ~(LPSPI_TCR_FRAMESZ(31))) | LPSPI_TCR_FRAMESZ(7);
    // IMXRT_LPSPI3_S.FCR = 0;
    // // Lets try to output the first byte to make sure that we are in 8 bit mode...
    // IMXRT_LPSPI3_S.DER = LPSPI_DER_TDDE | LPSPI_DER_RDDE; //enable DMA on both TX and RX
    // IMXRT_LPSPI3_S.SR = 0x3f00;                           // clear out all of the other status...
}

void Master1::clearTransaction()
{
    // TODO:
    // IMXRT_LPSPI3_S.FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save; // restore the FSR status...
    // IMXRT_LPSPI3_S.DER = 0;                     // DMA no longer doing TX (or RX)
    // IMXRT_LPSPI3_S.CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF; // actually clear both...
    // IMXRT_LPSPI3_S.SR = 0x3f00;                                     // clear out all of the other status...
}


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

#endif // defined (KINETISL)
