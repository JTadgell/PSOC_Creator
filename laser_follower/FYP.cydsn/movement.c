// include directives

// RIGHT WHEEL IS MOTOR 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// speed is a value between 0 and 65535
#include "project.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
    
char mystring[50];


/* declare global variables */


    long int cur_dest_left = 0;
    long int cur_dest_right = 0;  
    long int prev_dest_right;
    long int prev_dest_left;
    
    long int cur_pos_left;  
    long int cur_pos_right;
    long int last_pos_right;
    long int last_pos_left;

    int volt_motor_left;
    int volt_motor_right;

    int adj_motor_left;
    int adj_motor_right;

    int error_left;
    int error_right;

    int error_left_prev;
    int error_right_prev;

    int error_left_sum;
    int error_right_sum;

    long int distance_left;
    long int distance_right;

    double Kp=100;
    double Ki=0.1;
    double Kd=1000;

    int speed_left;
    int speed_right;

    int inc_left;
    int inc_right;

    long int time_ms;
    long int time_ms_start;


    

void turn_wheel(char side, int volt){
    // turning right wheel
    if (side == 'r'){
        Standby_Write(1);
        PWM_M2_WriteCompare(abs(volt));
        
        if (volt > 0)
        {
            M2_FWD_Write(0);
            M2_BWD_Write(1);
        }
        else if (volt < 0)
        {
            M2_FWD_Write(1);
            M2_BWD_Write(0);
        }
        else
        {
            M2_FWD_Write(0);
            M2_BWD_Write(0);
        }
    }
    
    //turning left wheel
    if (side == 'l'){
        Standby_Write(1);
        PWM_M1_WriteCompare(abs(volt));
        
        if (volt > 0)
        {
            M1_FWD_Write(0);
            M1_BWD_Write(1);
        }
        else if (volt < 0)
        {
            M1_FWD_Write(1);
            M1_BWD_Write(0);
        }
        else
        {
            M1_FWD_Write(0);
            M1_BWD_Write(0);
        }
    }
}
void update_angle(angle){

    distance_left = 1/2 * angle;
    distance_right = -1/2 * angle; 

}

void step_response(long int left_dest, long int right_dest){
    
     time_ms_start = time_ms; 
    
     cur_dest_left = left_dest;   
     cur_dest_right = right_dest;
        
     inc_left = 0;
     inc_right = 0;
    
}
/*
void Get_StartSpeed(){
    speed_left = 10*(cur_dest_left - prev_dest_left);
    speed_right = 10*(cur_dest_right - prev_dest_left);
}
  
*/
void test_values(double kp, double kd, double ki)
{   Kp=kp;
    Kd=kd;
    Ki=ki;
}
void new_path(int incleft, int incright){
    
    
    inc_left = incleft + distance_left;
    inc_right = incright + distance_right;
    
    distance_left = 0;
    distance_right = 0;
    
    
    /*
    
    int speed = 30;
    inc_left = speed;
    inc_right = speed;
    
    if (cur_dest_right < fin_dest_right){
        direction_right = 1;}
    else{
        direction_right = -1;}
    
    if (cur_dest_left < fin_dest_left){
        direction_left = 1;}
    else{
        direction_left = -1;}
    
    iterations_left = fin_dest_left - cur_dest_left;
    iterations_count_left = 0;
    
    iterations_right = fin_dest_right - cur_dest_right;
    iterations_count_right = 0;
    
    */
    
}



void Get_Destination(){
    
    cur_dest_left = cur_dest_left + inc_left;
    cur_dest_right = cur_dest_right + inc_right;
}
void Get_Position(){
    cur_pos_right = -64*M2QuadDec_GetCounter();
    cur_pos_left = -64*M1QuadDec_GetCounter();
}
void Get_Error(){
    error_left_prev = error_left;
    error_right_prev = error_right;
    
    error_left = cur_dest_left - cur_pos_left;
    error_right = cur_dest_right - cur_pos_right;
    
    error_left_sum = error_left_sum + error_left;
    error_right_sum = error_right_sum + error_right;

}

void Get_PID(){   
    volt_motor_left =  ( Kp * error_left ) + ( Ki * error_left_sum ) + ( Kd * (error_left - error_left_prev) );
    //volt_motor_left =  adj_motor_left;
    
        if (volt_motor_left < -65535){
            volt_motor_left = -65535;}
        else if (volt_motor_left > 65535){
            volt_motor_left = 65535;}
    
    volt_motor_right = ( Kp * error_right ) + ( Ki * error_right_sum ) + ( Kd * (error_right - error_right_prev ));
    //volt_motor_right =  adj_motor_right;
    
        if (volt_motor_right < -65535){
            volt_motor_right = -65535;}
        else if (volt_motor_right > 65535){
            volt_motor_right = 65535;}
}    
void Adj_Volt(){
    
    turn_wheel('l', volt_motor_left);
    turn_wheel('r', volt_motor_right);
}

void Check_Speed(){
    time_ms = time_ms + 1;
    Get_Destination();  // update the destination
    Get_Position();     // update the position
    Get_Error();        // update the current and previous errors
    Get_PID();          // calculate the current voltages required
    Adj_Volt();      // update the speed of the wheVels
    
}

void Print_Values(){
    sprintf(mystring, "%d|%d|%ld|%ld|%ld|%d|%d|%d\n", error_left, volt_motor_left, cur_pos_left, cur_dest_left, time_ms-time_ms_start,error_left,(error_left-error_left_prev), (error_left_sum));
    UART_PutString(mystring);
    
    /*
    sprintf(mystring, "left error:%d     right error: %d\n", error_left, error_right);
    UART_PutString(mystring);
    sprintf(mystring, "left voltage:%d     right voltage: %d\n", volt_motor_left, volt_motor_right);
    UART_PutString(mystring);
    sprintf(mystring, "left position:%ld     right position: %ld\n", cur_pos_left, cur_pos_right);
    UART_PutString(mystring);
    sprintf(mystring, "left destination:%ld     right destination: %ld\n", cur_dest_left, cur_dest_right);
    UART_PutString(mystring);
    */
}




/* [] END OF FILE */
