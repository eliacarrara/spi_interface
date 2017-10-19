#pragma once

#include <linux/spi/spidev.h>
#include <string>

using namespace std;

enum class Endianess {
    MSB = 0x0,
    LSB = 0x1,
};

// see linux/spi/spidev.h
enum class SpiMode {
    SpiMode0 = SPI_MODE_0,
    SpiMode1 = SPI_MODE_1,
    SpiMode2 = SPI_MODE_2,
    SpiMode3 = SPI_MODE_3,
};

class SpiInterface {
    __int32_t m_Fd;
    std::string m_FileName;
    spi_ioc_transfer m_SpiMsg;
public:
    SpiInterface(const std::string & FileName);

    bool Open();
    bool Close();
    bool IsOpen() const { return m_Fd > -1; }

    SpiMode GetMode() const;
    __uint8_t GetBitsPerWord() const;
    __uint32_t GetSpeed() const;
    Endianess GetEndianness() const;

    void SetMode(SpiMode Mode) const;
    void SetBitsPerWord(__uint8_t bpw) const;
    void SetSpeed(__uint32_t Speed) const;
    void SetEndianness(Endianess Endian) const;

    void Transact(__uint8_t * tx_data, __uint8_t *rx_data, size_t length);
};
