/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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
#include <stdlib.h>
#include "ringBufferDrawing.h"

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
 * Initialisation of a ringbuffer
 * @param RB_Draw_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return RC_SUCCESS or error code
 */
RC_t RB_Draw_t_init(RB_Draw_t * const me)
{
    return RB_Draw_t_clear(me);
}

/**
 * Clearing of a ringbuffer
 * @param RB_Draw_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return RC_SUCCESS or error code
 */
RC_t RB_Draw_t_clear(RB_Draw_t * const me)
{
    if (0 == me) return RC_ERROR_BAD_PARAM;
    
    me->m_fillLevel = 0;
    me->m_readIndex = 0;
    me->m_writeIndex = 0;
    
    for (uint16_t i = 0; i < RB_DRAWING_SIZE; i++)
    {
        me->m_data[i].color = WHITE;
        me->m_data[i].numLines = 0;
        me->m_data[i].lines->coordinates[0] = 0;
        me->m_data[i].lines->coordinates[1] = 0;
        me->m_data[i].lines->coordinates[2] = 0;
        me->m_data[i].lines->coordinates[3] = 0;

    }
    
    return RC_SUCCESS;
}
    

/**
 * Write one element to the ringbuffer
 * @param RB_Draw_t * const me : IN/OUT - pointer to ringbuffer object 
 * @param RB_data_t const * const data : IN - Data to be written
 * @return RC_SUCCESS or error code
 */
RC_t RB_Draw_t_write(RB_Draw_t * const me, RB_Draw_data_t const * const data)
{
    if (me->m_fillLevel < RB_DRAWING_SIZE)
    {
        me->m_data[me->m_writeIndex++] = *data;
        
        me->m_writeIndex %= RB_DRAWING_SIZE;
        me->m_fillLevel++;
        
        return RC_SUCCESS;
    }
    else
    {
        return RC_ERROR_BUFFER_FULL;
    }
}

/**
 * Read one element from the ringbuffer
 * @param RB_Draw_t * const me : IN/OUT - pointer to ringbuffer object 
 * @param RB_data_t * const data : OUT - Data read
 * @return RC_SUCCESS or error code
 */
RC_t RB_Draw_t_read(RB_Draw_t * const me, RB_Draw_data_t * const data)
{
    if (me->m_fillLevel > 0)
    {
        *data = me->m_data[me->m_readIndex++];
        
        me->m_readIndex %= RB_DRAWING_SIZE;
        me->m_fillLevel--;
        
        return RC_SUCCESS;
    }
    else
    {
        return RC_ERROR_BUFFER_EMTPY;
    }
}

/**
 * Provide available space in buffer
 * @param RB_Draw_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return Available number of elements to be stored
 */
uint16_t RB_Draw_t_getCapacity(RB_Draw_t * const me)
{
    //Todo: No  error handling considered, assume all other functions work as intended
    return RB_DRAWING_SIZE - me->m_fillLevel;
}

/**
 * Check how much data is stored
 * @param RB_Draw_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return number of byte stored
 */
uint16_t RB_Draw_t_getNumberOfStoredElements(RB_Draw_t * const me)
{
    return me->m_fillLevel;
}
