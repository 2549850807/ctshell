/*
 * Copyright (c) 2026, MDLZCOOL
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "ctshell.h"
#include "driver/uart.h"

#ifdef __cplusplus
extern "C" {
#endif

void ctshell_esp32_init(ctshell_ctx_t *ctx, uart_port_t uart_num);

#ifdef __cplusplus
}
#endif
