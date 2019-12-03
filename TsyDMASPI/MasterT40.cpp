#if defined(__IMXRT1062__)

#include "MasterT40.h"

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN

void tsydmaspi_rxisr_0();
void tsydmaspi_rxisr_1();
void tsydmaspi_rxisr_2();


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
    dmatx()->disable();
    dmatx()->destination((volatile uint8_t &)IMXRT_LPSPI4_S.TDR);
    dmatx()->disableOnCompletion();
    dmatx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI4_TX);
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
    dmarx()->disable();
    dmarx()->source((volatile uint8_t &)IMXRT_LPSPI4_S.RDR);
    dmarx()->disableOnCompletion();
    dmarx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI4_RX);
    dmarx()->attachInterrupt(tsydmaspi_rxisr_0);
    dmarx()->interruptAtCompletion();
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
    IMXRT_LPSPI4_S.TCR = (IMXRT_LPSPI4_S.TCR & ~(LPSPI_TCR_FRAMESZ(31))) | LPSPI_TCR_FRAMESZ(7);
    IMXRT_LPSPI4_S.FCR = 0;

    // Lets try to output the first byte to make sure that we are in 8 bit mode...
    IMXRT_LPSPI4_S.DER = LPSPI_DER_TDDE | LPSPI_DER_RDDE; //enable DMA on both TX and RX
    IMXRT_LPSPI4_S.SR = 0x3f00;                           // clear out all of the other status...
}

void Master0::clearTransaction()
{
    IMXRT_LPSPI4_S.FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save; // restore the FSR status...
    IMXRT_LPSPI4_S.DER = 0;                     // DMA no longer doing TX (or RX)

    IMXRT_LPSPI4_S.CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF; // actually clear both...
    IMXRT_LPSPI4_S.SR = 0x3f00;                                     // clear out all of the other status...
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
    dmatx()->disable();
    dmatx()->destination((volatile uint8_t &)IMXRT_LPSPI3_S.TDR);
    dmatx()->disableOnCompletion();
    dmatx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI3_TX);
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
    dmarx()->disable();
    dmarx()->source((volatile uint8_t &)IMXRT_LPSPI3_S.RDR);
    dmarx()->disableOnCompletion();
    dmarx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI3_RX);
    dmarx()->attachInterrupt(tsydmaspi_rxisr_1);
    dmarx()->interruptAtCompletion();
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
    IMXRT_LPSPI3_S.TCR = (IMXRT_LPSPI3_S.TCR & ~(LPSPI_TCR_FRAMESZ(31))) | LPSPI_TCR_FRAMESZ(7);
    IMXRT_LPSPI3_S.FCR = 0;

    // Lets try to output the first byte to make sure that we are in 8 bit mode...
    IMXRT_LPSPI3_S.DER = LPSPI_DER_TDDE | LPSPI_DER_RDDE; //enable DMA on both TX and RX
    IMXRT_LPSPI3_S.SR = 0x3f00;                           // clear out all of the other status...
}

void Master1::clearTransaction()
{
    IMXRT_LPSPI3_S.FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save; // restore the FSR status...
    IMXRT_LPSPI3_S.DER = 0;                     // DMA no longer doing TX (or RX)

    IMXRT_LPSPI3_S.CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF; // actually clear both...
    IMXRT_LPSPI3_S.SR = 0x3f00;                                     // clear out all of the other status...
}



Master2::~Master2()
{
    destroy();
}

bool Master2::begin(const SPISettings& setting)
{
    return this->MasterBase::begin(SPI2, setting);
}

DMAChannel* Master2::dmarx()
{
    static DMAChannel *rx = new DMAChannel();
    return rx;
}

DMAChannel* Master2::dmatx()
{
    static DMAChannel *tx = new DMAChannel();
    return tx;
}

bool Master2::initDmaTx()
{
    if (dmatx() == nullptr)
    {
        Serial.println("[ERROR] create dma tx buffer failed");
        return false;
    }
    dmatx()->disable();
    dmatx()->destination((volatile uint8_t &)IMXRT_LPSPI1_S.TDR);
    dmatx()->disableOnCompletion();
    dmatx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI1_TX);
    if (dmatx()->error())
    {
        delete dmatx();
        return false;
    }
    return true;
}

bool Master2::initDmaRx()
{
    if (dmarx() == nullptr)
    {
        Serial.println("[ERROR] create dma tx buffer failed");
        return false;
    }
    dmarx()->disable();
    dmarx()->source((volatile uint8_t &)IMXRT_LPSPI1_S.RDR);
    dmarx()->disableOnCompletion();
    dmarx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI1_RX);
    dmarx()->attachInterrupt(tsydmaspi_rxisr_2);
    dmarx()->interruptAtCompletion();
    if (dmarx()->error())
    {
        delete dmarx();
        return false;
    }
    return true;
}

void Master2::destroy()
{
    if (dmarx() != nullptr) delete dmarx();
    if (dmatx() != nullptr) delete dmatx();
}

void Master2::initTransaction()
{
    IMXRT_LPSPI1_S.TCR = (IMXRT_LPSPI1_S.TCR & ~(LPSPI_TCR_FRAMESZ(31))) | LPSPI_TCR_FRAMESZ(7);
    IMXRT_LPSPI1_S.FCR = 0;

    // Lets try to output the first byte to make sure that we are in 8 bit mode...
    IMXRT_LPSPI1_S.DER = LPSPI_DER_TDDE | LPSPI_DER_RDDE; //enable DMA on both TX and RX
    IMXRT_LPSPI1_S.SR = 0x3f00;                           // clear out all of the other status...
}

void Master2::clearTransaction()
{
    IMXRT_LPSPI1_S.FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save; // restore the FSR status...
    IMXRT_LPSPI1_S.DER = 0;                     // DMA no longer doing TX (or RX)

    IMXRT_LPSPI1_S.CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF; // actually clear both...
    IMXRT_LPSPI1_S.SR = 0x3f00;                                     // clear out all of the other status...
}



ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

#endif // defined(__IMXRT1062__)
