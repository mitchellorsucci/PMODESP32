/*
 * main.c
 *
 *  Created on: Jan 17, 2018
 *      Author: mitchellorsucci
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <unistd.h>
#include "xgpio.h"

#include "ESP32.h"

#define RX_BUF_SIZE 512

/************ Global Variables ************/
INTC intc;
Uart ESP_32;
unsigned char rx_buf [RX_BUF_SIZE];

int main() {
    memset(rx_buf, 0, RX_BUF_SIZE);
    int status;
    xil_printf("Hello World\n\r");
    // Initializes UART for AT command control of ESP
    Uart * esp_device = &ESP_32;
	status = initATCtrl(UARTLITE_DEVICE_ID, esp_device, &intc);
    if(status != XST_SUCCESS) {
    	xil_printf("Error setting up UART/Interrupt\n\r");
    	return XST_FAILURE;
    }
	// status = setupInterrupt(esp_device, INTERRUPT_DEV_ID, UART_INTERRUPT_ID);
    // if(status != XST_SUCCESS) {
    //     xil_printf("Could not set up interrupt system\n\r");
    //     return -1;
    // }
	// Initializes USB-UART
    init_platform();

    xil_printf("Setting up GPIOS\n\r");
    XGpio_Config * gpio_config = XGpio_LookupConfig(XPAR_GPIO_0_DEVICE_ID);
    XGpio OUTS;
    XGpio_CfgInitialize(&OUTS, gpio_config, XPAR_GPIO_0_BASEADDR);
    XGpio_SetDataDirection(&OUTS, 1, 0);

    resetESP32(esp_device);

    while(1) {
		XGpio_DiscreteWrite(&OUTS, 1, 5);
		usleep(100000);
		XGpio_DiscreteWrite(&OUTS, 1, 0);
		usleep(100000);
    }

    cleanup_platform();
    return 0;
}
