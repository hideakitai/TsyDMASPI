#ifndef ARDUINO_TEENSY_DMA_SPI_MASTER_T36_H
#define ARDUINO_TEENSY_DMA_SPI_MASTER_T36_H
#if defined(__MK64FX512__) || defined(__MK66FX1M0__)

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

struct Master2 : public MasterBase
{
    friend void tsydmaspi_rxisr_2();

    virtual ~Master2();

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

#endif // defined(__MK64FX512__) || defined(__MK66FX1M0__)
#endif // ARDUINO_TEENSY_DMA_SPI_MASTER_T36_H
