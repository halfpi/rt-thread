/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     misonyo   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "button.h"
#include "lis3dsh.h"
#include <stdio.h>

/* defined the LED4 pin: PD12 */
#define LED4_PIN    GET_PIN(D, 12)
/* defined the LED5 pin: PD14 */
#define LED5_PIN    GET_PIN(D, 14)

#define KEY_PIN          GET_PIN(A, 0)
#define KEY_PRESS_VALUE  1

void spi_test(void);

void key_cb(struct my_button *button)
{
    switch (button->event)
    {
    case BUTTON_EVENT_CLICK_UP:
        rt_pin_write(LED4_PIN, !rt_pin_read(LED4_PIN));
        rt_kprintf("This is click up callback!\n");
        break;
    case BUTTON_EVENT_HOLD_CYC:
        rt_pin_write(LED4_PIN, !rt_pin_read(LED4_PIN));
        rt_kprintf("This is hold cyc callback!\n");
        break;
    default:
        ;
    }
}

int main(void)
{
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED5_PIN, PIN_MODE_OUTPUT);

    static struct my_button key = {0};
    key.press_logic_level = KEY_PRESS_VALUE;
    key.hold_cyc_period = 100;
    key.cb = (my_button_callback)key_cb;
    key.pin = KEY_PIN;
    my_button_register(&key);
    my_button_start();
		
    while (1)
    {
        rt_pin_write(LED5_PIN, !rt_pin_read(LED5_PIN));
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
