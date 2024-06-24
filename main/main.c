#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "config.h"

static const char *TAG = UART_TAG;
//static const char *MESSAGE = "Hello, this is a periodic message from ESP32-C3!";

void uart_init(void) {
    const uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_BITS,
        .parity    = UART_PARITY,
        .stop_bits = UART_STOP_BITS,
        .flow_ctrl = UART_FLOW_CTRL,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Install UART driver, and get the queue.
    uart_driver_install(UART_PORT_NUM, 256, 0, 0, NULL, 0);
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void periodic_send_task(void *pvParameters) {
    int counter = 0;
    char message_to_send[100];
    while (1) {
        snprintf(message_to_send, sizeof(message_to_send), "%s%d", MESSAGE, counter); //Combine MESSAGE and counter into String
        uart_write_bytes(UART_PORT_NUM, message_to_send, strlen(message_to_send));
        ESP_LOGI(TAG, "Message sent: %s", message_to_send);
        ESP_LOGI(TAG, "Next message in: %d ticks", MESSAGE_DELAY);
        ESP_LOGI(TAG, "*********************************************");
        counter++;
        vTaskDelay(pdMS_TO_TICKS(MESSAGE_DELAY));  // Delay configured in config.h
    }
}

void app_main(void) {
    // Initialize UART
    uart_init();

    // Create a task to periodically send messages
    xTaskCreate(periodic_send_task, "periodic_send_task", 2048, NULL, 10, NULL);
}
