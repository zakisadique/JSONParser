/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "global.h"
#include "project.h"
#include "cfg.h"
#include "uart.h"
#include "events.h"
#include "parser.h"
#include "drawer.h"

UART_t UART_port;
EVENT_t parsingEventHandler;
EVENT_t drawingEventHandler;
PARSER_t jsonParser;
DRAWER_t drawer;


uint8_t string [20];
uint8_t i = 0;
/********************************************************************************
 * Systick
 ********************************************************************************/

/*
* ISR which will increment the systick counter every ms
*/
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    //Set systick period to 1 ms. Enable the INT and start it.
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
    EE_systick_enable_int();



    for(;;)
    {
        StartOS(OSDEFAULTAPPMODE);

    }
}

TASK(tsk_auto){
    
    /* Initialise Reaction Game and Arcadian */

    UART_init(&UART_port);
    EVENT_init(&parsingEventHandler);
    EVENT_init(&drawingEventHandler);
    PARSER_init(&jsonParser);
    DRAWER_init (&drawer);
        
        
    /* Reconfigure ISRs with OS parameters.
     * This line MUST be called after the hardware driver initialization!
     */
    EE_system_init();
    
    /* Must be started after interrupt reconfiguration */
    EE_systick_start();
    
    /* Activate tasks*/
    ActivateTask(tsk_handleEvents);
    ActivateTask(tsk_background);
    
    /* Terminate this task after initialization */
    TerminateTask();
}

TASK(tsk_background){
    
    while (1){
    
    }
    TerminateTask();
}

TASK(tsk_handleEvents){
    
    EventMaskType ev = 0;
    uint8_t jsonStringBuffer[MAX_JSON_STRING_LENGTH];
    
    while (1){
        WaitEvent(ev_centralEvent);
        GetEvent(tsk_handleEvents, &ev);
        ClearEvent(ev); 
   
        if (ev & ev_centralEvent){
            eEvent_t event;
            /* Read events from the buffer for parsing JSON. */  
            if (EVENT_read(&parsingEventHandler, &event) == RC_SUCCESS){
                if (event == ev_parseJSON){

                    /* CRITICAL SECTION:
                    * Reads data from the buffer that stores elements received on UART.
                    * Resourse is occupied because reading takes place in multiple clock cycles;
                    * if new data is received on UART while the buffer is being read,
                    * handling the UART interrupt before read action is completed may curropt the metadata of the buffer
                    */  
                    GetResource(res_buffer);
                    RC_t result = UART_getJsonString(&UART_port, jsonStringBuffer);
                    ReleaseResource(res_buffer);
                    
                    if (result == RC_SUCCESS){   
                        /* Parse the JSON string and trigger the event that draws on TFT display */  
                        PARSER_setJsonString(&jsonParser, jsonStringBuffer);
                        if (PARSER_parseJSON(&jsonParser) == RC_SUCCESS){
                            if (DRAWER_getDrawingInstructions(&drawer, &jsonParser)== RC_SUCCESS){
                                EVENT_add(&drawingEventHandler, ev_drawOnTFT);
                                SetEvent(tsk_handleEvents, ev_centralEvent);
                            } else {
                                DRAWER_sendMessage("Invalid coordinates\n");
                                SetEvent(tsk_handleEvents, ev_centralEvent);
                            }
                        } else {
                        UART_putString("Invalid JSON packet\n"); 
                        SetEvent(tsk_handleEvents, ev_centralEvent);
                        } 
                    }
                    
                } else if (event == ev_uartError){
                    /* Handle error in case of buffer overflow */  
                    while (1){
                        EVENT_read(&parsingEventHandler, &event);
                        /* After buffer overflow is encountered, buffer is reset.
                        * The next terminating character belongs to the lost JSON, so when 
                        * ev_parseJSON event is triggered, it needs to be ignored.
                        */  
                        if (event == ev_parseJSON){
                            UART_clear(&UART_port);
                            break;
                        }
                        
                    }
                    UART_putString("JSON size exceeded\n");
                    SetEvent(tsk_handleEvents, ev_centralEvent);
                }
            }
            else {
                /* Read events from the buffer for drawing on TFT. */
                if (EVENT_read(&drawingEventHandler, &event) == RC_SUCCESS){
                    if (event == ev_drawOnTFT){
                        DrawingInstr_t instr;
                        
                        /* CRITICAL SECTION:
                        * Reads data from the buffer that stores drawing instructions
                        * Resourse is occupied because reading takes place in multiple clock cycles;
                        * if new instruction is ready to be written to the buffer while the read operation is being carried out,
                        * executing the write operation before reading is completed may curropt the metadata of the buffer.
                        */ 
                        GetResource(res_drawingBuffer);
                        RC_t result = DRAWER_readInstruction(&drawer, &instr);
                        ReleaseResource(res_drawingBuffer);
                        
                        if (result == RC_SUCCESS){
                            DRAWER_drawOnTFT(&instr);
                            SetEvent(tsk_handleEvents, ev_centralEvent);
                        } else {
                            DRAWER_sendMessage("Unexpected error\ncall for HELP\n");
                            SetEvent(tsk_handleEvents, ev_centralEvent);
                        }
                    }
                }
            }            
        }            
    }

     TerminateTask();
}


ISR2(isr_UART_RX){
#if 0
    RC_t result = RC_ERROR_UNKNOWN;
    result = UART_RX_isrHandler(&UART_port);

    if (result == RC_TRIGGER){
        EVENT_add(&parsingEventHandler, ev_parseJSON);
        SetEvent(tsk_handleEvents, ev_centralEvent);
    }
    else if (result == RC_ERROR_BUFFER_FULL){
        UART_clear(&UART_port);
        EVENT_add(&parsingEventHandler, ev_uartError);
        SetEvent(tsk_handleEvents, ev_centralEvent);
        
    } else {}
#endif

    uint8_t receivedByte = UART_readByte();
    

    string [i] = receivedByte;
    i++;
    
    //UART_LOG_PutChar(receivedByte);
  
}

/* [] END OF FILE */
