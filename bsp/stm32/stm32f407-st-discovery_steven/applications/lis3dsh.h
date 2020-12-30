#ifndef _LIS3DSH_H_
#define _LIS3DSH_H_

#include <rtthread.h>
#include <drivers/spi.h>
#include "lis3dsh_reg.h"

int32_t lis3dsh_data_output(lis3dsh_data_t *data);

rt_err_t lis3dsh_attach(const char *spi_device_name);

#endif
