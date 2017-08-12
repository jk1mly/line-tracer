//  ライントレーサ
//  東芝アマチュア無線クラブ
//      JA1YTS:Toshiba Amature Radio Station
//      JK1MLY:Hidekazu Inaba
//  

// Line tracer for PIC12F1501
//  (C)2017 JA1YTS,JK1MLY All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation and/or 
// other materials provided with the distribution.

#define _XTAL_FREQ        8000000
#define SPD0    16
#define SPD1    112
#define SPD2    208
#define SPD3    240
#define W_ADC   3
#define W_FULL  30
#define W_RUN   50
#define W_ADD   20
#define W_IDL   100
#define W_LED1  10
#define W_LED0  50
#define HD_0    0
#define HD_L    1
#define HD_R    2
#define LOS     4

#include <xc.h>
//#include <pic12f1501.h>         //Include header file

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin) 
//#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
//#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
//#pragma config FOSC = HS        // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR) 
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
//#pragma config IOSCFS = 4MHZ    // Internal Oscillator Frequency Select (4 MHz)
#pragma config BOREN = OFF       // Brown-out Reset Selection bits (BOR enabled)
//#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
//#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
//#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
//#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2 
//#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
//#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
//#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
//#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled) 
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// Pin2 PWM4(RA5) Right Motor
// Pin3 PWM3(RA4) Left Motor
// Pin7 ADC0(RA0) Right LED
// Pin6 ADC1(RA1) Center LED
// Pin5 ADC2(RA2) Left LED
// Pin4 RA0 Test Mode = Low

void LED_0(void){
    ADCON0 = 0b00111001;
    ANSELA = 0b00000110;
    TRISA  = 0b00001110;
    RA0 = 1;
}

void LED_1(void){
    ADCON0 = 0b00111001;
    ANSELA = 0b00000101;
    TRISA  = 0b00001101;
    RA1 = 1;
}

void LED_2(void){
    ADCON0 = 0b00111001;
    ANSELA = 0b00000011;
    TRISA  = 0b00001011;
    RA2 = 1;
}

void LED_02(void){
    ADCON0 = 0b00111101;
    ANSELA = 0b00000010;
    TRISA  = 0b00001010;
    RA0 = 1;
    RA2 = 1;
}

void LED_I(void){
    TRISA  = 0b00001111;
    ANSELA = 0b00000111;
    ADCON0 = 0b00111001;
    PORTA  = 0b00000000;
}

void Turn_R(void){
    PWM3DCH = 255 ;
    PWM4DCH = 0 ;
    __delay_ms(W_FULL);   
    PWM3DCH = SPD3 ;
    PWM4DCH = 0 ;
    LED_0();
    __delay_ms(W_ADD);  
}

void Turn_L(void){
    PWM3DCH = 0 ;
    PWM4DCH = 255 ;
    __delay_ms(W_FULL);   
    PWM3DCH = 0 ;
    PWM4DCH = SPD3 ;
    LED_2();
    __delay_ms(W_ADD);  
}

void Run_R(void){
    PWM3DCH = 255 ;
    PWM4DCH = 255 ;
    __delay_ms(W_FULL);   
    PWM3DCH = SPD2 ;
    PWM4DCH = SPD1 ;
}

void Run_L(void){
    PWM3DCH = 255 ;
    PWM4DCH = 255 ;
    __delay_ms(W_FULL);   
    PWM3DCH = SPD1 ;
    PWM4DCH = SPD2 ;
}

void Run_F(void){
    PWM3DCH = 255 ;
    PWM4DCH = 255 ;
    __delay_ms(W_FULL);   
    PWM3DCH = SPD3 ;
    PWM4DCH = SPD3 ;
    LED_1();
}

void Run_M(void){
    PWM3DCH = 255 ;
    PWM4DCH = 255 ;
    __delay_ms(W_FULL);   
    PWM3DCH = SPD2 ;
    PWM4DCH = SPD2 ;
    LED_1();
}

void Run_S(void){
    PWM3DCH = 255 ;
    PWM4DCH = 255 ;
    __delay_ms(W_FULL);   
    PWM3DCH = SPD1 ;
    PWM4DCH = SPD1 ;
    LED_1();
}

void S_Full(void){
    PWM3DCH = 255 ;
    PWM4DCH = 255 ;
}

void M_Idle(void){
    PWM3DCH = SPD0 ;
    PWM4DCH = SPD0 ;
}

void M_Stop(void){
    PWM3DCH = 0 ;
    PWM4DCH = 0 ;
}

void Init(void){
//ADC Setup
    TRISA  = 0b00001111;    //INPUT  1
    ANSELA = 0b00000111;    //ANALOG 1
    PORTA  = 0b00000000;
    ADCON0 = 0b00000001;
//    ADCON1 = 0b11000000;    //<0>:6bit + 2bit + 8bit OSC/4
    ADCON1 = 0b00010000;    //8bit + 2bit + <0>:6bit OSC/8
    ADCON2 = 0b00000000;

//PWM Setup
    PWM3CON = 0b11010000 ; // PWM3(EN OE OUT POL)
    PWM3DCH = 0 ;       
    PWM3DCL = 0 ;
    PWM4CON = 0b11010000 ; // PWM3(EN OE OUT POL)
    PWM4DCH = 0 ;       
    PWM4DCL = 0 ;
//    T2CON   = 0b00000010 ; // TMR2(0 Post=1:1 ON Pre=1/16)
    T2CON   = 0b00000001 ; // TMR2(0 Post=1:1 ON Pre=1/4)
    TMR2    = 0 ;          // TMR2 clear
    PR2     = 255 ;        // count
    TMR2ON  = 1 ;          // TMR2 start
}

// ---------------------------------------------------------

void main(void){

    unsigned int meml;
    unsigned int memr;
    unsigned int memc;
    unsigned int oldl = 4;
    unsigned int oldr = 4;
    unsigned int oldc = 4;
//    unsigned int oldd = 4;
//    unsigned int oldb = 4;    
    unsigned char hding = HD_0;    
    unsigned char spd_f = 1;    
    
//             76543210
    ANSELA = 0b00000000;    //ANALOG 1
    TRISA  = 0b00001000;    //INPUT  1
    PORTA  = 0b00110000;    //LEVEL
    OSCCON = 0b01110000;    //INT8M
    WPUA   = 0b00001000;    //PullUp 1
    nWPUEN = 0;
//  INTCON = 0b00000000;
// Wait
    __delay_ms(100);
   
//  LED check RA0,1,2
    for(int i = 0; i< 10; i++){
        PORTA  = 0b00110111;
        __delay_ms(W_LED1);
        PORTA  = 0b00110000;
        __delay_ms(W_LED0);
    }   

    Init();    
// ---------------------------------------------------------
    
// Test Mode Pin4 connect to GND
    while((RA3 & 0x01) == 0){

/*
//LED DETECT
        ADCON0 = 0b01111001;
        ANSELA = 0b00000101;    //ANALOG 1
        TRISA  = 0b00001101;    //INPUT  1
        PORTA  = 0b00110000;

        RA1 = 1;
        __delay_ms(5000);
        RA1 = 0;
        __delay_ms(5000);
        
        ANSELA = 0b00000010;    //ANALOG 1
        TRISA  = 0b00001010;    //INPUT  1
        PORTA  = 0b00110000;

        RA0 = 1;
        RA2 = 1;
        __delay_ms(5000);
        RA0 = 0;
        RA2 = 0;
        __delay_ms(5000);
*/        

/*        
//Motor1
        ADCON0 = 0b01111001;
        ANSELA = 0b00000111;    //ANALOG 1
        TRISA  = 0b00001111;    //INPUT  1
        PORTA  = 0b00110000;
//  Left MOTOR check RA4
        RA4 = 0;
        __delay_ms(1000);
        RA4 = 1;
        __delay_ms(1000);

//  Right MOTOR check RA5
        RA5 = 0;
        __delay_ms(1000);
        RA5 = 1;
        __delay_ms(1000);
*/

/*
//Motor2
        TRISA  = 0b00001101;    //INPUT  1
        ANSELA = 0b00000101;    //ANALOG 1
        PORTA  = 0b00000010;
//        RA1 = 1;
//        RA4 = 0;
//        RA5 = 0;
        __delay_ms(100);
        RA1 = 0;
        __delay_ms(500);
        RA1 = 1;
        __delay_ms(100);
        RA1 = 0;
        __delay_ms(5000);
        RA1 = 1;
        __delay_ms(100);
        PORTA  = 0b00110000;
//        RA1 = 0;
//        RA4 = 1;
//        RA5 = 1;
        __delay_ms(5000);
*/

/*
// PWM
        PWM3CON = 0b11010000 ; // PWM3(EN OE OUT POL)
        PWM3DCH = SPD1 ;       
        PWM3DCL = 0 ;
        PWM4CON = 0b11010000 ; // PWM3(EN OE OUT POL)
        PWM4DCH = SPD1 ;       
        PWM4DCL = 0 ;
        T2CON   = 0b00000010 ; // TMR2(0 Post=1:1 ON Pre=1/16)
        TMR2    = 0 ;          // TMR2 clear
        PR2     = 255 ;        // count
        TMR2ON  = 1 ;          // TMR2 start
        __delay_ms(5000);
        PWM3CON = 0b00000000 ; // PWM3(EN OE OUT POL)
        PWM4CON = 0b00000000 ; // PWM3(EN OE OUT POL)
*/

//Simple
        LED_1();
        __delay_ms(W_LED1);
        ADCON0 = 0b00000001;
        __delay_ms(W_ADC);

        GO_nDONE = 1;
        while(GO_nDONE) ;

        memr = (ADRESH << 8) | ADRESL;
      
        ADCON0 = 0b00001001;
        __delay_ms(W_ADC);

        GO_nDONE = 1;
        while(GO_nDONE) ;

        meml = (ADRESH << 8) | ADRESL;

        LED_I();

        if(meml > memr){
//            Run_R();
            Turn_R();
        } else {
//            Run_L();
            Turn_L();
        }
        __delay_ms(W_RUN);
        __delay_ms(W_RUN);

        M_Idle();
        __delay_ms(W_IDL);
        
    }

// ---------------------------------------------------------

    Init();

//Stop / Run
    M_Idle();
    __delay_ms(500);
    Run_S();
    __delay_ms(100);
    M_Stop();

// ---------------------------------------------------------

    while(1){
//  Speed Up
        if((RA3 & 0x01) == 0) {
            spd_f = 1;
        } else {
            spd_f = 0;
        }
//  Start
        PORTA  = 0b00000000;
        M_Stop();
        __delay_ms(W_ADC);    

//  CH1 Center (RA1=AN1)
        LED_02();
        __delay_ms(W_LED1);
        ADCON0 = 0b00000101;
        __delay_ms(W_ADC);

        GO_nDONE = 1;
        while(GO_nDONE) ;

        memc = (ADRESH << 8) | ADRESL;
                
//  CH0 Right (RA0=AN0)
        LED_1();
        __delay_ms(W_LED1);
        ADCON0 = 0b00000001;
        __delay_ms(W_ADC);

        GO_nDONE = 1;
        while(GO_nDONE) ;

        memr = (ADRESH << 8) | ADRESL;
      
//  CH2 Left (RA2=AN2)
        ADCON0 = 0b00001001;
        __delay_ms(W_ADC);

        GO_nDONE = 1;
        while(GO_nDONE) ;

        meml = (ADRESH << 8) | ADRESL;

// ---------------------------------------------------------
        
//Loop Start
//        M_Idle();

//        LED_1();
//        __delay_ms(W_LED1);
//        RA1 = 0;
//        __delay_ms(W_LED0);
//        RA1 = 1;
//        __delay_ms(W_LED1);
        LED_I();
//        __delay_ms(W_LED0);

//Main Control
//Center
        if((meml > memc) && (memr > memc)){
            Run_M();
            hding = HD_0;

//Turn Right
        } else if((meml > memc) && (meml > memr)){
            Turn_R();
//            Run_R();
            hding = HD_R;
//Turn Left
        } else if((memr > memc) && (memr > meml)){
            Turn_L();
//            Run_L();
            hding = HD_L;

//Turn Left
        } else if((meml < memc) && (meml < memr)){
            Turn_L();
            hding = HD_L;
//Turn Right
        } else if((memr < memc) && (memr < meml)){
            Turn_R();
            hding = HD_R;

//Turn Right
        } else if((memr < oldr) && (memr < meml)){
            Turn_R();
            hding = HD_R;
//Turn Left
        } else if((meml < oldl) && (meml < memr)){
            Turn_L();
            hding = HD_L;

//Turn Right
        } else if((memc > oldc) && (meml > memr)){
            Turn_R();
            hding = HD_R;
//Turn Left
        } else if((memc > oldc) && (memr > meml)){
            Turn_L();
            hding = HD_L;

//Turn Right
        } else if((memr < oldr) && (memr < memc)){
            Turn_R();
            hding = HD_R;
//Turn Left
        } else if((meml < oldl) && (meml < memc)){
            Turn_L();
            hding = HD_L;

//Maybe Center
        } else if((memc < oldc) && (memc < meml)){
            Run_S();
            hding = HD_0;
        } else if((memc < oldc) && (memc < memr)){
            Run_S();
            hding = HD_0;
            
//Keep
        } else if(hding == HD_0){
            M_Idle();
            LED_02();
            __delay_ms(W_LED1);
            Run_S();
        } else if(hding == HD_R){
            M_Idle();
            LED_02();
            __delay_ms(W_LED1);
            Turn_R();
        } else if(hding == HD_L){
            M_Idle();
            LED_02();
            __delay_ms(W_LED1);
            Turn_L();

//Others
        } else {
            Run_F();
            LED_02();
            __delay_ms(W_LED1);
            LED_1();
            M_Idle();
        }
        __delay_ms(W_RUN);
        if(spd_f == 1){
            __delay_ms(W_RUN);
        }
        LED_I();
        
// Idle
        M_Stop();
//        M_Idle();
        __delay_ms(W_IDL);


// ---------------------------------------------------------
    
/*
// Dark
        oldd++;
        if(oldd > memr){
            oldd = memr;
        }
        if(oldd > meml){
            oldd = meml;
        }
        if(oldd > memc){
            oldd = memc;
        }

// Bright
        oldb--;
        if(memr > oldb){
            oldb = memr;
        }
        if(meml > oldb){
            oldb = meml;
        }
        if(memc > oldb){
            oldb = memc;
        }
*/
        oldr = memr;
        oldl = meml;
        oldc = memc;

    }
}

