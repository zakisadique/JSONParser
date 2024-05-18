/**
* \file uart.c
* \author P. Fromm
* \date 8.12.19
*
* \brief UART wrapper
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <string.h>

#include "uart.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Init a Uart Port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or error code
 */
RC_t UART_init(UART_t *const me)
{
    RB_init(&me->m_rxBuffer);
    RB_init(&me->m_txBuffer);
    me -> countISR = 0;
    
    UART_start();
    UART_putString("UART is ready to receive JSON packets\n");

    return RC_SUCCESS;
}

RC_t UART_clear(UART_t *const me){
    RB_clear(&me->m_rxBuffer);
    RB_clear(&me->m_txBuffer);
    
    return RC_SUCCESS;

}

RC_t UART_restartOperation(){
    UART_LOG_Stop();
    UART_start();

}

/**
 * Write a string to the UART, Using Ringbuffer and ISR
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @param uint8_t const * const s : IN - pointer to the string to be transmitted
 * @return <return description>
 */
RC_t UART_writeString(UART_t *const me, uint8_t const * const s)
{
    //Write data into ringbuffer
    uint16_t len = strlen(s);
    uint16_t capacity = RB_getCapacity(&me->m_txBuffer);
    
    if (len < capacity)
    {
        for (uint16_t i = 0; i < len; i++)
        {
            RB_write(&me->m_txBuffer, &s[i]);
        }
    
        //Initiate transfer
        //Can be optimized in terms of speed
        uint8_t firstElement = 0;
        RB_read(&me->m_txBuffer, &firstElement);
        
        //Send to driver
        //Rest will be transmitted by TX_isr;
        UART_writeByte(firstElement);
    }
    else
    {
        return RC_ERROR_MEMORY;
    }
    
    return RC_SUCCESS;
}

/**
 * Write next char to the UART port
 * @param UART_t * const me : IN/OUT - pointer to uart port object 
 * @return RC_SUCCESS or errorcode
 */
RC_t UART_TX_isrHandler(UART_t *const me)
{
    
    if (RB_getNumberOfStoredElements(&me->m_txBuffer))
    {
        uint8_t nextElement = 0;
        RB_read(&me->m_txBuffer, &nextElement);
        
        //Send to driver
        UART_writeByte(nextElement);
        
        return RC_SUCCESS;
    }
    else
    {
        //do nothing, transfer ended
        return RC_ERROR_BUFFER_EMTPY;
    }
    
}



RC_t UART_RX_isrHandler(UART_t *const me){
    uint8_t receivedByte = UART_readByte();
    
    
    RC_t result = RC_ERROR;
    result =  RB_write(&me->m_rxBuffer, &receivedByte);
    if (result == RC_SUCCESS && receivedByte == UART_Terminator){
        result = RC_TRIGGER;
    }
    me -> countISR++;
    return result;
}

RC_t UART_getJsonString(UART_t * const me, uint8_t * const jsonString){
#if 0
    if (me == NULL || jsonString == NULL){
        return RC_ERROR_NULL;
    }
    
    if (RB_getNumberOfStoredElements(&me->m_rxBuffer) == 0) {
        return RC_ERROR_BUFFER_EMTPY;
    }
#endif
for (uint8_t i = 0; i > MAX_JSON_STRING_LENGTH; ++i){

    jsonString[i] = '\0';
}


    char receivedChar;
    int index = 0;
    uint8_t data;
    while (1) {
        RC_t result = RB_read(&me->m_rxBuffer, &data);

        if (result == RC_SUCCESS) {
            receivedChar = data;
            jsonString[index++] = receivedChar;
      
            if (receivedChar == UART_Terminator) {
                jsonString[index] = '\0';
                //UART_LOG_PutString("UART_getString");
                //UART_LOG_PutString((const char8 *)jsonString); // debug
                //UART_LOG_PutString("\n");
                return RC_SUCCESS;
            }

            if (index >= MAX_JSON_STRING_LENGTH - 1) {
                return RC_ERROR_READ_FAILS;
                break;
            }
        } else {
             return RC_ERROR_READ_FAILS;
            //break;
        }
    }
}
