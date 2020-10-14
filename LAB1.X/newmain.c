/*
 * File:   newmain.c
 * Author: FLIA
 *
 * Created on 16 de agosto de 2020, 03:50 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000
#include "pic18f4550.h"
int pul = 0;
int bit = 1;
int c = 0x00;
int b = 0xFF;
int a = 1;
int j = 0;
int m = 1;
void main(void) {
    ADCON1bits.PCFG=0xFF;
    TRISA = 0x04;
    TRISD = 0x00;
    TRISB = 0x00;
    LATD = 0x00;
    LATB = 0x00;
    LATA = 0x00;
    while (1) {
    if(PORTAbits.RA2==1){
        __delay_ms(200);
            pul=pul+1;
            if(pul==5){
                pul=1;
            }
        }
    if(pul==1){
        LATD=0x80;
        __delay_ms(200);
        for(int i =0; i<=7;i++){
            __delay_ms(200);
            LATD=LATD>>1;}
            
        LATD=0x01;
        for(int i=0;i<=7;i++){
            __delay_ms(200);
            LATD=LATD<<1;}
        }

    else if(pul==2){
        c=0x00;
        LATB=c;
        a=1;
        for(int i=0;i<=8;i++){
            __delay_ms(1000);
            LATB=c;
            c=c+a;
            a=a*2;
        }
        b=0xFF;
        a=1;
        LATB=b;
        for(int i=0;i<=8;i++){
            __delay_ms(1000);
            LATB=b;
            b=b-a;
            a=a*2;
    }
    }
    else if(pul==3){
        for( int i = 0; i<=15; i++){
        __delay_ms(1000);
        LATA=j;
        j=j+8;
        __delay_ms(1000);
        LATA=m;
        m=m+8;
    }
    }
    else if(pul==4){
        LATA=0x00;
        LATAbits.LA1 = 1;
            __delay_ms(500);
        LATAbits.LA1 = 0;
            __delay_ms(500);   
    }
    }
}
