/*
 * File:   mainMotor.c
 * Author: Marcus Vinícius Fernandes Pavão de Souza
 */

// Funciona na Placa Exto NEO201 e na PicGenios
// alterar flexlcd.h para o LCD funcionar em cada uma das placas

#define _XTAL_FREQ 8000000
#include "configbits.h"
#include <xc.h>
#include "flexlcd.h"
#define MY_NAME PORTBbits.RB3
#define RELAY1 PORTCbits.RC0
#define RELAY2 PORTEbits.RE0

void main(void) 
{
    ADCON0 = 0b00000000; // Desabilita o conversor A/D
    ADCON1 = 0b00001111; //configura todos os pinos AD como I/O
    //ADCON2 = 0b00000000;
    //INTCON = 0b00000000;
    //INTCON2 = 0b00000000;
    INTCON2bits.RBPU = 1; // Pull-up resistors
    // Input or Output
    TRISB = 0b11111111; 
    TRISC = 0b00000000;
    TRISD = 0b00000000; 
    TRISE = 0b00000000;
    
    INTCON2bits.INTEDG0 = 0; // 0 = Interrupt on falling edge
    
    INTCONbits.INT0IF = 0; 
    INTCONbits.INT0IE = 1;        

    INTCON3bits.INT1IF = 0;     
    INTCON3bits.INT1IE = 1; 
    // Clear ports
    PORTB = 0; 
    LATB = 0;
    PORTC = 0; 
    LATC = 0;
    PORTD = 0; 
    LATD = 0;
    PORTE = 0; 
    LATE = 0;
    
    int col, l;
    col = 0;
    l = 1;
    Lcd_Init();
    Lcd_Cmd(LCD_CURSOR_OFF);
    Lcd_Out(1, 0, "Motor 1: OFF");
    Lcd_Out(2, 0, "Motor 2: OFF");
    ei(); // Enable global interrupt
    while(1) 
    {
            
        if(MY_NAME == 0){
            Lcd_Cmd(LCD_CLEAR);  
            Lcd_Out(l, 0, "Marcus");
            __delaywdt_ms(200);
        }
        
        CLRWDT();   
    }
    return;
    
}

void interrupt isr(void){
    if(INTCON3bits.INT1IF == 1)
    {
        INTCON3bits.INT1IF = 0;
        if(RELAY2 == 0){
            RELAY2 = ~RELAY2;
            Lcd_Out(2, 0, "Motor 2: ON ");
            __delaywdt_ms(200);}
        else{
            RELAY2 = ~RELAY2;
            Lcd_Out(2, 0, "Motor 2: OFF");
            __delaywdt_ms(200);
        }
        
    }
    if (INTCONbits.INT0IF == 1)
    {
        INTCONbits.INT0IF = 0;
        if(RELAY1 == 0){
            RELAY1 = ~RELAY1;
            Lcd_Cmd(LCD_FIRST_ROW);
            Lcd_Out(1, 0, "Motor 1: ON ");
            __delaywdt_ms(200);}
        else{
            RELAY1 = ~RELAY1;
            Lcd_Out(1, 0, "Motor 1: OFF");
            __delaywdt_ms(200);
        }
        
    }
}
