/* File:   Prática 3
 * Author: Marcus Vinícius Fernandes Pavão de Souza */

#include "configbits.h"
#define _XTAL_FREQ 8000000
#include <xc.h>
#include "display7s.h"

// variables
int count = 0, flag = 0;
unsigned char tmp;


void main(void) 
{
    // Configure Ports
    TRISA = 0b00000000; //
    TRISB = 0b00001111; //
    TRISD = 0b00000000; //
    PORTA = 0; //All pins off
    LATA = 0; //All pins off
    PORTB = 0; //All pins off
    LATB = 0; //All pins off
    PORTD = 0; //All pins off
    LATD = 0; //All pins off   
    
    ADCON1 = 0b00001111; //configura todos os pinos AD como I/O digital

    INTCON2bits.RBPU = 0; // 0 = PORTB pull-ups are enabled by individual port latch values 

    INTCON2bits.INTEDG0 = 0;
    
    INTCON3bits.INT1IF = 0;     
    INTCON3bits.INT1IE = 1;
    
    INTCON3bits.INT2IF = 0;     
    INTCON3bits.INT2IE = 1;
    
    INTCONbits.INT0IF = 0; 
    INTCONbits.INT0IE = 1;
    
    INTCONbits.TMR0IF = 0; 
    INTCONbits.TMR0IE = 1; 

    //Timer 0 config
    T0CON = 0b11000101; // 8bit and 1:64 Prescale - 0.5u * 256 * 64 = 8ms
    TMR0 = 131;
    ei(); // Enable global interrupt

    LATAbits.LATA2 = 1; //habilita Display 1 da PICGenios
    while(1) 
    {
//    LATD = display7s(tmp);
//    __delaywdt_ms(300);
//    LATBbits.LATB1 = ~LATBbits.LATB1;
//    tmp++;    
    CLRWDT();
    }
    return;
}

void interrupt isr(void){
//    if (INTCONbits.INT0F == 1)
//    {
//        INTCONbits.INT0F = 0; 
//        tmp = 0;
//        flag = 1;
//    }
//    if(INTCON3bits.INT2IF == 1)
//    {
//        INTCON3bits.INT2IF = 0;
//        LATD = display7s(tmp);
//        tmp++;
//    }
//    if(INTCON3bits.INT1IF == 1)
//    {
//        INTCON3bits.INT1IF = 0;
//        tmp = tmp - 1;
//        LATD = display7s(tmp);
//    }
//    if (INTCONbits.TMR0IF == 1)
//    {
//        INTCONbits.TMR0IF = 0; 
//        TMR0 = 131;
//        count ++;
//        if (count == 250)
//        {
//            count = 0;
//            LATBbits.LATB1 = ~LATBbits.LATB1;
//            LATD = display7s(tmp);
//            tmp++;
//            if(tmp == 10 && flag == 1)
//            {
//                INTCONbits.TMR0IE = 0;
//                __delaywdt_ms(1000);
//                LATD = display7s(0);                
//            }
//            if (tmp > 15)
//            {
//                tmp = 0;
//            }
//        }
//        
//    }
}
