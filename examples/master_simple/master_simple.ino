#include <TsyDMASPI.h>

// connect MOSI and MISO on Teensy (loop back)

#define PIN_CS 10
#define DMASIZE 8192
uint8_t src[DMASIZE];
volatile uint8_t dest[DMASIZE];
volatile uint8_t dest1[DMASIZE];

void dumpBuffer(const volatile uint8_t *buf, const char *prefix)
{
    Serial.print(prefix);
    for (size_t i = 0; i < DMASIZE; i++)
    {
        Serial.printf("0x%02x ", buf[i]);
    }
    Serial.print('\n');
}

void compareBuffers(const uint8_t *src_, const uint8_t *dest_)
{
    int n = memcmp((const void *)src_, (const void *)dest_, DMASIZE);
    if (n == 0)
    {
        Serial.println("src and dest match");
    }
    else
    {
        Serial.println("src and dest don't match");
        dumpBuffer(src_, " src: ");
        dumpBuffer(dest_, "dest: ");
    }
}

void setSrc()
{
    for (size_t i = 0; i < DMASIZE; i++)
    {
        src[i] = i;
    }
}

void clrDest(uint8_t *dest_)
{
    memset((void *)dest_, 0x00, DMASIZE);
}


void setup()
{
    Serial.begin(115200);

    delay(5000);

    setSrc();
    clrDest((uint8_t *)dest);

    TsyDMASPI0.begin(PIN_CS, SPISettings(4000000, MSBFIRST, SPI_MODE3));

    Serial.println("Testing src -> dest, single transfer");
    Serial.println("--------------------------------------------------");
    TsyDMASPI0.transfer(src, dest, DMASIZE);
    compareBuffers(src, (const uint8_t *)dest);
    Serial.println("==================================================\n\n");

    Serial.println("Testing multiple queued transfers");
    Serial.println("--------------------------------------------------");
    setSrc();
    clrDest((uint8_t *)dest);
    clrDest((uint8_t *)dest1);
    TsyDMASPI0.queue(src, dest, DMASIZE);
    TsyDMASPI0.queue(src, dest1, DMASIZE);
    TsyDMASPI0.yield();
    compareBuffers(src, (const uint8_t *)dest);
    compareBuffers(src, (const uint8_t *)dest1);
    Serial.println("==================================================\n\n");

    TsyDMASPI0.end();
}

void loop()
{
}
