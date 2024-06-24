#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#include "driver/uart.h"

// Define the UART pins
#define UART_TX_PIN             21
#define UART_RX_PIN             20

// UART configuration
#define UART_PORT_NUM           UART_NUM_1
#define UART_BAUD_RATE          115200
#define UART_DATA_BITS          UART_DATA_8_BITS
#define UART_PARITY             UART_PARITY_DISABLE
#define UART_STOP_BITS          UART_STOP_BITS_1
#define UART_FLOW_CTRL          UART_HW_FLOWCTRL_DISABLE

// Define Misc
#define MESSAGE_DELAY           3000                                                    // Delay in Ticks. Ticks are not milliseconds
#define MESSAGE                 "Hello, this is a periodic message from ESP32-C3! Counter: "      // Message to send via uart and serial console
#define UART_TAG                "UART_PERIODIC_SEND"                                    // Tag that appears in serial output              
#endif // UART_CONFIG_H
