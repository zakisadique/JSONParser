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
#include "string.h"
#include "parser.h"

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
RC_t PARSER_init(PARSER_t *const me){
    jsmn_init(&me -> parser);
    me -> nextTokenNum = 0;
    me -> jsonStringBuffer = NULL;
    me -> numTokens = 0;
    return RC_SUCCESS;
}

RC_t PARSER_setJsonString(PARSER_t *const me, uint8_t *jsonStringBuffer){
    PARSER_init(me);
    me -> jsonStringBuffer = jsonStringBuffer;
    return RC_SUCCESS;
}

RC_t PARSER_parseJSON(PARSER_t *const me){       
    me -> numTokens = jsmn_parse(&me -> parser, (const char *)me -> jsonStringBuffer, strlen((const char *) me -> jsonStringBuffer), me ->tokens, MAX_JSMN_TOKENS);
    if (me -> numTokens > 0 && me -> numTokens <= MAX_JSMN_TOKENS){
        return RC_SUCCESS;
    }
    return RC_ERROR;
}
RC_t PARSER_getToken(PARSER_t *const me, jsmntok_t *const token){
    if (me ->nextTokenNum <= me -> numTokens){
        *token = me ->tokens[me ->nextTokenNum++];
        return RC_SUCCESS;
    }    
    return RC_ERROR;
}