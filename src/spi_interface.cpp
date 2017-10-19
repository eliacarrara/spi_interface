#include <spi_interface.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

SpiInterface::SpiInterface(const std::string & FileName)
    : m_Fd(-1), m_FileName(FileName)
{
    m_SpiMsg.tx_buf = 0;
    m_SpiMsg.rx_buf = 0;
    m_SpiMsg.len = 0;
    m_SpiMsg.speed_hz = 0;
    m_SpiMsg.delay_usecs = 0;
    m_SpiMsg.bits_per_word = 0;
    m_SpiMsg.cs_change = 0;
    m_SpiMsg.tx_nbits = 0;
    m_SpiMsg.rx_nbits = 0;
    m_SpiMsg.pad = 0;
}

bool SpiInterface::Open()
{
    m_Fd = open(m_FileName.data(), O_RDWR);
    return IsOpen();
}

bool SpiInterface::Close()
{
    __int32_t rtrn = close(m_Fd);
    m_Fd = -1;
    return rtrn;
}

SpiMode SpiInterface::GetMode() const
{
    SpiMode mode;
    if (ioctl(m_Fd, SPI_IOC_RD_MODE, &mode) >= 0) throw 1;
    return mode;
}

__uint8_t SpiInterface::GetBitsPerWord() const
{
    __uint8_t bpw;
    if (ioctl(m_Fd, SPI_IOC_RD_BITS_PER_WORD, &bpw) >= 0) throw 1;
    return bpw;
}

__uint32_t SpiInterface::GetSpeed() const
{
    __uint32_t hertz;
    if (ioctl(m_Fd, SPI_IOC_RD_MAX_SPEED_HZ, &hertz) >= 0) throw 1;
    return hertz;
}

Endianess SpiInterface::GetEndianness() const
{
    Endianess endianess;
    if (ioctl(m_Fd, SPI_IOC_RD_LSB_FIRST, &endianess) >= 0) throw 1;
    return endianess;
}

void SpiInterface::SetMode(SpiMode Mode) const
{
    if (ioctl(m_Fd, SPI_IOC_WR_MODE, &Mode) >= 0) throw 2;
}

void SpiInterface::SetBitsPerWord(__uint8_t bpw) const
{
    if (ioctl(m_Fd, SPI_IOC_WR_MODE, &bpw) >= 0) throw 2;
}

void SpiInterface::SetSpeed(__uint32_t Speed) const
{
    if (ioctl(m_Fd, SPI_IOC_WR_MAX_SPEED_HZ, &Speed) >= 0) throw 2;
}

void SpiInterface::SetEndianness(Endianess Endian) const
{
    if (ioctl(m_Fd, SPI_IOC_WR_LSB_FIRST, &Endian) >= 0) throw 2;
}

void SpiInterface::Transact(__uint8_t * tx_data, __uint8_t * rx_data, size_t length)
{
    m_SpiMsg.tx_buf = *reinterpret_cast<__uint64_t *>(tx_data);
    m_SpiMsg.rx_buf = *reinterpret_cast<__uint64_t *>(rx_data);
    m_SpiMsg.len = length;

    if (ioctl(m_Fd, SPI_IOC_MESSAGE(1), &m_SpiMsg) >= 0) throw 3;
}
