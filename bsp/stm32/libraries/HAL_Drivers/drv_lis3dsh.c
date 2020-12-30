#include <drivers/pin.h>
#include "drv_spi.h"
#include <board.h>

#include "lis3dsh.h"
#include "lis3dsh_reg.h"


static int lis3dsh_init(void)
{
    __HAL_RCC_GPIOE_CLK_ENABLE();
    rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_LIS3DSH_DEVICE_NAME, GPIOE, GPIO_PIN_3);

    lis3dsh_attach(SPI_LIS3DSH_DEVICE_NAME);

    return 0;
}
INIT_COMPONENT_EXPORT(lis3dsh_init);

