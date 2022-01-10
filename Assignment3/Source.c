/*******************************************************************************
 *
 * Description: Bai4
 *
 *
 * Last Changed By:  $Author: TrungNT $
 * Revision:         $Revision: 1.0 $
 * Last Changed:     $Date: 22/9/2021 $
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "queue.h"
// Macro------------------------------------------------------------------
#define SIZE_QUEUE_DATA_RX 256
//Khởi tạo giá trị kích thước mảng nhận dữ liệu là 16 bytes.
#define RX_BUFFER_SIZE     16

//------------------------------------------------------------------------
//Sử dụng kiểu liệt kê Enum để kiểm tra các Byte nhận được bao gồm Byte Start,
//các Byte Data và Byte Checkxor.
typedef enum {
	RX_STATE_START_BYTE, RX_STATE_DATA_BYTES, RX_STATE_CXOR_BYTE
} RX_STATE;

/*
 * Sử dụng kiểu liệt kê Enum liệt kê các trạng thái phản hồi khi nhận dữ liệu.
 */
typedef enum {
	UART_STATE_IDLE,
	UART_STATE_DATA_RECEIVED,
	UART_STATE_ACK_RECEIVED,
	UART_STATE_NACK_RECEIVED,
	UART_STATE_ERROR,
	UART_STATE_RX_TIMEOUT,

} UART_STATE;
//----------------------------------------------------------------------------
//Khởi tạo các giá trị cho các byte Start, byte ACK, byte NACK, byte CheckXor
/* @brief Start of frame */
#define FRAME_SOF		0xB1

/* @brief Frame ack and nack */
#define FRAME_ACK		0x06
#define FRAME_NACK		0x15

/* @brief check xor init  */
#define CXOR_INIT_VAL	0xFF

/*
 * Gán các giá trị các phần tử trong mảng byRxBuffer với các giá trị kiểm tra
 * dữ liệu sau khi nhận được dữ liệu gồm các byte Command ID, Command Type, và Data.
 */
#define CMD_ID				byRxBuffer[2]
#define CMD_TYPE			byRxBuffer[3]
#define CMD_DATA_EPOINT		byRxBuffer[4]
#define CMD_DATA_STATE		byRxBuffer[5]
/*	Private variables**************************************************/
static uint8_t byRxBufState;
static uint8_t byIndexRxBuf;
static uint8_t byCheckXorRxBuf;
static buffqueue_t serialQueueRx;
static uint8_t pBuffDataRx[SIZE_QUEUE_DATA_RX];
uint8_t byRxBuffer[RX_BUFFER_SIZE] = { 0 };

//-----------------------------------------------------------------------
uint8_t SerialPoll(void);
static void check_data_transmis(void);
//-----------------------------------------------------------------------
int main() {
	// Define Strings
	uint8_t i;
	uint8_t stateRx;

	unsigned int frame[9];
	/* Initializes receive register buffer	*/
	bufInit(pBuffDataRx, &serialQueueRx, sizeof(pBuffDataRx[0]),
			SIZE_QUEUE_DATA_RX);
	printf("Enter Frame: ");

	for (i = 0; i < 9; i++) {
		fflush(stdout);
		scanf("%x", &frame[i]);
		bufEnDat(&serialQueueRx, (uint8_t*) &frame[i], 1);
	}
//-----------------------------------------------------------------------------------------------
	stateRx = SerialPoll();
	if (stateRx != UART_STATE_IDLE) {
		switch (stateRx) {
		case UART_STATE_ACK_RECEIVED:
			printf("UART_STATE_ACK_RECEIVED\r\n");
			break;

		case UART_STATE_NACK_RECEIVED:
			printf("UART_STATE_NACK_RECEIVED\r\n");
			break;

		case UART_STATE_DATA_RECEIVED:
			printf("UART_STATE_DATA_RECEIVED\n");
			check_data_transmis();
			break;

		case UART_STATE_ERROR:
		case UART_STATE_RX_TIMEOUT:
			printf("UART_STATE_RX_TIMEOUT\r\n");
			break;

		default:
			break;
		}
	}
	getchar();
	getchar();
	return 0;
}
uint8_t SerialPoll(void) {
	uint8_t byRxData;
	uint8_t byUartState = (uint8_t) UART_STATE_IDLE;
	while ((bufNumItems(&serialQueueRx) != 0)
			&& (byUartState == UART_STATE_IDLE)) {
		bufDeDat(&serialQueueRx, &byRxData, 1);
		switch (byRxBufState) {
		case RX_STATE_START_BYTE:
			if (byRxData == FRAME_SOF) {
				byIndexRxBuf = 0;
				byCheckXorRxBuf = CXOR_INIT_VAL;
				byRxBufState = RX_STATE_DATA_BYTES;
			} else if (byRxData == FRAME_ACK) {
				byUartState = UART_STATE_ACK_RECEIVED;
			} else if (byRxData == FRAME_NACK) {
				byUartState = UART_STATE_NACK_RECEIVED;
			} else {
				byUartState = UART_STATE_ERROR;
			}
			break;
		case RX_STATE_DATA_BYTES:
			if (byIndexRxBuf < RX_BUFFER_SIZE) {
				byRxBuffer[byIndexRxBuf] = byRxData;
				if (byIndexRxBuf > 0) {
					byCheckXorRxBuf ^= byRxData;
				}
				if (++byIndexRxBuf == *byRxBuffer) {
					byRxBufState = RX_STATE_CXOR_BYTE;
				}
			} else {
				byRxBufState = RX_STATE_START_BYTE;
				byUartState = UART_STATE_ERROR;
			}
			break;
		case RX_STATE_CXOR_BYTE: {
			if (byRxData == byCheckXorRxBuf) {
				byUartState = UART_STATE_DATA_RECEIVED;
			} else {
				byUartState = UART_STATE_ERROR;
			}
		default:
		byRxBufState = RX_STATE_START_BYTE;
		break;
		}

		}
	}
	return byUartState;
}
/*
 *
 */
static void check_data_transmis(void) {
	if (CMD_ID== 0x00)
	{
		if(CMD_TYPE == 0x00)
		{
			printf("Board STM32F4 Nucleo\r\n");
		}
	}
	else if(CMD_ID == 0x01)
	{
		if(CMD_TYPE == 0x02)
		{
			if(CMD_DATA_STATE == 0xff)
			{
				printf("Led turned on\r\n");
			}
			else
			{
				printf("Led turned off\r\n");
			}
		}
	}
	else if(CMD_ID == 0x04)
	{
		if(CMD_TYPE == 0x02)
		{
			if(CMD_DATA_STATE == 0xff)
			{
				printf("Buzzer turned on\r\n");
			}
			else
			{
				printf("Buzzer turned off\r\n");
			}
		}
	}
	else if(CMD_ID == 0x84)
	{
		if(CMD_TYPE == 0x01)
		{
			printf("Update value temp \r\n");
		}
		if(CMD_TYPE == 0x00)
		{
			printf("Request send temp to computer \r\n");
		}
	}
	else if(CMD_ID == 0x85)
	{
		if(CMD_TYPE == 0x01)
		{
			printf("Update value humi \r\n");
		}
		if(CMD_TYPE == 0x00)
		{
			printf("Request send humi to computer \r\n");
		}
	}
	else if(CMD_ID == 0x86)
	{
		if(CMD_TYPE == 0x01)
		{
			printf("Update value light \r\n");
		}
		if(CMD_TYPE == 0x00)
		{
			printf("Request send light to computer \r\n");
		}
	}
	else
	{
		printf("Error!");
	}

}

/*
* SOF	LENGTH	OTP		CMD_ID
 b1 07 00 00 00 00 00 00 ff    // Thông tin thiết bị
 b1 07 00 01 02 00 ff 00 03    // Điều khiển bật led
 b1 07 00 01 02 00 00 00 fc    // Điều khiển tắt led
 b1 07 00 04 02 ff 00 00 06    // Điều khiển bật còi
 b1 07 00 04 02 00 00 00 f9    // Điều khiển tắt còi
 b1 07 00 84 01 00 00 00 7a  // Cập nhật giá trị nhiệt độ
 b1 07 00 85 01 00 00 00 7b   // Cập nhật giá trị độ ẩm
 b1 07 00 86 01 00 00 00 78    // Cập nhật giá trị ánh sáng
 b1 07 00 84 00 00 00 00 7b   // Yêu cầu gửi giá trị nhiệt độ lên máy tính
 b1 07 00 85 00 00 00 00 7a   // Yêu cầu gửi giá trị độ ẩm lên máy tính
 b1 07 00 86 00 00 00 00 79   // Yêu cầu gửi giá trị ánh sáng lên máy tính
 Lưu ý: Chỉ nhập giá trị phía sau “0x” của mã Hex. Hãy tìm giá trị xx?

 CXOR = 0xFF ^ OPT ^ CMDID ^ CMDTYPE ^ DATA(n bytes) ^ SEQUENCE.
 */
