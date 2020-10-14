/*
 * File:   LAB2.c
 * Author: FLIA
 *
 * Created on 24 de agosto de 2020, 03:29 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000
#include "pic18f4550.h"
unsigned int ADC_L(unsigned char c);
void ADC_1(void);
void ADC_2(void);
void main(void) {
    TRISA = 1;
    TRISB = 1;
    TRISD = 0;
    TRISC = 0;
    LATD = 0;
    LATC = 0;
    ADCON1bits.PCFG = 0b1110; // A0 es analogo.
    ADCON1bits.VCFG = 0;
    ADCON2bits.ACQT = 2;
    ADCON2bits.ADCS = 4;
    ADCON2bits.ADFM = 1;
    
    while (1){
    if(PORTBbits.RB4==1){
        while(1){
            ADC_L(0);
            ADC_1();
            if(PORTBbits.RB4==0){
                LATC=0;
                LATD=0;
                break;}
        }
    }
    else if(PORTBbits.RB5==1){
        while(1){
            ADC_L(1);
            ADC_2();
            if(PORTBbits.RB5==0){
                LATD=0;
                LATC=0;
                break;}
        }
    }
    }
}

unsigned int ADC_L(unsigned char c){
    if(c>13){return 0;}
    ADCON0=0;
    ADCON0= c<<2;    
    ADCON0bits.ADON = 1;
    ADCON0bits.GO_DONE=1;
    while(ADCON0bits.GO_DONE==1);
    ADCON0bits.ADON = 0;
    return ADRES;
}
void ADC_1(void){
    int h = 1024/5;
    int v,b,e;
    float a,c,d;
        a = ((ADRESL)+(ADRESH*256));
        c = a/h;
        v = c;
        d = c-v;
        d = d*10;
        e = d;
        LATD = (c+(e*16));
        if(a>=512){LATCbits.LC0=1;}
        else {LATCbits.LC0=0;}
}
void ADC_2(void){
    int a;
    int s;
        a = ((ADRESL)+(ADRESH*256));
        if(a>=164){
            s = 1;
            LATCbits.LC1=1;}
        else {
            s = 0;
            LATCbits.LC1=0;}
        int L1=!s&!PORTBbits.RB0&PORTBbits.RB1&!PORTBbits.RB2;
        int L2=!s&PORTBbits.RB0&!PORTBbits.RB1&PORTBbits.RB2;
        int L3=s&PORTBbits.RB0&PORTBbits.RB1&!PORTBbits.RB2;
        int L4=s&!PORTBbits.RB0&!PORTBbits.RB1&PORTBbits.RB2;
        int L5=L1|L2|L3|L4;
        LATCbits.LC2=L5;
}
