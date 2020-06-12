#pragma once
#ifndef ARDUINO_TEENSY_DMA_SPI_MASTER_T32_H
#define ARDUINO_TEENSY_DMA_SPI_MASTER_T32_H
#if defined(KINETISK)

#include "MasterBase.h"

inline void tsydmaspi_rxisr_0();

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN

struct Master0 : public MasterBase
{
    friend void tsydmaspi_rxisr_0();

    virtual ~Master0()
    {
        destroy();
    }

    bool begin(const uint8_t cs, const bool active_low = true)
    {
        return this->MasterBase::begin(SPI, cs, SPISettings(), active_low);
    }

    bool begin(const uint8_t cs, const SPISettings& setting, const bool active_low = true)
    {
        return this->MasterBase::begin(SPI, cs, setting, active_low);
    }

    virtual DMAChannel* dmarx() override final
    {
        static DMAChannel *rx = new DMAChannel();
        return rx;
    }

    virtual DMAChannel* dmatx() override final
    {
        static DMAChannel *tx = new DMAChannel();
        return tx;
    }

    virtual bool initDmaTx() override final
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

    virtual bool initDmaRx() override final
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

    virtual void destroy() override final
    {
        if (dmarx() != nullptr) delete dmarx();
        if (dmatx() != nullptr) delete dmatx();
    }

    virtual void initTransaction() override final
    {
        // TODO:
        // SPI1_SR = 0xFF0F0000;
        // SPI1_RSER = SPI_RSER_RFDF_RE | SPI_RSER_RFDF_DIRS | SPI_RSER_TFFF_RE | SPI_RSER_TFFF_DIRS;
    }

    virtual void clearTransaction() override final
    {
        // TODO:
        // SPI1_RSER = 0;
        // SPI1_SR = 0xFF0F0000;
    }

};

ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END


static TsyDMASPI::Master0 TsyDMASPI0;


inline void tsydmaspi_rxisr_0()
{
    TsyDMASPI0.dmarx()->clearInterrupt();
    TsyDMASPI0.next();
}

#endif // defined(KINETISK)
#endif // ARDUINO_TEENSY_DMA_SPI_MASTER_T32_H
