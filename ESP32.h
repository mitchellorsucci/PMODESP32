#ifndef ESP32_H
#define ESP32_H

#include "xparameters.h"
#include "xil_printf.h"
#include "xintc.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xintc_l.h"
#include "xuartlite.h"
#include "xil_exception.h"
#include "xuartlite_l.h"
#include <stdio.h>


#define UARTLITE_DEVICE_ID      XPAR_UARTLITE_1_DEVICE_ID
#define INTC_DEVICE_ID          XPAR_INTC_0_DEVICE_ID
#define UARTLITE_INT_IRQ_ID     XPAR_INTC_0_UARTLITE_1_VEC_ID

#define AT_STUB					"AT"

// Typedefs for cleaner code
typedef XUartLite         	    Uart;
#define INTC                    XIntc
#define INTC_HANDLER            XIntc_InterruptHandler


int initATCtrl(u32 UART_DEVICE_ID, Uart * devicePtr, INTC * intPtr);
int resetESP32(Uart * devicePtr);
int sendNLCR(Uart * devicePtr);

int setupInterrupt(Uart * devicePtr, u32 interruptDeviceID, u32 interruptID);
void uartRecvHandler(void * CallBackRef, unsigned int EventData);

#endif  /* end of protection macro */
