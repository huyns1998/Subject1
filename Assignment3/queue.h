/******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Ring buffer queue
 *
 * Author: HoangNH
 *
 * Bug Fixes: Fix buffer overflow. Thanks to Mr.Thien reported.
 *
 * Last Changed By:  $Author: hoangnh $
 * Revision:         $Revision: 1.2 $
 * Last Changed:     $Date: 7/6/2020 $
 *
 ******************************************************************************/
#ifndef _QUEUE_H_
#define _QUEUE_H_
 /******************************************************************************/
 /*                              INCLUDE FILES                                 */
 /******************************************************************************/
#include <stdint.h>
#include <string.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define QUEUE_BUFFER_SIZE 32

#if (QUEUE_BUFFER_SIZE & (QUEUE_BUFFER_SIZE - 1)) != 0
#error "QUEUE_BUFFER_SIZE must be a power of two"
#endif

#define ERR_OK                         0x00 
#define ERR_BUF_FULL                   0x01
#define ERR_BUF_EMPTY                  0x02     
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/*!
 * FIFO structure
 */
typedef struct __buff_queue__ {
    uint16_t wCountElement;  /*< Count element */
    uint16_t wHeadIndex;  /*< Points to the beginning of the queue storage area. */
    uint16_t wTailIndex;  /*< Points to the byte at the end of the queue storage area */
    uint8_t buffer[QUEUE_BUFFER_SIZE];  /*< Data memory */
} buffqueue_t, * buffqueue_p;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
/**
 * @func   bufInit
 * @brief  Initializes the FIFO structure
 * @param  pBuffer: Data to be pushed into the FIFO
 * @param  pQueue: Pointer to the FIFO object
 * @param  sizeofElement: Size of a element in the buffer
 * @param  numberOfElement: Size of the buffer
 * @retval None
 */
void
bufInit(
    buffqueue_p pQueue
);

/**
 * @func   bufNumEle
 * @brief  Determine number of bytes in FIFO has not been processed
 * @param  pQueue: Pointer to the FIFO object
 * @retval Number of bytes in FIFO
 */
uint16_t
bufNumItems(
    buffqueue_p pQueue
);

/**
 * @func   bufIsEmpty
 * @brief  Checks if the FIFO is empty
 * @param  pQueue: Pointer to the FIFO object
 * @retval TRUE of FALSE
 */
uint8_t
bufIsEmpty(
    buffqueue_p pQueue
);

/**
 * @func   bufEnDat
 * @brief  Pushes data to the FIFO
 * @param  pQueue: Pointer to the FIFO object
 * @param  pReceiverData: Received data to be pushed into the FIFO
 * @retval ERR_OK or ERR_BUF_FUL
 */
uint8_t
bufEnDat(
    buffqueue_p pQueue,
    uint8_t* pReceiverData,
    uint8_t sizeofReceiverData
);

/**
 * @func   bufDeDat
 * @brief  Pops data from the FIFO
 * @param  pQueue: Pointer to the FIFO object
 * @param  pBuffer: Data in the FIFO popped into the buffer
 * @retval ERR_OK or ERR_BUF_EMPTY
 */
uint8_t
bufDeDat(
    buffqueue_p pQueue,
    uint8_t* pBuffer,
    uint8_t sizeofBuffer
);

#endif /* END FILE */
