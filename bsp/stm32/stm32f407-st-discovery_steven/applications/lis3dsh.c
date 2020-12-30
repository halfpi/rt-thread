#include "lis3dsh.h"

#define MEMS_TRACE

#ifdef MEMS_TRACE
    #define MEMS_DEBUG         rt_kprintf
#else
    #define MEMS_DEBUG(...)
#endif

static struct rt_spi_device *spi_device;

static void spi_read_op(struct rt_spi_device *spi_device, uint8_t reg, uint8_t *data, uint32_t len)
{
    reg |= (uint8_t)0x80; // 读操作的RW位为1

    rt_spi_send_then_recv(spi_device, &reg, 1, data, len);
}

static void spi_write_op(struct rt_spi_device *spi_device, uint8_t reg, uint8_t *data, uint32_t len)
{
    reg &= (uint8_t)0x7F; // 写操作的RW位为0

    rt_spi_send_then_send(spi_device, &reg, 1, data, len);
}

rt_err_t lis3dsh_attach(const char *spi_device_name)
{
    spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if (spi_device == RT_NULL)
    {
        MEMS_DEBUG("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }
    
    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_3 | RT_SPI_MSB;
        cfg.max_hz = 500 * 1000;
        rt_spi_configure(spi_device, &cfg);
    }

    /* detect device */
    uint8_t id = 0;
    spi_read_op(spi_device, LIS3DSH_WHO_AM_I, &id, 1); // 第一次执行的目的：使SPI CLK变高电平
    spi_read_op(spi_device, LIS3DSH_WHO_AM_I, &id, 1); // 读回WHO_AM_I为0x3F
}
