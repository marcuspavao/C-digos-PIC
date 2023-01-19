/*
 * File:   Timer.c
 * Author: Marcus Vinícius Fernandes Pavão de Souza
 */

#include "configbits.h"
#define _XTAL_FREQ 8000000//6710783
#include <xc.h>

unsigned contagem = 0;
unsigned cont = 0;
void main(void) 
{
    ////////////////////////
    /// Configure Ports
    ////////////////////////
    TRISB = 0b00000011; //All pins as output
    TRISD = 0b00000000; //All pins as output
    PORTB = 0b00000000; //All pins off
    LATB = 0; //All pins off
    PORTD = 0; //All pins off
    LATD = 0; //All pins off   
    
    ADCON1 = 0b00001111; //configura todos os pinos AD como I/O digital
    // RBPU: PORTB Pull-up Enable bit 
    INTCON2bits.RBPU = 0; // 0 = PORTB pull-ups are enabled by individual port latch values 
    ////////////////////////
    /// Configure Ports
    ////////////////////////
    
    INTCON2bits.INTEDG0 = 0; // 0 = Interrupt on falling edge
    
    INTCONbits.INT0IF = 0; // The INT0 external interrupt occurred (must be cleared in software)
    INTCONbits.INT0IE = 1; //1 = Enables the INT0 external interrupt        

    INTCON3bits.INT1IF = 0;     
    INTCON3bits.INT1IE = 1; 
    
    //TMR0IE: TMR0 Overflow Interrupt Enable bit
    INTCONbits.TMR0IE = 1; //1 = Enables the TMR0 overflow interrupt
    //TMR0IF: TMR0 Overflow Interrupt Flag bit
    INTCONbits.TMR0IF = 0; // TMR0 register has overflowed (must be cleared in software)
    //Timer 0 config
    
    // FreqOsc = 8 Mhz / 4 = 2 Mhz que é a frequência da cpu
    T0CON = 0b11000010; // 0.5u (1 / 2 Mhz = 0.5us Período da CPU) * 256 (8 Bits) * 8 (8 prescale) = 1ms 
    TMR0 = 0;
    // O timer T0 irá estourar a cada 1ms
    INTCONbits.GIE = 1;
    while(1) 
    {
        CLRWDT();        
    if(contagem == 10000)    //quando o contagem = 10000, tempo = 10000 * 1ms = 10s;
    {   if(cont == 0){   
            LATDbits.LATD0 = 1;
        }else if(cont > 0 && cont <= 3){
            LATDbits.LATD1 = 1;
        }else if(cont > 3){
            LATDbits.LATD2 = 1;
        }
    }     
    }
    return;
}
/**************************************************************
***************************************************************/
void interrupt isr(void){
    if(INTCON3bits.INT1IF == 1)
    {
        INTCON3bits.INT1IF = 0;
        contagem = 0;
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
    }
    if (INTCONbits.INT0IF == 1)
    {
        INTCONbits.INT0IF = 0;
        cont++; 
        //__delaywdt_ms(100);
        //LATDbits.LATD4 = 1;
        //__delaywdt_ms(1000);
    }
    if (INTCONbits.TMR0IF == 1)
    {
        contagem++;
        INTCONbits.TMR0IF = 0;         
    }
}
