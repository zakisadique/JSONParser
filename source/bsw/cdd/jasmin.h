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


 
#ifndef JASMIN_H
#define JASMIN_H
#include <stddef.h>

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
//####################### Defines/Macros

#ifdef JSMN_STATIC
#define JSMN_API static
#else
#define JSMN_API extern
#endif
//####################### Enumerations

/**
 * JSON type identifier. Basic types are:
 * 	o Object
 * 	o Array
 * 	o String
 * 	o Other primitive: number, boolean (true/false) or null
 */
typedef enum {
  JSMN_UNDEFINED = 0,
  JSMN_OBJECT = 1 << 0,
  JSMN_ARRAY = 1 << 1,
  JSMN_STRING = 1 << 2,
  JSMN_PRIMITIVE = 1 << 3
} jsmntype_t;

enum jsmnerr {
  /* Not enough tokens were provided */
  JSMN_ERROR_NOMEM = -1,
  /* Invalid character inside JSON string */
  JSMN_ERROR_INVAL = -2,
  /* The string is not a full JSON packet, more bytes expected */
  JSMN_ERROR_PART = -3
};

//####################### Structures
/**
 * JSON token description.
 * type		type (object, array, string etc.)
 * start	start position in JSON data string
 * end		end position in JSON data string
 */
typedef struct jsmntok {
  jsmntype_t type;
  int start;
  int end;
  int size;
#ifdef JSMN_PARENT_LINKS
  int parent;
#endif
} jsmntok_t;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string.
 */
typedef struct jsmn_parser {
  unsigned int pos;     /* offset in the JSON string */
  unsigned int toknext; /* next token to allocate */
  int toksuper;         /* superior token node, e.g. parent object or array */
} jsmn_parser;    


/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/
JSMN_API void jsmn_init(jsmn_parser *parser);
JSMN_API int jsmn_parse(jsmn_parser *parser, const char *js, const size_t len, jsmntok_t *tokens, 
    const unsigned int num_tokens);

#endif /* JASMIN_H */
