/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* detailed description what the file does
*
* \note <notes>
* Programming rules (may be deleted in the final release of the file)
* ===================================================================
*
* 1. Naming conventions:
*    - Prefix of your module in front of every function and static data. 
*    - Scope _ for public and __ for private functions / data / types, e.g. 
*       Public:  void CONTROL_straightPark_Init();
*       Private: static void CONTROL__calcDistance();
*       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
*    - Own type definitions e.g. for structs or enums get a postfix _t
*    - #define's and enums are written in CAPITAL letters
* 2. Code structure
*    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
*    - Prepare your design before starting to code
*    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
*    - Avoid magic numbers, use enums and #define's instead
*    - Make sure, that all error conditions are properly handled
*    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
*	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
* 3. Data conventions
*    - Minimize the scope of data (and functions)
*    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
*    - All static objects have to be placed in a valid linker sections
*    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
*    - Do not mix signed and unsigned data in the same operation
* 4. Documentation
*    - Use self explaining function and variable names
*    - Use proper indentation
*    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
*    		- Every  File has to be documented in the header
*			- Every function parameter and return value must be documented, the valid range needs to be specified
*     		- Logical code blocks in the C-File must be commented
*    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html 
* 5. Qualification
*    - Perform and document design and code reviews for every module
*    - Provide test specifications for every module (focus on error conditions)
*
* Further information:
*    - Check the programming rules defined in the MIMIR project guide
*         - Code structure: https://mimir.h-da.io/public/methods/eng_codestructure/method.htm
*         - MISRA for C: https://mimir.h-da.io/public/methods/eng_c_rules/method.htm
*         - MISRA for C++: https://mimir.h-da.io/public/methods/eng_cpp_rules/method.htm
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
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


 
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "global.h"
#include "cfg.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
*
* If needed, a more detailed description can be given below */
#define RB_SIZE 200
typedef uint8_t RB_data_t;
//####################### Enumerations
/**
* \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explaination of the enumeration.
*/

//####################### Structures
/**
* \brief The purpose as well as the members of a structure have to be documented.
*
* Make clear what the structure is used for and what is the purpose of the members.
*/
typedef struct {
    RB_data_t   m_data[RB_SIZE];
    uint16_t    m_readIndex;
    uint16_t    m_writeIndex;
    uint16_t    m_fillLevel;
} RB_t;


// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class FILE
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/



/**
 * Initialisation of a ringbuffer
 * @param RB_t  * const me : IN/OUT - pointer to ringbuffer object 
 * @return RC_SUCCESS or error code
 */
RC_t RB_init(RB_t * const me);

/**
 * Clearing of a ringbuffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return RC_SUCCESS or error code
 */
RC_t RB_clear(RB_t * const me);

/**
 * Write one element to the ringbuffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @param RB_data_t const * const data : IN - Data to be written
 * @return RC_SUCCESS or error code
 */
RC_t RB_write(RB_t * const me, RB_data_t const * const data);

/**
 * Read one element from the ringbuffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @param RB_data_t * const data : OUT - Data read
 * @return RC_SUCCESS or error code
 */
RC_t RB_read(RB_t * const me, RB_data_t * const data);

/**
 * Provide available space in buffer
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return Available number of elements to be stored
 */
uint16_t RB_getCapacity(RB_t * const me);

/**
 * Check how much data is stored
 * @param RB_t * const me : IN/OUT - pointer to ringbuffer object 
 * @return number of byte stored
 */
uint16_t RB_getNumberOfStoredElements(RB_t * const me);

/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
//Not visible for compiler, only used for document generation
private:


};
#endif /* Together */

#endif /* RINGBUFFER_H */
