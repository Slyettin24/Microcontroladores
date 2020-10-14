/*
 * File:   LAB_4.c
 * Author: FLIA
 *
 * Created on 24 de septiembre de 2020, 06:00 PM
 */


#include <xc.h>
#define _XTAL_FREQ 100000
#include "pic18f4550.h"
int af,x,y,z,d;
int ciclo_util=78;
void PORT_INIT(void);
void AFORO(void);
void TIMER0_INITAF(void);
void TIMER1_INITAF(void);
void PWM_50_80(void);
void main(void) {
    PORT_INIT();
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    PWM_50_80();
    TIMER0_INITAF();
    TIMER1_INITAF();
    TMR0L=0x00;
    TMR1L=0x00;
    while(1){
        AFORO();
        if(PORTAbits.RA0==1){
            ciclo_util=ciclo_util+47;
            if(ciclo_util>125){
                ciclo_util=124;
            }
            CCPR1L=ciclo_util;
        }
        if(PORTAbits.RA0==0){
            ciclo_util=ciclo_util-47;
            if(ciclo_util<78){
                ciclo_util=78;
            }
            CCPR1L=ciclo_util;
        }
    }           
}
void PORT_INIT(void){
    ADCON1bits.PCFG=0xFF;
    TRISAbits.RA0=1;
    TRISAbits.RA4=1;
    TRISCbits.RC0=1;
    TRISCbits.RC1=0;
    TRISCbits.RC2=0;
    TRISD=0x00;
    TRISEbits.RE0=0;
    LATD=0x00;
    LATE=0x00;
}
void AFORO(void){  
    af=TMR1L-TMR0L;
            x=af/10;
            z=x;
            z=z*10;
            y=af-z;
            PORTD=y+(x*16);
    if(af>=30){LATEbits.LE0=1;}
    else if(af<=30){LATEbits.LE0=0;}
}
void TIMER0_INITAF(void){
    T0CONbits.T08BIT=1;
    T0CONbits.T0CS=1;
    T0CONbits.T0SE=0;
    T0CONbits.TMR0ON=1;
}
void TIMER1_INITAF(void){
    T1CONbits.RD16=0;
    T1CONbits.T1CKPS=00;
    T1CONbits.TMR1CS=1;
    T1CONbits.TMR1ON=1;
}
void PWM_50_80(void){
    PR2=0x9B;                               //periodo 100ms
    T2CON = 0x03;                           //prescaler 16
    CCP1CON = 0x0C;                         // modo pwm
    TMR2=0;                                                 
    T2CONbits.TMR2ON=1;
    CCPR1L=78;
}

//625--->000010011100 01
//50%--->000001001110 00 -->78
//80%--->000001111101 00 -->125   