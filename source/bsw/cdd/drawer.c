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

#include "drawer.h"
#include "UART_LOG.h"

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

RC_t DRAWER_init(DRAWER_t *const me){
    TFT_init();
    DRAWER_sendMessage("TFT is ready.\n\nSend JSON packets viaUART");
    return RB_Draw_t_init(&me->m_buffer);
    
    
}
RC_t DRAWER_convertToColor(DrawingInstr_t * const instruction, uint8_t* const data){
    if (strcmp((char *)data, "red") == 0) {
        instruction ->color = RED;
    } else if (strcmp((char *)data, "green") == 0) {
        instruction ->color = GREEN;
    } else if (strcmp((char *)data, "blue") == 0) {
        instruction ->color = BLUE;
    }
    return RC_SUCCESS;
}

RC_t DRAWER_convertToCoordinate(DrawingInstr_t * const instruction, uint8_t* const data, uint8_t coordinateIndex, uint8_t numLines){
    
    uint16_t coordinate = 0;
    for (uint8_t i = 0; data[i] != '\0'; ++i){
        if (data[i] - '0' < 0 || data[i] - '0' >= 9){
            return RC_ERROR;
        }
        coordinate = coordinate * 10 + (data[i] - '0');
    }    
    instruction->lines[numLines].coordinates[coordinateIndex] = coordinate;
    return RC_SUCCESS;
}

RC_t DRAWER_getDrawingInstructions(DRAWER_t *const me, PARSER_t *const parser){
   
    uint8_t data[10];
    uint8_t index = 0;
    uint16_t coordinate = 0;
    uint8_t coordinateIndex = 0;
    uint8_t numLines = 0;
    jsmntok_t token;
    DrawingInstr_t instruction;

    while (PARSER_getToken(parser, &token) == RC_SUCCESS){

       if (token.size == 1){
            if (parser -> jsonStringBuffer [token.start] == 'c'){
                PARSER_getToken(parser, &token);
                for (uint16_t i = token.start; i < token.end; ++i){
                    data[index++] = parser -> jsonStringBuffer[i]; 
                }
                data[index] = '\0';
                index = 0;
                // convert data to color
                DRAWER_convertToColor(&instruction, data);
            }
            else if (parser -> jsonStringBuffer [token.start] == 'd'){
                PARSER_getToken(parser, &token);
                // get coordinates
                
                for (int i = 0; i < 4; ++i){
                    PARSER_getToken(parser, &token);

                    for (uint16_t i = token.start; i < token.end; ++i){
                        data[index++] = parser -> jsonStringBuffer[i];
                    }
                    data[index] = '\0';
                    index = 0;
                    // convert string to int
                    if (DRAWER_convertToCoordinate(&instruction, data, coordinateIndex, numLines) == RC_ERROR){
                        return RC_ERROR;
                    }
                    ++coordinateIndex;
                    //instruction.coordinates[coordinateIndex++] = 256;
                    
                }
                instruction.numLines = numLines++;
                coordinateIndex = 0;
            }
        }

   
    }
    RB_Draw_t_write(&me -> m_buffer, &instruction);

return RC_SUCCESS;
}

RC_t DRAWER_readInstruction(DRAWER_t *const me, DrawingInstr_t * const instruction){
    return RB_Draw_t_read (&me -> m_buffer, instruction);

}

RC_t DRAWER_drawOnTFT(DrawingInstr_t * const instruction){
    TFT_clearScreen();
    uint8_t numLines = instruction->numLines;
    TFT_color_t color = instruction->color;
    
    for (uint8_t i = 0; i <= numLines; ++i){          
        
        TFT_writeLine(instruction->lines[i].coordinates[0], instruction->lines[i].coordinates[1], instruction->lines[i].coordinates[2],
                    instruction->lines[i].coordinates[3], color);
    
    }
    UART_LOG_PutString("Drawn\n");
    return RC_SUCCESS;

}

RC_t DRAWER_sendMessage(const char* const message){
    TFT_clearScreen();
    TFT_print((char*)message);
    return RC_SUCCESS;
}
