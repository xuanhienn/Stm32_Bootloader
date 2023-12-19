/*
 * FOTA.h
 *
 *  Created on: Dec 19, 2023
 *      Author: Admin
 */
#include <stdint.h>

#ifndef INC_FOTA_H_
#define INC_FOTA_H_

#define ETX_OTA_SOF  0xAA // START OF THE FRAME
#define ETX_OTA_EOF  0xBB
#define ETX_OTA_ACK  0x00
#define ETX_OTA_NACK 0x01

#define ETX_APP_FLASH_ADDR	0x08040000 //application flash address

#define ETX_OTA_DATA_MAX_SIZE (1024)
#define ETX_OTA_DATA_OVERHEAD (9)
#define ETX_OTA_PACKET_MAX_SIZE (ETX_OTA_DATA_MAX_SIZE + ETX_OTA_DATA_OVERHEAD)

typedef enum
{
	ETX_OTA_EX_OK	= 1,
	ETX_OTA_EX_ERR	= 0,
}ETX_OTA_EX_;
/*OTA process state*/
typedef enum
{
	ETX_OTA_STATE_IDLE = 0,
	ETX_OTA_STATE_START = 1,
	ETX_OTA_STATE_HEADER = 2,
	EXT_OTA_STATE_DATA = 3,
	EXT_OTA_STATE_END = 4,
}ETX_OTA_STATE_;

typedef enum
{
	ETX_OTA_PACKET_TYPE_CMD		= 0,
	ETX_OTA_PACKET_TYPE_DATA	= 1,
	ETX_OTA_PACKET_TYPE_HEADER	= 2,
	ETX_OTA_PACKET_TYPE_RESPONE	= 3,
}ETX_OTA_PACKET_TYPE_;

// OTA COMMAND
typedef enum
{
	ETX_OTA_CMD_START	= 0,
	ETX_OTA_CMD_END		= 1,
	ETX_OTA_CMD_ABORT	= 2,
}ETX_OTA_CMD_;
/*
 * OTA META INFO
 */
typedef struct
{
	uint32_t package_size;
	uint32_t package_crc;
	uint32_t reserved1;
	uint32_t reserved2;
}__attribute__((packed)) meta_info;

/*
 * OTA Command format
 *
 * ________________________________________
 * |     | Packet |     |     |     |     |
 * | SOF | Type   | Len | CMD | CRC | EOF |
 * |_____|________|_____|_____|_____|_____|
 *   1B      1B     2B    1B     4B    1B
*/
typedef struct
{
	uint8_t sof;
	uint8_t packet_type;
	uint16_t data_len;
	uint8_t cmd;
	uint32_t crc;
	uint8_t eof;
}__attribute__((packed)) ETX_OTA_COMMAND_;

/*
 * OTA Header format
 *
 * __________________________________________
 * |     | Packet |     | Header |     |     |
 * | SOF | Type   | Len |  Data  | CRC | EOF |
 * |_____|________|_____|________|_____|_____|
 *   1B      1B     2B     16B     4B    1B
 */

typedef struct
{
	uint8_t sof;
	uint8_t packet_type;
	uint16_t data_len;
	meta_info meta_data;
	uint32_t crc;
	uint8_t eof;
}__attribute__((packed)) ETX_OTA_HEADER_;

/*
 * OTA Data format
 *
 * __________________________________________
 * |     | Packet |     |        |     |     |
 * | SOF | Type   | Len |  Data  | CRC | EOF |
 * |_____|________|_____|________|_____|_____|
 *   1B      1B     2B    nBytes   4B    1B
 */
typedef struct
{
	uint8_t sof;
	uint8_t packet_type;
	uint16_t data_len;
	uint32_t *data;
	uint32_t crc;
	uint8_t eof;
}__attribute__((packed)) ETX_OTA_DATA_;

/*
 * OTA Response format
 *
 * __________________________________________
 * |     | Packet |     |        |     |     |
 * | SOF | Type   | Len | Status | CRC | EOF |
 * |_____|________|_____|________|_____|_____|
 *   1B      1B     2B      1B     4B    1B
 */
typedef struct
{
	uint8_t sof;
	uint8_t packet_type;
	uint16_t data_len;
	uint8_t status;
	uint32_t crc;
	uint8_t eof;
}__attribute__((packed)) ETX_OTA_RESP_;

ETX_OTA_EX_ etx_ota_download_and_flash(void);


#endif /* INC_FOTA_H_ */
