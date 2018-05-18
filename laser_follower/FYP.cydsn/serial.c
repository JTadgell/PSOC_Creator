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
#include "project.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
 
 int i;

 char buffer[UART_RXBUFFERSIZE];
 uint8 trigger;

void get_serial_speed(int *int1, int *int2){
    int counter=0;
    UART_ClearRxBuffer();
    while(counter<2){
        if ((0u != UART_ReadRxStatus())||(0u != UART_GetRxBufferSize()))
            {trigger=1;}
        if (0u != trigger)
        {
            CyDelay(10);
            strncpy(buffer, (const char *)UART_rxBuffer, UART_RXBUFFERSIZE);
            if (counter==0)
                {
                    
                    char str[100];
                    *int1=atoi(buffer);
                    //sprintf(str,"Recieved 1st [%i] \n",*int1);
                    //UART_PutString(str);
   
                    UART_ClearRxBuffer();
                    strncpy((char *)UART_rxBuffer,"",sizeof(UART_rxBuffer));
                    strncpy(buffer,"",sizeof(buffer));
                    
                }
             else if(counter==1)
                {
                    
                    char str[100];
                    *int2=atoi(buffer);
                    //sprintf(str,"Recieved 2nd [%i] \n",*int2);
                    //UART_PutString(str);
   
                    UART_ClearRxBuffer();
                    strncpy((char *)UART_rxBuffer,"",sizeof(UART_rxBuffer));
                    strncpy(buffer,"",sizeof(buffer));
                    
                }
                trigger=0;
                counter=counter+1;
        }

    }
}

void get_serial_control(double *int1, double *int2, double *int3){
    int counter=0;
    UART_ClearRxBuffer();
    while(counter<3){
        if ((0u != UART_ReadRxStatus())||(0u != UART_GetRxBufferSize()))
            {trigger=1;}
                if (0u != trigger)
                {
                    CyDelay(10);
                    strncpy(buffer, (const char *)UART_rxBuffer, UART_RXBUFFERSIZE);
                    if (counter==0)
                        {
                            
                            char str[100];
                            *int1=atof(buffer);
                            //sprintf(str,"Recieved 1st [%f] \n",*int1);
                            //UART_PutString(str);
           
                            UART_ClearRxBuffer();
                            strncpy((char *)UART_rxBuffer,"",sizeof(UART_rxBuffer));
                            strncpy(buffer,"",sizeof(buffer));
                            
                        }
                     else if(counter==1)
                        {
                            
                            char str[100];
                            *int2=atof(buffer);
                            //sprintf(str,"Recieved 2nd [%f] \n",*int2);
                            //UART_PutString(str);
           
                            UART_ClearRxBuffer();
                            strncpy((char *)UART_rxBuffer,"",sizeof(UART_rxBuffer));
                            strncpy(buffer,"",sizeof(buffer));
                            
                        }
                    else if(counter==2)
                        {
                            
                            char str[100];
                            *int3=atof(buffer);
                            //sprintf(str,"Recieved 3rd [%f] \n",*int3);
                            //UART_PutString(str);
           
                            UART_ClearRxBuffer();
                            strncpy((char *)UART_rxBuffer,"",sizeof(UART_rxBuffer));
                            strncpy(buffer,"",sizeof(buffer));
                            
                        }    
                        trigger=0;
                        counter=counter+1;
                }

    }
}

int get_serial_update(int *int1){
    int counter=0;
    UART_ClearRxBuffer();
    while(counter<1){
        if ((0u != UART_ReadRxStatus())||(0u != UART_GetRxBufferSize()))
            {trigger=1;}
                if (0u != trigger)
                {
                    CyDelay(10);
                    strncpy(buffer, (const char *)UART_rxBuffer, UART_RXBUFFERSIZE);
                    if (counter==0)
                        {
                            
                            char str[100];
                            *int1=atoi(buffer);
                            //sprintf(str,"Recieved 1st [%i] \n",*int1);
                            //UART_PutString(str);
           
                            UART_ClearRxBuffer();
                            strncpy((char *)UART_rxBuffer,"",sizeof(UART_rxBuffer));
                            strncpy(buffer,"",sizeof(buffer));
                            
                        }
                    
                        trigger=0;
                        counter=counter+1;
                }
    }
    return 0;
}