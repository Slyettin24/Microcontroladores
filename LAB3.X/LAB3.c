/*
 * File:   LAB3.1
 * Author: FLIA
 *
 * Created on 13 de septiembre de 2020, 08:13 PM
 */
#include <xc.h>
#include <pic18f4550.h>
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config FOSC = XT_XT     // Oscillator Selection bits (XT oscillator (XT))
#define _XTAL_FREQ 4000000
int obtener_numero(void);
int leer_teclado(void);
char i;
void main(void) {
    ADCON1bits.PCFG=0xF;
    INTCON2bits.NOT_RBPU=0;
    TRISC=0x00;
    PORTC=0x00;
    TRISB=0b11110000;
    PORTB=0b00001111;
    TRISD=0x00;
    PORTD=0x00;
    INTCONbits.GIE=1;
    INTCONbits.RBIE=1;
    INTCONbits.RBIF=0;
    while(1){
        i=teclado();
        if(i!=0b00100011){
            PORTD=i;
        }
    }
    return;
}
int __interrupt () teclado (void) {
    int j;
    j=obtener_numero();
    while(PORTBbits.RB4==0||PORTBbits.RB5==0||PORTBbits.RB6==0);
    INTCONbits.RBIF=0;
    return j;
}
int obtener_numero(void){
    int valor=0;
    int H,L;
    char T,U;
    T=leer_teclado();
    H=T-'0';
    PORTD=H;
    U=leer_teclado();
    L=U-'0';
    H=H*16;
    valor=H+L;
    return valor;
}
int leer_teclado(void){
    char v;
    PORTD=0x00;
    PORTB=0b11111110;
    if(PORTBbits.RB0==0){
        if(PORTBbits.RB4==0){v='1';}
        if(PORTBbits.RB5==0){v='2';}
        if(PORTBbits.RB6==0){v='3';}
    }
    PORTB=0b11111101;
    if(PORTBbits.RB1==0){
        if(PORTBbits.RB4==0){v='4';}
        if(PORTBbits.RB5==0){v='5';}
        if(PORTBbits.RB6==0){v='6';}
    }
    PORTB=0b11111011;
    if(PORTBbits.RB2==0){
        if(PORTBbits.RB4==0){v='7';}
        if(PORTBbits.RB5==0){v='8';}
        if(PORTBbits.RB6==0){v='9';}
    }
    PORTB=0b11110111;    
    if(PORTBbits.RB3==0){
        if(PORTBbits.RB4==0){v='*';}
        if(PORTBbits.RB5==0){v='0';}
        if(PORTBbits.RB6==0){v='#';}
    }
    PORTB=0b11111111;
    return v;
}