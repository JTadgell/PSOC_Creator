// include directives
#include "project.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

extern void forward();
extern void stop();
extern void drive();
extern void turn_wheel();
extern void turn();
extern void straight();
extern void turn();
extern void Check_Speed();
extern void Print_Values();
extern void new_path();
extern int get_serial_update();
extern int get_serial_update2();
extern void get_serial_speed();
extern void get_serial_control();
extern void test_values();
extern void step_response();
extern void update_angle();

char mystring[50];

//turn on all components
void Setup(){
    
    PWM_M1_Start();
    PWM_M2_Start();
    UART_Start();
    M1Clock_Start();
    MClock_Start();
    
    M1QuadDec_Start();
    M1QuadDec_Enable();
    CyDelay(1000);
    M1QuadDec_SetCounter(0);

    CyDelay(1000);
    
    M2QuadDec_Start();
    M2QuadDec_Enable();
    CyDelay(1000);
    M2QuadDec_SetCounter(0);
    
    Timer_1_Start();
    isr_1ms_Enable();
   
}

void Stop(){
PWM_M1_Stop();
    PWM_M2_Stop();}
CY_ISR( Timer_1_Handler ){
    
    Check_Speed(30);
    Timer_1_ReadStatusRegister();
    //Print_Values();
    
    
}

int main(void){
    
    CyGlobalIntEnable;
    
    Setup();
    char str[50];

    isr_1ms_StartEx( Timer_1_Handler );
    int counter = 0; 
    Timer_1_WritePeriod(12000); //CHANGE THIS BACK TO 12000
    int trigger1=0;
    int int1=0;
    int int2=0;
    int int3=0;
    int update;
    double int11;
    double int22;
    double int33;
    long int angle;
    int i;
     /*  
    for(;;){ 
    
    get_serial_update(&update);
    
    if(update==0){      
        UART_PutString("----- Reset -----\n"); 
        CySoftwareReset();
        
    }
    else if (update==2){
        UART_PutString("----- Speed -----\n"); 
        get_serial_speed(&int1, &int2);
        new_path(int1,int2);
        do {                
            Print_Values();
            if((0u != UART_ReadRxStatus())||(0u != UART_GetRxBufferSize())){trigger1=1;}
        } while(trigger1==0);
    
    }
    else if (update==1){
        UART_PutString("----- Update  -----\n"); 
        get_serial_control(&int11,&int22,&int33);
        test_values(int11,int22,int33); 
    } 
    else if (update==3){
        
        UART_PutString("----- Distance -----\n"); 
        get_serial_speed(&int111, &int222);
        step_response(int111,int222);
        
        do {                
            Print_Values();
            if((0u != UART_ReadRxStatus())||(0u != UART_GetRxBufferSize())){trigger1=1;}
        } while(trigger1==0);
    
    }
    trigger1=0;
    
    
    }
    */
    
    
    for(;;){
        get_serial_update(&update);
        
        if(update==0){      
            UART_PutString("----- Reset -----\n"); 
            CySoftwareReset();
            
        }
        // update the base speed of the robot
        else if (update==2){
            UART_PutString("----- Speed -----\n"); 
            get_serial_speed(&int1, &int2);
            new_path(int1,int2);
        }

        // update a 1 time increment
        else if (update==3){
            UART_PutString("----- Angle -----\n"); 
            get_serial_update2(&angle);
            update_angle(angle);
        
            do {                
                Print_Values();
                if((0u != UART_ReadRxStatus())||(0u != UART_GetRxBufferSize())){trigger1=1;}
            } while(trigger1==0);
    
        }



        trigger1=0;
    }
    
    
}

/* [] END OF FILE */
