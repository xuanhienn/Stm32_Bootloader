/*
 * FOTA.c
 *
 *  Created on: Dec 19, 2023
 *      Author: Admin
 */
#include <stdio.h>
#include "FOTA.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>

// buffer to receive data
static uint8_t Rx_Buffer[ETX_OTA_DATA_MAX_SIZE];

// OTA State
static ETX_OTA_STATE_ ota_state = ETX_OTA_STATE_IDLE;

/* Firmware Total Size that we are going to receive */
static uint32_t ota_fw_total_size;
static uint32_t ota_fw_crc;
static uint32_t ota_fw_received_size;

static uint16_t etx_received_chunk(uint8_t *buff, uint16_t max_length);

static ETX_OTA_EX_ etx_process_data(uint8_t *buf, uint16_t len);

static void etx_ota_send_resp(uint8_t type);

static HAL_StatusTypeDef write_data_to_flash_app(uint8_t *data, uint16_t len, bool is_full_image);
