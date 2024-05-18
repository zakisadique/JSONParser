/**
* \file uart.h
* \author P. Fromm
* \date 8.12.19
*
* \brief uard wrapper driver
*
*
* \note Set the symbols in the cfg file to the port you want to use and configure the buffer size in the ringbuffer config file
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 8.12.19; P. Fromm
*            - Initial Release
*
* \copyright Copyright �2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
**/


 
#ifndef UART_H
#define UART_H

#include "global.h"
#include "ringBuffer.h"
#include "UART_LOG.h"
#include "cfg.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#define UART_start() UART_LOG_Start()
#define UART_putString(data) UART_LOG_PutString(data);
    
#define UART_writeByte(data) UART_LOG_WriteTxData(data)
    
#define UART_readByte() UART_LOG_GetByte()   
    

    

//####################### Structures
/**
* \brief The rinbuffer structure contains all data elements representing a ringbuffer object
*
*/
struct sUart {
    RB_t   m_txBuffer;
    RB_t   m_rxBuffer;
    uint16_t countISR;
};
typedef struct sUart UART_t;

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Uart
{
public:
#endif /* Together */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Init a Uart Port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_init(UART_t *const me);

/**
 * Write a string to the UART, Using Ringbuffer and ISR
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @param uint8_t const * const s : IN - pointer to the string to be transmitted
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_writeString(UART_t *const me, uint8_t const * const s);

/**
 * Write next char to the UART port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_TX_isrHandler(UART_t *const me);


/**
 * @brief Handles UART receive interrupt.
 * @param me Pointer to the UART instance.
 * @return Status code indicating success or failure.
 */
RC_t UART_RX_isrHandler(UART_t *const me);

/**
 * @brief Retrieves the JSON string from UART.
 * @param me Pointer to the UART instance.
 * @param jsonString Pointer to store the retrieved JSON string.
 * @return Status code indicating success or failure.
 */
RC_t UART_getJsonString(UART_t *const me, uint8_t *const jsonString);

/**
 * @brief Restarts the UART operation.
 * @return Status code indicating success or failure.
 */
RC_t UART_restartOperation();

/**
 * @brief Clears the UART instance.
 * @param me Pointer to the UART instance.
 * @return Status code indicating success or failure.
 */
RC_t UART_clear(UART_t *const me);


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
};
#endif /* Together */

#endif /* UART_H */
