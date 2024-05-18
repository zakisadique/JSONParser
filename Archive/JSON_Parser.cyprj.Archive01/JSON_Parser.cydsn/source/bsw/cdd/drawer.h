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
**/


 
#ifndef DRAWER_H
#define DRAWER_H

#include "global.h"
#include "cfg.h"
#include "tft.h"
#include "ringBufferDrawing.h"
    #include "parser.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

    

    

//####################### Structures
/**
* \brief The rinbuffer structure contains all data elements representing a ringbuffer object
*
*/


struct sDrawer {
    RB_Draw_t m_buffer;
};
typedef struct sDrawer DRAWER_t;

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Uart
{
public:
#endif /* Together */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/
RC_t DRAWER_init(DRAWER_t *const me);
RC_t DRAWER_getDrawingInstructions(DRAWER_t *const me, PARSER_t *const parser);
RC_t DRAWER_convertToColor(DrawingInstr_t * const instruction, uint8_t* const data);
RC_t DRAWER_convertToCoordinate(DrawingInstr_t * const instruction, uint8_t* const data, uint8_t coordinateIndex, uint8_t numLines);
RC_t DRAWER_readInstruction(DRAWER_t *const me, DrawingInstr_t * const instruction);
RC_t DRAWER_drawOnTFT(DrawingInstr_t * const instruction);
RC_t DRAWER_sendMessage(const char* const message);

/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
};
#endif /* Together */

#endif /* DRAWER_H */
