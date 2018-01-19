#include "ESP32.h"

int initATCtrl(u32 UART_DEVICE_ID, Uart * devicePtr, INTC * intPtr) {
    int Status;
	xil_printf("Inside of initATCtrl\n\r");
    Status = XUartLite_Initialize(devicePtr, UART_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        xil_printf("Could not initialize uart\n\r");
        return XST_FAILURE;
    }

    Status = XIntc_Initialize(intPtr, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
        xil_printf("Could not Initialize Interrupt Controller\n\r");
        return XST_FAILURE;
	}

    Status = XIntc_Connect(intPtr, UARTLITE_INT_IRQ_ID,
               (XInterruptHandler)XUartLite_InterruptHandler,
               (void *)devicePtr);
    if (Status != XST_SUCCESS) {
        xil_printf("Could not Connect UART to  Interrupt Controller\n\r");
        return XST_FAILURE;
    }

    Status = XIntc_Start(intPtr, XIN_REAL_MODE);
    if (Status != XST_SUCCESS) {
        xil_printf("Could not start interrupt controller\n\r");
        return XST_FAILURE;
    }

    XIntc_Enable(intPtr, UARTLITE_INT_IRQ_ID);

    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 (Xil_ExceptionHandler)XIntc_InterruptHandler,
			 intPtr);

    Xil_ExceptionEnable();

    XUartLite_SetRecvHandler(devicePtr, uartRecvHandler, devicePtr);
    XUartLite_EnableInterrupt(devicePtr);

    // unsigned char buf[100];
    // XUartLite_Recv(devicePtr, buf, 100);

    xil_printf("Finished setting up Interrupt system and Uart\n\r");

    return XST_SUCCESS;
}

void uartRecvHandler(void * CallBackRef, unsigned int EventData) {
	// int recvd = 0;
	// u8 rx_buf[512];
	// xil_printf("Interrupt Triggered\n\r");
	// // Start receiving new sentence
	// recvd = XUartLite_Recv(CallBackRef, rx_buf, 512);
	// if(recvd) {
	// 	u8 * charPtr = rx_buf;
	// 	for(int i = 0; i < recvd; i++) {
	// 		xil_printf("%c", charPtr++);
	// 	}
    //     xil_printf("\n\r");
	// }
	Uart * devicePtr = (Uart *) CallBackRef;
    char c;
    while(!XUartLite_IsReceiveEmpty(devicePtr->RegBaseAddress)) {
        c = XUartLite_RecvByte(devicePtr->RegBaseAddress);
        xil_printf("%c", c);
    }
}

int resetESP32(Uart * devicePtr) {
	unsigned char tx[6];
	sprintf((char *)tx, "%s+RST", AT_STUB);
	XUartLite_Send(devicePtr, tx, 6);
	sendNLCR(devicePtr);
	return XST_SUCCESS;
}

int sendNLCR(Uart * devicePtr) {
	unsigned char tx[2] = {'\n','\r'};
	XUartLite_Send(devicePtr, tx, 2);
	return XST_SUCCESS;
}
