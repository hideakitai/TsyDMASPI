#ifndef ARDUINO_TEENSY_DMA_SPI_MASTER_TLC_H
#define ARDUINO_TEENSY_DMA_SPI_MASTER_TLC_H
#if defined (KINETISL)

#include "MasterBase.h"

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN


struct Master0 : public MasterBase
{
    friend void tsydmaspi_rxisr_0();

    virtual ~Master0();

    bool begin(const SPISettings& setting);

    virtual DMAChannel* dmarx() final;
    virtual DMAChannel* dmatx() final;

    virtual bool initDmaTx() final;
    virtual bool initDmaRx() final;
    virtual void destroy() final;

    virtual void initTransaction() final;
    virtual void clearTransaction() final;

};

struct Master1 : public MasterBase
{
    friend void tsydmaspi_rxisr_1();

    virtual ~Master1();

    bool begin(const SPISettings& setting);

    virtual DMAChannel* dmarx() final;
    virtual DMAChannel* dmatx() final;

    virtual bool initDmaTx() final;
    virtual bool initDmaRx() final;
    virtual void destroy() final;

    virtual void initTransaction() final;
    virtual void clearTransaction() final;

};


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END

#endif // defined (KINETISL)
#endif // ARDUINO_TEENSY_DMA_SPI_MASTER_TLC_H
