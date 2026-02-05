/*
 * Copyright (c) 2026, MDLZCOOL
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ctshell_esp32.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"

typedef struct {
    uart_port_t uart_num;
} ctshell_esp32_priv_t;

static ctshell_ctx_t *g_ctx;
static ctshell_esp32_priv_t priv;
static TaskHandle_t s_shell_task_handle = NULL;

static void esp32_shell_write(const char *str, uint16_t len, void *p) {
    ctshell_esp32_priv_t *d = (ctshell_esp32_priv_t *) p;
    uart_write_bytes(d->uart_num, str, len);
}

static uint32_t esp32_get_tick(void) {
    return (uint32_t)(esp_timer_get_time() / 1000ULL);
}

static void shell_rx_task(void *arg) {
    uint8_t data;
    while (1) {
        int len = uart_read_bytes(priv.uart_num, &data, 1, portMAX_DELAY);

        if (len > 0) {
            ctshell_input(g_ctx, data);
        }

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void ctshell_esp32_init(ctshell_ctx_t *ctx, uart_port_t uart_num) {
    memset(&priv, 0, sizeof(priv));
    priv.uart_num = uart_num;
    g_ctx = ctx;

    ctshell_io_t io = {
            .write = esp32_shell_write,
            .get_tick = esp32_get_tick,
    };

    ctshell_init(ctx, io, &priv);

    xTaskCreate(shell_rx_task, "shell_rx", 2048, NULL, 5, &s_shell_task_handle);
}
