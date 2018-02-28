/*******************************************************************************
    The AT commands utilized here for interfacing with the ESP32 are found
    in the document ESP32_AT_Instruction_Set_and_Example__EN provided by
    ESPRESSIF> This library does not implement all of the AT commands that
    are available to be used. If the user wishes to use an AP command that is
    not included in the library, the user can implement it in much the same
    way that these AT commands are implemented
*******************************************************************************/

/*******************************************************************************
    Revision History

    01/26/18        Initial Release         Mitchell Orsucci
                                            (mitchell.orsucci@ni.com)

*******************************************************************************/

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
#include <unistd.h>

//#define UART_BUF_SIZE			16
//#define UART_BUF_SIZE			15
#define UART_BUF_SIZE			14

/*************************** XILINX ARGUMENT MACROS ***************************/
#define UARTLITE_DEVICE_ID      XPAR_UARTLITE_1_DEVICE_ID
#define INTC_DEVICE_ID          XPAR_INTC_0_DEVICE_ID
#define UARTLITE_INT_IRQ_ID     XPAR_INTC_0_UARTLITE_1_VEC_ID

/***************************** TYPEDEFs ***************************/
typedef XUartLite         	    Uart;
#define INTC                    XIntc
#define INTC_HANDLER            XIntc_InterruptHandler

/****************************** WIFI COMMAND MACROS ***************************/
    // Wifi mode macros
#define NULL_MODE				0
#define STATION_MODE			1
#define SOFTAP_MODE				2
#define SOFTAP_AND_STATION_MODE	3

    // Encryption mode macros for SoftAP mode
#define NO_PASSWORD             0
#define WPA_PSK                 2
#define WPA2_PSK                3
#define WPA_WPA2_PSK            4

/****************************** AT Control Utilities **************************/
int initATCtrl(u32 UART_DEVICE_ID, Uart * devicePtr, INTC * intPtr);
int resetESP32(Uart * devicePtr);
int checkVersionInfo(Uart * devicePtr);
int enterDeepSleep(Uart * devicePtr, unsigned int time);
int sendNLCR(Uart * devicePtr);

/****************************** WiFi Control Functions ************************/
int getWiFiMode(Uart * devicePtr);
int setWiFiMode(Uart * devicePtr, unsigned int mode);
int getCurrentAP(Uart * devicePtr);
int setCurrentAP(Uart * devicePtr, char * ssid, char * pwd, char * bssid);
int listAvailableAPs(Uart * devicePtr, char * ssid);
int setDHCPmode(Uart * devicePtr, u8 operate, u8 mode);
int getDHCPmode(Uart * devicePtr);
int getSoftAPConfiguration(Uart * devicePtr);
int setSoftAPConfiguration(Uart * devicePtr, char * ssid, char * pwd,
    u8 channel, u8 encryption, u8 maxConn, u8 hidden);
int listCurrentSoftAPConnections(Uart * devicePtr);

/**************************** TCP/IP Control Utilities ************************/
int getConnectionStatus(Uart * devicePtr);
int establishTCPConnection(Uart * devicePtr, char * remoteIP,
     int remotePort, int TCP_KeepAlive);
int TCPsend(Uart * devicePtr, u8 * data, int length);



/************************ AxiUartLite Control Functions ***********************/
int setupInterrupt(Uart * devicePtr, u32 interruptDeviceID, u32 interruptID);
void uartRecvHandler(void * CallBackRef, unsigned int EventData);
void uartSendHandler(void * CallBackRef, unsigned int EventData);

#endif  /* end of protection macro */
